/* ISC license. */

#include <nsss/pwd-unix.h>
#include "nsss-unix-internal.h"

void nsss_unix_endpwent (void)
{
  nsss_unix_pwd_end(&nsss_unix_pwd_here) ;
}
