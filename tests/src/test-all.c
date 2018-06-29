/* ISC license. */

#include <errno.h>
#include <skalibs/buffer.h>
#include <skalibs/lolstdio.h>
#include <nsss/pwd.h>
#include <nsss/nsss-all.h>

int main (void)
{
  for (;;)
  {
    struct passwd *pw ;
    errno = 0 ;
    pw = nsss_all_getpwent() ;
    if (!pw) break ;
    lolprintf("%s:%s:%d:%d:%s:%s:%s\n", pw->pw_name, pw->pw_passwd, (int)pw->pw_uid, (int)pw->pw_gid, pw->pw_gecos, pw->pw_dir, pw->pw_shell) ;
  }
  if (errno)
    strerr_diefu1sys(111, "nsss_all_getpwent") ;
  nsss_all_endpwent() ;
  buffer_flush(buffer_1) ;
  lolprintf("\n") ;

  for (;;)
  {
    struct group *gr ;
    char **p ;
    errno = 0 ;
    gr = nsss_all_getgrent() ;
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
    strerr_diefu1sys(111, "nsss_all_getgrent") ;
  nsss_all_endgrent() ;
  buffer_flush(buffer_1) ;  
  return 0 ;
}
