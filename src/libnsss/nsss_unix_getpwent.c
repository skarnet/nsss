/* ISC license. */

#include <nsss/pwd-unix.h>
#include <nsss/nsss-unix.h>
#include "nsss-internal.h"
#include "nsss-unix-internal.h"

struct passwd *nsss_unix_getpwent (void)
{
  if (!nsss_unix_pwd_maybe_start(&nsss_unix_pwd_here)) return 0 ;
  nsss_pwd_sa_here.len = 0 ;
  if (!nsss_unix_pwd_get(&nsss_unix_pwd_here, &nsss_pwd_here, &nsss_pwd_sa_here)) return 0 ;
  return &nsss_pwd_here ;
}
