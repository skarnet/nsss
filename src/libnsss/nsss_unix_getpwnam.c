/* ISC license. */

#include <nsss/pwd-unix.h>
#include <nsss/nsss-unix.h>
#include "nsss-internal.h"

struct passwd *nsss_unix_getpwnam (char const *name)
{
  nsss_unix_t a = NSSS_UNIX_ZERO ;
  if (!nsss_unix_pwd_start(&a)) return 0 ;
  nsss_pwd_sa_here.len = 0 ;
  if (!nsss_unix_pwd_getbyname(&a, &nsss_pwd_here, &nsss_pwd_sa_here, name))
  {
    nsss_unix_pwd_end(&a) ;
    return 0 ;
  }
  nsss_unix_pwd_end(&a) ;
  return &nsss_pwd_here ;
}
