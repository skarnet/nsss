/* ISC license. */

#include <nsss/pwd-unix.h>
#include <nsss/pwd-switch.h>
#include <nsss/pwd-all.h>
#include "nsss-all-internal.h"

void nsss_all_endpwent (void)
{
  if (nsss_all_errno) goto fallback ;
  nsss_switch_endpwent() ;
  return ;

 fallback:
  nsss_unix_endpwent() ;
  nsss_all_errno = 0 ;
}
