/* ISC license. */

#include <string.h>
#include <sys/uio.h>
#include <errno.h>

#include <skalibs/posixishard.h>
#include <skalibs/uint32.h>
#include <skalibs/uint64.h>
#include <skalibs/types.h>
#include <skalibs/buffer.h>
#include <skalibs/stralloc.h>
#include <skalibs/unix-timed.h>

#include <nsss/nsss-switch.h>

 /*
    Expects:
      8 bytes: n
      8 bytes: r
      min(n, r) * sizeof(gid_t) bytes: the list of gids
  */

static int nsss_switch_grouplist_read (buffer *b, size_t n, size_t *r, gid_t *gids, stralloc *sa, tain_t const *deadline, tain_t *stamp)
{
  size_t rr ;
  uint64_t res ;
  char buf[8] ;
  if (!buffer_timed_get(b, buf, 8, deadline, stamp)) return 0 ;
  uint64_unpack_big(buf, &res) ;
  if (res != n) return (errno = EPROTO, 0) ;
  if (!buffer_timed_get(b, buf, 8, deadline, stamp)) return 0 ;
  uint64_unpack_big(buf, &res) ;
  rr = res ;
  if (res > n) res = n ;
  if (res)
  {
    int sawasnull = !sa->s ;
    size_t sabase = sa->len ;
    if (!stralloc_readyplus(sa, res * sizeof(gid_t))) return 0 ;
    if (!buffer_timed_get(b, sa->s + sabase, res * sizeof(gid_t), deadline, stamp))
    {
      if (sawasnull) stralloc_free(sa) ; else sa->len = sabase ;
      return 0 ;
    }
    for (size_t i = 0 ; i < res ; i++)
      gid_unpack_big(sa->s + sabase + i * sizeof(gid_t), gids + i) ;
    if (sawasnull) stralloc_free(sa) ; else sa->len = sabase ;  
  }
  *r = rr ;
  return 1 ;
}

int nsss_switch_grp_getlist (nsss_switch_t *a, char const *user, gid_t *gids, size_t n, size_t *r, stralloc *sa, tain_t const *deadline, tain_t *stamp)
{
  char buf[13] = { NSSS_SWITCH_GRP_GETLIST } ;
  size_t len = strlen(user) ;
  struct iovec v[2] = { { .iov_base = buf, .iov_len = 13 }, { .iov_base = (char *)user, .iov_len = len + 1 } } ;
  if (len > NSSS_SWITCH_NAME_MAXLEN - 1) return (errno = EINVAL, 0) ;
  uint64_pack_big(buf + 1, n) ;
  uint32_pack_big(buf + 9, len + 1) ;
  if (!ipc_timed_sendv(buffer_fd(&a->b), v, 2, deadline, stamp)) return 0 ;
  if (!buffer_timed_get(&a->b, &buf[0], 1, deadline, stamp)) return 0 ;
  if (buf[0]) return (errno = buf[0], 0) ;
  return nsss_switch_grouplist_read(&a->b, n, r, gids, sa, deadline, stamp) ;
}
