/* ISC license. */

#include <nsss/pwd-unix.h>
#include <nsss/nsss-unix.h>
#include "nsss-internal.h"

struct passwd *nsss_unix_getpwuid (uid_t uid)
{
  nsss_unix_t a = NSSS_UNIX_ZERO ;
  if (!nsss_unix_pwd_start(&a)) return 0 ;
  nsss_pwd_sa_here.len = 0 ;
  if (!nsss_unix_pwd_getbyuid(&a, &nsss_pwd_here, &nsss_pwd_sa_here, uid))
  {
    nsss_unix_pwd_end(&a) ;
    return 0 ;
  }
  nsss_unix_pwd_end(&a) ;
  return &nsss_pwd_here ;
}
