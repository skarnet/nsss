/* ISC license. */

#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <stdint.h>
#include <errno.h>

#include <skalibs/posixishard.h>
#include <skalibs/posixplz.h>
#include <skalibs/uint32.h>
#include <skalibs/sgetopt.h>
#include <skalibs/buffer.h>
#include <skalibs/strerr.h>
#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <skalibs/djbunix.h>
#include <skalibs/socket.h>
#include <skalibs/unix-timed.h>

#include <nsss/nsssd.h>
#include "nsssd-nslcd.h"

#define USAGE "nsssd-nslcd [ -t timeout ] path-to-nslcd-socket"
#define dieusage() strerr_dieusage(100, USAGE)

typedef struct nslcd_handle_s nslcd_handle_t, *nslcd_handle_t_ref ;
struct nslcd_handle_s
{
  char const *socketpath ;
  genalloc entries[3] ; /* nsss_passwd_t, nsss_group_t, nsss_spwd_t */
  stralloc data[3] ;
  size_t head[3] ;
  genalloc grmemc ; /* size_t */
  genalloc grmem ; /* char * */
  size_t grhead ;
  unsigned int needdata ;
} ;
#define NSLCD_HANDLE_ZERO \
{ \
  .socketpath = 0, \
  .entries = { GENALLOC_ZERO, GENALLOC_ZERO, GENALLOC_ZERO }, \
  .data = { STRALLOC_ZERO, STRALLOC_ZERO, STRALLOC_ZERO }, \
  .head = { 0, 0, 0 }, \
  .grmemc = GENALLOC_ZERO, \
  .grmem = GENALLOC_ZERO, \
  .grhead = 0, \
  .needdata = 0 \
}

static tain tto = TAIN_INFINITE_RELATIVE ;

void *nsssd_handle_init (void)
{
  static nslcd_handle_t a = NSLCD_HANDLE_ZERO ;
  return &a ;
}

int nsssd_handle_start (void *handle, char const *const *argv)
{
  nslcd_handle_t *a = handle ;
  if (!argv[0]) strerr_dieusage(100, USAGE) ;
  a->socketpath = argv[0] ;
  return 1 ;
}

void nsssd_handle_end (void *handle)
{
  static const nslcd_handle_t nslcd_handle_zero = NSLCD_HANDLE_ZERO ;
  nslcd_handle_t *a = handle ;
  genalloc_free(nsssd_passwd_t, &a->entries[0]) ;
  genalloc_free(nsssd_group_t, &a->entries[1]) ;
  genalloc_free(nsssd_spwd_t, &a->entries[2]) ;
  stralloc_free(&a->data[0]) ;
  stralloc_free(&a->data[1]) ;
  stralloc_free(&a->data[2]) ;
  genalloc_free(size_t, &a->grmemc) ;
  genalloc_free(char *, &a->grmem) ;
  *a = nslcd_handle_zero ;
}

static int read_uint32 (buffer *b, uint32_t *x, tain const *deadline)
{
  char pack[4] ;
  if (buffer_timed_get_g(b, pack, 4, deadline) < 4) return 0 ;
  uint32_unpack_big(pack, x) ;
  return 1 ;
}

static int read_string (buffer *b, size_t *value, stralloc *sa, tain const *deadline)
{
  uint32_t len ;
  if (!read_uint32(b, &len, deadline)) return 0 ;
  if (!stralloc_readyplus(sa, len+1)) return 0 ;
  if (buffer_timed_get_g(b, sa->s + sa->len, len, deadline) < len) return 0 ;
  *value = sa->len ;
  sa->len += len ;
  sa->s[sa->len++] = 0 ;
  return 1 ;
}

static inline int read_stringlist (buffer *b, size_t *head, size_t *n, stralloc *sa, genalloc *ga, tain const *deadline)
{
  uint32_t i ;
  size_t *p ;
  if (!read_uint32(b, &i, deadline)) return 0 ;
  if (!genalloc_readyplus(size_t, ga, i)) return 0 ;
  *head = genalloc_len(size_t, ga) ;
  p = genalloc_s(size_t, ga) + *head ;
  *n = i ;
  while (i--) if (!read_string(b, p++, sa, deadline)) return 0 ;
  return 1 ;
}

static inline int read_header (buffer *b, uint32_t action, tain const *deadline)
{
  uint32_t x ;
  char pack[8] ;
  if (buffer_timed_get_g(b, pack, 8, deadline) < 8) return 0 ;
  uint32_unpack_big(pack, &x) ;
  if (x != NSLCD_VERSION) return (errno = EPROTO, 0) ;
  uint32_unpack_big(pack+4, &x) ;
  if (x != action) return (errno = EPROTO, 0) ;
  return 1 ;
}

static int read_beginend (buffer *b, tain const *deadline)
{
  uint32_t x ;
  if (!read_uint32(b, &x, deadline)) return -1 ;
  switch (x)
  {
    case NSLCD_RESULT_BEGIN : return 1 ;
    case NSLCD_RESULT_END : return 0 ;
    default : return (errno = EPROTO, -1) ;
  }
}

static int read_eof (buffer *b, tain const *deadline)
{
  char c ;
  ssize_t r = buffer_timed_get_g(b, &c, 1, deadline) ;
  if (r < 0) return 0 ;
  if (r) return (errno = EPROTO, 0) ;
  return 1 ;
}

static int read_endeof(buffer *b, tain const *deadline)
{
  int r = read_beginend(b, deadline) ;
  if (r < 0) return 0 ;
  if (r) return (errno = EPROTO, 0) ;
  return read_eof(b, deadline) ;
}

static int read_pw (buffer *b, nsssd_passwd_t *pw, stralloc *sa, tain const *deadline)
{
  uint32_t x ;
  if (!read_string(b, &pw->pw_name, sa, deadline)) return 0 ;
  if (!read_string(b, &pw->pw_passwd, sa, deadline)) return 0 ;
  if (!read_uint32(b, &x, deadline)) return 0 ;
  pw->pw_uid = x ;
  if (!read_uint32(b, &x, deadline)) return 0 ;
  pw->pw_gid = x ;
  if (!read_string(b, &pw->pw_gecos, sa, deadline)) return 0 ;
  if (!read_string(b, &pw->pw_dir, sa, deadline)) return 0 ;
  if (!read_string(b, &pw->pw_shell, sa, deadline)) return 0 ;
  return 1 ;
}

static int read_gr (buffer *b, nsssd_group_t *gr, stralloc *sa, genalloc *ga, tain const *deadline)
{
  uint32_t x ;
  if (!read_string(b, &gr->gr_name, sa, deadline)) return 0 ;
  if (!read_string(b, &gr->gr_passwd, sa, deadline)) return 0 ;
  if (!read_uint32(b, &x, deadline)) return 0 ;
  gr->gr_gid = x ;
  if (!read_stringlist(b, &gr->gr_mem, &gr->gr_mem_n, sa, ga, deadline)) return 0 ;
  return 1 ;
}

static int read_sp (buffer *b, nsssd_spwd_t *sp, stralloc *sa, tain const *deadline)
{
  uint32_t x ;
  if (!read_string(b, &sp->sp_namp, sa, deadline)) return 0 ;
  if (!read_string(b, &sp->sp_pwdp, sa, deadline)) return 0 ;
  if (!read_uint32(b, &x, deadline)) return 0 ;
  sp->sp_lstchg = x ;
  if (!read_uint32(b, &x, deadline)) return 0 ;
  sp->sp_min = x ;
  if (!read_uint32(b, &x, deadline)) return 0 ;
  sp->sp_max = x ;
  if (!read_uint32(b, &x, deadline)) return 0 ;
  sp->sp_warn = x ;
  if (!read_uint32(b, &x, deadline)) return 0 ;
  sp->sp_inact = x ;
  if (!read_uint32(b, &x, deadline)) return 0 ;
  sp->sp_expire = x ;
  if (!read_uint32(b, &x, deadline)) return 0 ;
  sp->sp_flag = x ;
  return 1 ;
}

static int nslcd_connect (nslcd_handle_t *a, uint32_t action, struct iovec const *v, unsigned int n, tain const *deadline)
{
  char pack[8] ;
  int fd = ipc_stream_nbcoe() ;
  struct iovec vv[n+1] ;
  if (fd < 0) return 0 ;
  vv[0].iov_base = pack ;
  vv[0].iov_len = 8 ;
  for (unsigned int i = 0 ; i < n ; i++) vv[i+1] = v[i] ;
  if (!ipc_timed_connect_g(fd, a->socketpath, deadline)) goto err ;
  uint32_pack_big(pack, NSLCD_VERSION) ;
  uint32_pack_big(pack + 4, action) ;
  if (!ipc_timed_sendv_g(fd, vv, n+1, deadline)) goto err ;
  if (shutdown(fd, SHUT_WR) < 0) goto err ;
  return fd ;

 err:
  fd_close(fd) ;
  return -1 ;
}

int nsssd_pwd_start (void *handle)
{
  nslcd_handle_t *a = handle ;
  a->head[0] = 0 ;
  a->needdata |= 1 ;
  return 1 ;
}

int nsssd_pwd_rewind (void *handle)
{
  nslcd_handle_t *a = handle ;
  a->head[0] = 0 ;
  a->needdata |= 1 ;
  return 1 ;
}

static inline int pwd_getall (nslcd_handle_t *a)
{
  tain deadline ;
  int fd ;
  buffer b ;
  char buf[8192] ;
  tain_add_g(&deadline, &tto) ;
  fd = nslcd_connect(a, NSLCD_ACTION_PASSWD_ALL, 0, 0, &deadline) ;
  if (fd < 0) return 0 ;
  buffer_init(&b, &buffer_read, fd, buf, 8192) ;
  if (!read_header(&b, NSLCD_ACTION_PASSWD_ALL, &deadline)) goto err ;
  genalloc_setlen(nsssd_passwd_t, &a->entries[0], 0) ;
  a->data[0].len = 0 ;
  for (;;)
  {
    int r = read_beginend(&b, &deadline) ;
    if (r < 0) goto err ;
    if (!r) break ;
    if (!genalloc_readyplus(nsssd_passwd_t, &a->entries[0], 1)) goto err ;
    if (!read_pw(&b, genalloc_s(nsssd_passwd_t, &a->entries[0]) + genalloc_len(nsssd_passwd_t, &a->entries[0]), &a->data[0], &deadline)) goto err ;
    genalloc_setlen(nsssd_passwd_t, &a->entries[0], genalloc_len(nsssd_passwd_t, &a->entries[0]) + 1) ;
  }
  if (!read_eof(&b, &deadline)) goto err ;
  fd_close(fd) ;
  return 1 ;

 err:
  fd_close(fd) ;
  return 0 ;
}

int nsssd_pwd_get (void *handle, struct passwd *pw)
{
  nslcd_handle_t *a = handle ;
  if (a->needdata & 1)
  {
    if (!pwd_getall(a)) return 0 ;
    a->needdata &= ~1 ;
  }
  if (a->head[0] >= genalloc_len(nsssd_passwd_t, &a->entries[0])) return 0 ;
  nsssd_passwd_convert(pw, genalloc_s(nsssd_passwd_t, &a->entries[0]) + a->head[0]++, a->data[0].s) ;
  return 1 ;
}

int nsssd_pwd_getbyuid (void *handle, struct passwd *pw, uid_t uid)
{
  nslcd_handle_t *a = handle ;
  nsssd_passwd_t pwc ;
  tain deadline ;
  int fd ;
  buffer b ;
  char buf[4096] ;
  struct iovec v = { .iov_base = buf, .iov_len = 4 } ;
  tain_add_g(&deadline, &tto) ;
  uint32_pack_big(buf, uid) ;
  fd = nslcd_connect(a, NSLCD_ACTION_PASSWD_BYUID, &v, 1, &deadline) ;
  if (fd < 0) return 0 ;
  buffer_init(&b, &buffer_read, fd, buf, 4096) ;
  if (!read_header(&b, NSLCD_ACTION_PASSWD_BYUID, &deadline)) goto err ;
  if (read_beginend(&b, &deadline) <= 0) goto err ;
  a->data[0].len = 0 ;
  if (!read_pw(&b, &pwc, &a->data[0], &deadline)) goto err ;
  if (!read_endeof(&b, &deadline)) goto err ;
  fd_close(fd) ;
  nsssd_passwd_convert(pw, &pwc, a->data[0].s) ;
  return 1 ;

 err:
  fd_close(fd) ;
  return 0 ;
}

int nsssd_pwd_getbyname (void *handle, struct passwd *pw, char const *name)
{
  nslcd_handle_t *a = handle ;
  nsssd_passwd_t pwc ;
  tain deadline ;
  int fd ;
  buffer b ;
  char buf[4096] ;
  struct iovec v[2] = { { .iov_base = buf, .iov_len = 4 }, { .iov_base = (char *)name, .iov_len = strlen(name) } } ;
  tain_add_g(&deadline, &tto) ;
  fd = nslcd_connect(a, NSLCD_ACTION_PASSWD_BYNAME, v, 2, &deadline) ;
  if (fd < 0) return 0 ;
  buffer_init(&b, &buffer_read, fd, buf, 4096) ;
  if (!read_header(&b, NSLCD_ACTION_PASSWD_BYNAME, &deadline)) goto err ;
  if (read_beginend(&b, &deadline) <= 0) goto err ;
  a->data[0].len = 0 ;
  if (!read_pw(&b, &pwc, &a->data[0], &deadline)) goto err ;
  if (!read_endeof(&b, &deadline)) goto err ;
  fd_close(fd) ;
  nsssd_passwd_convert(pw, &pwc, a->data[0].s) ;
  return 1 ;

 err:
  fd_close(fd) ;
  return 0 ;
}

void nsssd_pwd_end (void *handle)
{
  (void)handle ;
}

int nsssd_grp_start (void *handle)
{
  nslcd_handle_t *a = handle ;
  a->head[1] = 0 ;
  a->grhead = 0 ;
  a->needdata |= 2 ;
  return 1 ;
}

int nsssd_grp_rewind (void *handle)
{
  nslcd_handle_t *a = handle ;
  a->head[1] = 0 ;
  a->grhead = 0 ;
  a->needdata |= 2 ;
  return 1 ;
}

static inline int grp_getall (nslcd_handle_t *a)
{
  tain deadline ;
  int fd ;
  buffer b ;
  char buf[8192] ;
  tain_add_g(&deadline, &tto) ;
  fd = nslcd_connect(a, NSLCD_ACTION_GROUP_ALL, 0, 0, &deadline) ;
  if (fd < 0) return 0 ;
  buffer_init(&b, &buffer_read, fd, buf, 8192) ;
  if (!read_header(&b, NSLCD_ACTION_GROUP_ALL, &deadline)) goto err ;
  genalloc_setlen(nsssd_group_t, &a->entries[1], 0) ;
  a->data[1].len = 0 ;
  genalloc_setlen(size_t, &a->grmemc, 0) ;
  for (;;)
  {
    int r = read_beginend(&b, &deadline) ;
    if (r < 0) goto err ;
    if (!r) break ;
    if (!genalloc_readyplus(nsssd_group_t, &a->entries[1], 1)) goto err ;
    if (!read_gr(&b, genalloc_s(nsssd_group_t, &a->entries[1]) + genalloc_len(nsssd_group_t, &a->entries[1]), &a->data[1], &a->grmemc, &deadline)) goto err ;
    genalloc_setlen(nsssd_group_t, &a->entries[1], genalloc_len(nsssd_group_t, &a->entries[1]) + 1) ;
  }
  if (!read_eof(&b, &deadline)) goto err ;
  fd_close(fd) ;
  return 1 ;

 err:
  fd_close(fd) ;
  return 0 ;
}

int nsssd_grp_get (void *handle, struct group *gr)
{
  nslcd_handle_t *a = handle ;
  nsssd_group_t *grc ;
  if (a->needdata & 2)
  {
    if (!grp_getall(a)) return 0 ;
    a->needdata &= ~2 ;
  }
  if (a->head[1] >= genalloc_len(nsssd_group_t, &a->entries[1])) return 0 ;
  grc = genalloc_s(nsssd_group_t, &a->entries[1]) + a->head[1]++ ;
  if (!genalloc_ready(char *, &a->grmem, grc->gr_mem_n + 1)) return 0 ;
  nsssd_group_convert(gr, genalloc_s(char *, &a->grmem), grc, a->data[1].s, genalloc_s(size_t, &a->grmemc) + a->grhead) ;
  a->grhead += grc->gr_mem_n ;
  return 1 ;
}

int nsssd_grp_getbygid (void *handle, struct group *gr, gid_t gid)
{
  nslcd_handle_t *a = handle ;
  nsssd_group_t grc ;
  tain deadline ;
  int fd ;
  buffer b ;
  char buf[4096] ;
  struct iovec v = { .iov_base = buf, .iov_len = 4 } ;
  tain_add_g(&deadline, &tto) ;
  uint32_pack_big(buf, gid) ;
  fd = nslcd_connect(a, NSLCD_ACTION_GROUP_BYGID, &v, 1, &deadline) ;
  if (fd < 0) return 0 ;
  buffer_init(&b, &buffer_read, fd, buf, 4096) ;
  if (!read_header(&b, NSLCD_ACTION_GROUP_BYGID, &deadline)) goto err ;
  if (read_beginend(&b, &deadline) <= 0) goto err ;
  a->data[1].len = 0 ;
  genalloc_setlen(size_t, &a->grmemc, 0) ;
  if (!read_gr(&b, &grc, &a->data[1], &a->grmemc, &deadline)) goto err ;
  if (!read_endeof(&b, &deadline)) goto err ;
  fd_close(fd) ;
  if (!genalloc_ready(char *, &a->grmem, grc.gr_mem_n + 1)) return 0 ;
  nsssd_group_convert(gr, genalloc_s(char *, &a->grmem), &grc, a->data[1].s, genalloc_s(size_t, &a->grmemc)) ;
  return 1 ;

 err:
  fd_close(fd) ;
  return 0 ;
}

int nsssd_grp_getbyname (void *handle, struct group *gr, char const *name)
{
  nslcd_handle_t *a = handle ;
  nsssd_group_t grc ;
  tain deadline ;
  int fd ;
  buffer b ;
  char buf[4096] ;
  struct iovec v[2] = { { .iov_base = buf, .iov_len = 4 }, { .iov_base = (char *)name, .iov_len = strlen(name) } } ;
  tain_add_g(&deadline, &tto) ;
  fd = nslcd_connect(a, NSLCD_ACTION_GROUP_BYNAME, v, 2, &deadline) ;
  if (fd < 0) return 0 ;
  buffer_init(&b, &buffer_read, fd, buf, 4096) ;
  if (!read_header(&b, NSLCD_ACTION_GROUP_BYNAME, &deadline)) goto err ;
  if (read_beginend(&b, &deadline) <= 0) goto err ;
  a->data[1].len = 0 ;
  genalloc_setlen(size_t, &a->grmemc, 0) ;
  if (!read_gr(&b, &grc, &a->data[1], &a->grmemc, &deadline)) goto err ;
  if (!read_endeof(&b, &deadline)) goto err ;
  fd_close(fd) ;
  if (!genalloc_ready(char *, &a->grmem, grc.gr_mem_n + 1)) return 0 ;
  nsssd_group_convert(gr, genalloc_s(char *, &a->grmem), &grc, a->data[1].s, genalloc_s(size_t, &a->grmem)) ;
  return 1 ;

 err:
  fd_close(fd) ;
  return 0 ;
}

int nsssd_grp_getlist (void *handle, char const *user, gid_t *gids, size_t n, size_t *r)
{
  /* TODO: find a sane way of implementing getgrouplist() over nslcd */
  (void)handle ;
  (void)user ;
  (void)gids ;
  (void)n ;
  (void)r ;
  return (errno = ENOSYS, 0) ;
}

void nsssd_grp_end (void *handle)
{
  (void)handle ;
}

int nsssd_shadow_start (void *handle)
{
  nslcd_handle_t *a = handle ;
  a->head[2] = 0 ;
  a->needdata |= 4 ;
  return 1 ;
}

int nsssd_shadow_rewind (void *handle)
{
  nslcd_handle_t *a = handle ;
  a->head[2] = 0 ;
  a->needdata |= 4 ;
  return 1 ;
}

static inline int shadow_getall (nslcd_handle_t *a)
{
  tain deadline ;
  int fd ;
  buffer b ;
  char buf[8192] ;
  tain_add_g(&deadline, &tto) ;
  fd = nslcd_connect(a, NSLCD_ACTION_SHADOW_ALL, 0, 0, &deadline) ;
  if (fd < 0) return 0 ;
  buffer_init(&b, &buffer_read, fd, buf, 8192) ;
  if (!read_header(&b, NSLCD_ACTION_SHADOW_ALL, &deadline)) goto err ;
  genalloc_setlen(nsssd_spwd_t, &a->entries[2], 0) ;
  a->data[2].len = 0 ;
  for (;;)
  {
    int r = read_beginend(&b, &deadline) ;
    if (r < 0) goto err ;
    if (!r) break ;
    if (!genalloc_readyplus(nsssd_spwd_t, &a->entries[2], 1)) goto err ;
    if (!read_sp(&b, genalloc_s(nsssd_spwd_t, &a->entries[2]) + genalloc_len(nsssd_spwd_t, &a->entries[2]), &a->data[2], &deadline)) goto err ;
    genalloc_setlen(nsssd_spwd_t, &a->entries[2], genalloc_len(nsssd_spwd_t, &a->entries[2]) + 1) ;
  }
  if (!read_eof(&b, &deadline)) goto err ;
  fd_close(fd) ;
  return 1 ;

 err:
  fd_close(fd) ;
  return 0 ;
}

int nsssd_shadow_get (void *handle, struct spwd *sp)
{
  nslcd_handle_t *a = handle ;
  if (a->needdata & 4)
  {
    if (!shadow_getall(a)) return 0 ;
    a->needdata &= ~4 ;
  }
  if (a->head[2] >= genalloc_len(nsssd_spwd_t, &a->entries[2])) return 0 ;
  nsssd_spwd_convert(sp, genalloc_s(nsssd_spwd_t, &a->entries[2]) + a->head[2]++, a->data[2].s) ;
  return 1 ;
}

int nsssd_shadow_getbyname (void *handle, struct spwd *sp, char const *name)
{
  nslcd_handle_t *a = handle ;
  nsssd_spwd_t spc ;
  tain deadline ;
  int fd ;
  buffer b ;
  char buf[4096] ;
  struct iovec v[2] = { { .iov_base = buf, .iov_len = 4 }, { .iov_base = (char *)name, .iov_len = strlen(name) } } ;
  tain_add_g(&deadline, &tto) ;
  fd = nslcd_connect(a, NSLCD_ACTION_SHADOW_BYNAME, v, 2, &deadline) ;
  if (fd < 0) return 0 ;
  buffer_init(&b, &buffer_read, fd, buf, 4096) ;
  if (!read_header(&b, NSLCD_ACTION_SHADOW_BYNAME, &deadline)) goto err ;
  if (read_beginend(&b, &deadline) <= 0) goto err ;
  a->data[2].len = 0 ;
  if (!read_sp(&b, &spc, &a->data[2], &deadline)) goto err ;
  if (!read_endeof(&b, &deadline)) goto err ;
  fd_close(fd) ;
  nsssd_spwd_convert(sp, &spc, a->data[2].s) ;
  return 1 ;

 err:
  fd_close(fd) ;
  return 0 ;
}

void nsssd_shadow_end (void *handle)
{
  (void)handle ;
}

int main (int argc, char const *const *argv)
{
  PROG = "nsssd-nslcd" ;
  {
    subgetopt l = SUBGETOPT_ZERO ;
    uint32_t t = 0 ;
    for (;;)
    {
      int opt = subgetopt_r(argc, argv, "t:", &l) ;
      if (opt == -1) break ;
      switch (opt)
      {
        case 't' : if (!uint320_scan(l.arg, &t)) dieusage() ; break ;
        default : dieusage() ;
      }
    }
    argc -= l.ind ; argv += l.ind ;
    if (t) tain_from_millisecs(&tto, t) ;
  }

  return nsssd_main(argv) ;
}
