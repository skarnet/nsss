/* ISC license. */

#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#include <skalibs/posixishard.h>
#include <skalibs/uint32.h>
#include <skalibs/uint64.h>
#include <skalibs/types.h>
#include <skalibs/buffer.h>
#include <skalibs/strerr.h>
#include <skalibs/genalloc.h>
#include <skalibs/tai.h>
#include <skalibs/djbunix.h>
#include <skalibs/unix-timed.h>

#include <nsss/pwd-def.h>
#include <nsss/grp-def.h>
#include <nsss/shadow-def.h>
#include <nsss/nsss-switch.h>
#include <nsss/nsssd.h>

static unsigned int initted = 0 ;
static tain tto = TAIN_INFINITE_RELATIVE ;
static tain outertto = TAIN_INFINITE_RELATIVE ;

static void get0 (char *s, size_t n)
{
  tain deadline ;
  tain_add_g(&deadline, &tto) ;
  if (buffer_timed_get_g(buffer_0small, s, n, &deadline) < n)
    strerr_diefu1sys(111, "read from stdin") ;
}

static void put1 (char const *s, size_t n)
{
  size_t w = 0 ;
  tain deadline ;
  tain_add_g(&deadline, &tto) ;
  while (!buffer_putall(buffer_1, s, n, &w))
  {
    if (!buffer_timed_flush_g(buffer_1, &deadline))
    strerr_diefu1sys(111, "write to stdout") ;
  }
}

static void flush1 (void)
{
  tain deadline ;
  tain_add_g(&deadline, &tto) ;
  if (!buffer_timed_flush_g(buffer_1, &deadline))
    strerr_diefu1sys(111, "write to stdout") ;
}

static void answer (int e)
{
  unsigned char c = e ;
  buffer_putnoflush(buffer_1, (char *)&c, 1) ;
  flush1() ;
}

static inline void print_pw (struct passwd const *pw)
{
  size_t len, namelen, passwdlen, gecoslen, dirlen, shelllen ;
  char pack[12] ;
  namelen = strlen(pw->pw_name) + 1 ;
  passwdlen = strlen(pw->pw_passwd) + 1 ;
  gecoslen = strlen(pw->pw_gecos) + 1 ;
  dirlen = strlen(pw->pw_dir) + 1 ;
  shelllen = strlen(pw->pw_shell) + 1 ;
  len = namelen + passwdlen + gecoslen + dirlen + shelllen ;
  if (len > 0xffffffff) { answer(ENAMETOOLONG) ; return ; }
  put1("", 1) ;
  uint32_pack_big(pack, pw->pw_uid) ;
  uint32_pack_big(pack + 4, pw->pw_gid) ;
  uint32_pack_big(pack + 8, len) ;
  put1(pack, 12) ;
  put1(pw->pw_name, namelen) ;
  put1(pw->pw_passwd, passwdlen) ;
  put1(pw->pw_gecos, gecoslen) ;
  put1(pw->pw_dir, dirlen) ;
  put1(pw->pw_shell, shelllen) ;
  flush1() ;
}

static inline void print_gr (struct group const *gr)
{
  size_t len, namelen, passwdlen ;
  size_t n = 0 ;
  char pack[12] ;
  namelen = strlen(gr->gr_name) + 1 ;
  passwdlen = strlen(gr->gr_passwd) + 1 ;
  len = namelen + passwdlen ;
  for (char **p = gr->gr_mem ; *p ; n++, p++) len += strlen(*p) + 1 ;
  if (len > 0xffffffffu || n > 0x30000000u) { answer(ENAMETOOLONG) ; return ; }
  put1("", 1) ;
  uint32_pack_big(pack, gr->gr_gid) ;
  uint32_pack_big(pack + 4, len) ;
  uint32_pack_big(pack + 8, n) ;
  put1(pack, 12) ;
  put1(gr->gr_name, namelen) ;
  put1(gr->gr_passwd, passwdlen) ;
  for (size_t i = 0 ; i < n ; i++)
    put1(gr->gr_mem[i], strlen(gr->gr_mem[i]) + 1) ;
  flush1() ;
}

static inline void print_sp (struct spwd const *sp)
{
  size_t len, namplen, pwdplen ;
  char pack[60] ;
  namplen = strlen(sp->sp_namp) + 1 ;
  pwdplen = strlen(sp->sp_pwdp) + 1 ;
  len = namplen + pwdplen ;
  if (len > 0xffffffff) { answer(ENAMETOOLONG) ; return ; }
  put1("", 1) ;
  uint64_pack_big(pack, sp->sp_lstchg) ;
  uint64_pack_big(pack + 8, sp->sp_min) ;
  uint64_pack_big(pack + 16, sp->sp_max) ;
  uint64_pack_big(pack + 24, sp->sp_warn) ;
  uint64_pack_big(pack + 32, sp->sp_inact) ;
  uint64_pack_big(pack + 40, sp->sp_expire) ;
  uint64_pack_big(pack + 48, sp->sp_flag) ;
  uint32_pack_big(pack + 56, len) ;
  put1(pack, 60) ;
  put1(sp->sp_namp, namplen) ;
  put1(sp->sp_pwdp, pwdplen) ;
  flush1() ;
}

static inline void do_set_timeout (void)
{
  uint32_t t ;
  char buf[4] ;
  get0(buf, 4) ;
  uint32_unpack_big(buf, &t) ;
  if (t) tain_from_millisecs(&outertto, t) ;
  else outertto = tain_infinite_relative ;
  answer(0) ;
}

static inline void do_pwend (void *a)
{
  nsssd_pwd_end(a) ;
  answer(0) ;
}

static inline void do_pwrewind (void *a)
{
  if (!(initted & 1))
  {
    if (!nsssd_pwd_start(a))
    {
      answer(errno) ;
      return ;
    }
    initted |= 1 ;
  }
  if (!nsssd_pwd_rewind(a))
  {
    answer(errno) ;
    return ;
  }
  answer(0) ;
}

static inline void do_pwget (void *a)
{
  struct passwd pw ;
  if (!(initted & 1))
  {
    if (!nsssd_pwd_start(a))
    {
      answer(errno ? errno : NSSSD_EOF) ;
      return ;
    }
    initted |= 1 ;
  }
  if (!nsssd_pwd_get(a, &pw))
  {
    answer(errno ? errno : NSSSD_EOF) ;
    return ;
  }
  print_pw(&pw) ;
}

static inline void do_pwnam (void *a)
{
  struct passwd pw ;
  uint32_t len ;
  char buf[4] ;
  get0(buf, 4) ;
  uint32_unpack_big(buf, &len) ;
  if (!len || len > NSSS_SWITCH_NAME_MAXLEN - 1)
  {
    answer(EPROTO) ;
    return ;
  }
  {
    char name[len] ;
    get0(name, len) ;
    if (name[len-1])
    {
      answer(EPROTO) ;
      return ;
    }
    if (!nsssd_pwd_getbyname(a, &pw, name))
    {
      answer(errno ? errno : NSSSD_EOF) ;
      return ;
    }
  }
  print_pw(&pw) ;
}

static inline void do_pwuid (void *a)
{
  struct passwd pw ;
  uint32_t uid ;
  char buf[4] ;
  get0(buf, 4) ;
  uint32_unpack_big(buf, &uid) ;
  if (!nsssd_pwd_getbyuid(a, &pw, uid))
  {
    answer(errno ? errno : NSSSD_EOF) ;
    return ;
  }
  print_pw(&pw) ;
}

static inline void do_grend (void *a)
{
  nsssd_grp_end(a) ;
  answer(0) ;
}

static inline void do_grrewind (void *a)
{
  if (!(initted & 2))
  {
    if (!nsssd_grp_start(a))
    {
      answer(errno) ;
      return ;
    }
    initted |= 2 ;
  }
  if (!nsssd_grp_rewind(a))
  {
    answer(errno) ;
    return ;
  }
  answer(0) ;
}

static inline void do_grget (void *a)
{
  struct group gr ;
  if (!(initted & 2))
  {
    if (!nsssd_grp_start(a))
    {
      answer(errno) ;
      return ;
    }
    initted |= 2 ;
  }
  if (!nsssd_grp_get(a, &gr))
  {
    answer(errno ? errno : NSSSD_EOF) ;
    return ;
  }
  print_gr(&gr) ;
}

static inline void do_grnam (void *a)
{
  struct group gr ;
  uint32_t len ;
  char buf[4] ;
  get0(buf, 4) ;
  uint32_unpack_big(buf, &len) ;
  if (!len || len > NSSS_SWITCH_NAME_MAXLEN - 1)
  {
    answer(EPROTO) ;
    return ;
  }
  {
    char name[len] ;
    get0(name, len) ;
    if (name[len-1])
    {
      answer(EPROTO) ;
      return ;
    }
    if (!nsssd_grp_getbyname(a, &gr, name))
    {
      answer(errno ? errno : NSSSD_EOF) ;
      return ;
    }
  }
  print_gr(&gr) ;
}

static inline void do_grgid (void *a)
{
  struct group gr ;
  uint32_t gid ;
  char buf[4] ;
  get0(buf, 4) ;
  uint32_unpack_big(buf, &gid) ;
  if (!nsssd_grp_getbygid(a, &gr, gid))
  {
    answer(errno ? errno : NSSSD_EOF) ;
    return ;
  }
  print_gr(&gr) ;
}

static inline void do_grlist (void *a)
{
  uint64_t n ;
  uint32_t len ;
  char buf[12] ;
  get0(buf, 12) ;
  uint64_unpack_big(buf, &n) ;
  uint32_unpack_big(buf + 8, &len) ;
  if (!len || len > NSSS_SWITCH_NAME_MAXLEN - 1)
  {
    answer(EPROTO) ;
    return ;
  }
  {
    genalloc ga = GENALLOC_ZERO ;
    size_t r ;
    char user[len] ;
    get0(user, len) ;
    if (user[len-1])
    {
      answer(EPROTO) ;
      return ;
    }
    if (!genalloc_ready(gid_t, &ga, n))
    {
      answer(errno) ;
      return ;
    }
    if (!nsssd_grp_getlist(a, user, genalloc_s(gid_t, &ga), n, &r))
    {
      genalloc_free(gid_t, &ga) ;
      answer(errno) ;
      return ;
    }
    put1("", 1) ;
    uint64_pack_big(buf, n) ; put1(buf, 8) ;
    uint64_pack_big(buf, r) ; put1(buf, 8) ;
    if (r > n) r = n ;
    for (size_t i = 0 ; i < r ; i++)
    {
      gid_pack_big(buf, genalloc_s(gid_t, &ga)[i]) ;
      put1(buf, sizeof(gid_t)) ;
    }
    genalloc_free(gid_t, &ga) ;
  }
  flush1() ;
}

static inline void do_spend (void *a)
{
  nsssd_shadow_end(a) ;
  answer(0) ;
}

static inline void do_sprewind (void *a)
{
  if (!(initted & 4))
  {
    if (!nsssd_shadow_start(a))
    {
      answer(errno) ;
      return ;
    }
    initted |= 4 ;
  }
  if (!nsssd_shadow_rewind(a))
  {
    answer(errno) ;
    return ;
  }
  answer(0) ;
}

static inline void do_spget (void *a)
{
  struct spwd sp ;
  if (!(initted & 4))
  {
    if (!nsssd_shadow_start(a))
    {
      answer(errno) ;
      return ;
    }
    initted |= 4 ;
  }
  if (!nsssd_shadow_get(a, &sp))
  {
    answer(errno ? errno : NSSSD_EOF) ;
    return ;
  }
  print_sp(&sp) ;
}

static inline void do_spnam (void *a)
{
  struct spwd sp ;
  uint32_t len ;
  char buf[4] ;
  get0(buf, 4) ;
  uint32_unpack_big(buf, &len) ;
  if (!len || len > NSSS_SWITCH_NAME_MAXLEN - 1)
  {
    answer(EPROTO) ;
    return ;
  }
  {
    char name[len] ;
    get0(name, len) ;
    if (name[len-1])
    {
      answer(EPROTO) ;
      return ;
    }
    if (!nsssd_shadow_getbyname(a, &sp, name))
    {
      answer(errno ? errno : NSSSD_EOF) ;
      return ;
    }
  }
  print_sp(&sp) ;
}


int nsssd_main (char const *const *argv)
{
  void *a ;

 /* If root, drop privileges to the client's, because shadow */

  if (!geteuid())
  {                                                                   
    uid_t uid ;                                                             
    gid_t gid ;                                                         
    char const *x = getenv("IPCREMOTEEGID") ;                               
    if (!x) strerr_dienotset(100, "IPCREMOTEEGID") ;                       
    if (!gid0_scan(x, &gid)) strerr_dieinvalid(100, "IPCREMOTEEGID") ;      
    if (setgid(gid) == -1) strerr_diefu2sys(111, "setgid to ", x) ;         
    x = getenv("IPCREMOTEEUID") ;                                           
    if (!x) strerr_dienotset(100, "IPCREMOTEEUID") ;                        
    if (!uid0_scan(x, &uid)) strerr_dieinvalid(100, "IPCREMOTEEUID") ;      
    if (setuid(uid) == -1) strerr_diefu2sys(111, "setuid to ", x) ;
  }

  {
    char const *x = getenv("NSSSD_TIMEOUT") ;
    if (x)
    {
      uint32_t t ;
      if (!uint320_scan(x, &t))
        strerr_dief1x(100, "invalid NSSSD_TIMEOUT") ;
      if (t) tain_from_millisecs(&tto, t) ;
    }
  }

  tain_now_set_stopwatch_g() ;                                            
  a = nsssd_handle_init() ;
  if (ndelay_on(0) < 0) strerr_diefu1sys(111, "set stdin non-blocking") ;
  tain_now_g() ;
  if (!nsssd_handle_start(a, argv))
    strerr_diefu1sys(111, "nsssd_handle_start") ;

  for (;;)
  {
    tain deadline ;
    char c ;
    tain_add_g(&deadline, &outertto) ;
    if (!buffer_timed_get_g(buffer_0small, &c, 1, &deadline)) break ;
    errno = 0 ;
    switch (c)
    {
      case NSSS_SWITCH_SET_TIMEOUT : do_set_timeout() ; break ;
      case NSSS_SWITCH_PWD_END : do_pwend(a) ; break ;
      case NSSS_SWITCH_PWD_REWIND : do_pwrewind(a) ; break ;
      case NSSS_SWITCH_PWD_GET : do_pwget(a) ; break ;
      case NSSS_SWITCH_PWD_GETBYNAME : do_pwnam(a) ; break ;
      case NSSS_SWITCH_PWD_GETBYUID : do_pwuid(a) ; break ;
      case NSSS_SWITCH_GRP_END : do_grend(a) ; break ;
      case NSSS_SWITCH_GRP_REWIND : do_grrewind(a) ; break ;
      case NSSS_SWITCH_GRP_GET : do_grget(a) ; break ;
      case NSSS_SWITCH_GRP_GETBYNAME : do_grnam(a) ; break ;
      case NSSS_SWITCH_GRP_GETBYGID : do_grgid(a) ; break ;
      case NSSS_SWITCH_GRP_GETLIST : do_grlist(a) ; break ;
      case NSSS_SWITCH_SHADOW_END : do_spend(a) ; break ;
      case NSSS_SWITCH_SHADOW_REWIND : do_sprewind(a) ; break ;
      case NSSS_SWITCH_SHADOW_GET : do_spget(a) ; break ;
      case NSSS_SWITCH_SHADOW_GETBYNAME : do_spnam(a) ; break ;
      default :
        errno = EPROTO ;
        strerr_diefu1sys(1, "interpret stdin") ;
    }
  }
  nsssd_handle_end(a) ;
  return 0 ;
}
