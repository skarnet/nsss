/* ISC license. */

#include <errno.h>
#include <skalibs/buffer.h>
#include <skalibs/strerr.h>
#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <skalibs/lolstdio.h>
#include <skalibs/tai.h>
#include <nsss/pwd-def.h>
#include <nsss/grp-def.h>
#include <nsss/nsss-switch.h>

#define S "./.test-switch-socket"

int main (void)
{
  nsss_switch_t a = NSSS_SWITCH_ZERO ;
  stralloc sa = STRALLOC_ZERO ;
  genalloc ga = GENALLOC_ZERO ;
  tain deadline ;
  PROG = "test-switch" ;
  tain_now_set_stopwatch_g() ;
  tain_from_millisecs(&deadline, 10000) ;
  tain_add_g(&deadline, &deadline) ;

  if (!nsss_switch_start_g(&a, NSSS_SWITCH_PWD, S, &deadline))
    strerr_diefu1sys(111, "nsss_switch_start") ;

  for (;;)
  {
    struct passwd pw ;
    errno = 0 ;
    if (!nsss_switch_pwd_get_g(&a, &pw, &sa, &deadline)) break ;
    lolprintf("%s:%s:%d:%d:%s:%s:%s\n", pw.pw_name, pw.pw_passwd, (int)pw.pw_uid, (int)pw.pw_gid, pw.pw_gecos, pw.pw_dir, pw.pw_shell) ;
    sa.len = 0 ;
  }
  if (errno)
    strerr_diefu1sys(111, "nsss_switch_pwd_get") ;
  if (!nsss_switch_pwd_end_g(&a, &deadline))
    strerr_diefu1sys(111, "nsss_switch_pwd_end") ;
  lolprintf("\n") ;

  {
    struct passwd pw ;
    if (!nsss_switch_pwd_getbyname_g(&a, &pw, &sa, "root", &deadline))
      strerr_diefu1sys(111, "nsss_switch_pwd_getbyname") ;
    lolprintf("%u\n\n", (unsigned int)pw.pw_uid) ;
    sa.len = 0 ;
  }

  if (!nsss_switch_start_g(&a, NSSS_SWITCH_GRP, S, &deadline))
    strerr_diefu1sys(111, "nsss_switch_start") ;
  nsss_switch_end(&a, NSSS_SWITCH_PWD) ;
  buffer_flush(buffer_1) ;

  for (;;)
  {
    struct group gr ;
    char **p ;
    errno = 0 ;
    if (!nsss_switch_grp_get_g(&a, &gr, &sa, &ga, &deadline)) break ;
    p = gr.gr_mem ;
    lolprintf("%s:%s:%d:", gr.gr_name, gr.gr_passwd, (int)gr.gr_gid) ;
    buffer_flush(buffer_1) ;
    if (*p)
    {
      while (*p) lolprintf("%s,", *p++) ;
      buffer_unput(buffer_1, 1) ;
    }
    buffer_put(buffer_1, "\n", 1) ;
    sa.len = 0 ;
    genalloc_setlen(char *, &ga, 0) ;
  }
  if (errno)
    strerr_diefu1sys(111, "nsss_switch_grp_get") ;
  if (!nsss_switch_grp_end_g(&a, &deadline))
    strerr_diefu1sys(111, "nsss_switch_grp_end") ;
  nsss_switch_end(&a, NSSS_SWITCH_GRP) ;

  buffer_flush(buffer_1) ;  
  return 0 ;
}
