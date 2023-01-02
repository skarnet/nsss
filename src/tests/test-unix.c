/* ISC license. */

#include <errno.h>
#include <skalibs/buffer.h>
#include <skalibs/strerr.h>
#include <skalibs/lolstdio.h>
#include <nsss/pwd-def.h>
#include <nsss/grp-def.h>
#include <nsss/nsss-unix.h>

int main (void)
{
  PROG = "test-unix" ;
  for (;;)
  {
    struct passwd *pw ;
    errno = 0 ;
    pw = nsss_unix_getpwent() ;
    if (!pw) break ;
    lolprintf("%s:%s:%d:%d:%s:%s:%s\n", pw->pw_name, pw->pw_passwd, (int)pw->pw_uid, (int)pw->pw_gid, pw->pw_gecos, pw->pw_dir, pw->pw_shell) ;
  }
  if (errno)
    strerr_diefu1sys(111, "nsss_unix_getpwent") ;
  nsss_unix_endpwent() ;
  lolprintf("\n") ;

  {
    struct passwd *pw = nsss_unix_getpwnam("root") ;
    lolprintf("%u\n\n", (unsigned int)pw->pw_uid) ;
  }

  for (;;)
  {
    struct group *gr ;
    char **p ;
    errno = 0 ;
    gr = nsss_unix_getgrent() ;
    if (!gr) break ;
    p = gr->gr_mem ;
    lolprintf("%s:%s:%d:", gr->gr_name, gr->gr_passwd, (int)gr->gr_gid) ;
    if (*p)
    {
      while (*p) lolprintf("%s,", *p++) ;
      buffer_unput(buffer_1, 1) ;
    }
    buffer_put(buffer_1, "\n", 1) ;
  }
  if (errno)
    strerr_diefu1sys(111, "nsss_unix_getgrent") ;
  nsss_unix_endgrent() ;
  buffer_flush(buffer_1) ;  
  return 0 ;
}
