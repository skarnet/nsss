/* ISC license. */

#include <nsss/pwd-unix.h>
#include <nsss/nsss-unix.h>
#include "nsss-unix-internal.h"

void nsss_unix_setpwent (void)
{
  if (!nsss_unix_pwd_maybe_start(&nsss_unix_pwd_here)) return ;
  nsss_unix_pwd_rewind(&nsss_unix_pwd_here) ;
}
