/* ISC license. */

#include <nsss/shadow-unix.h>
#include <nsss/shadow-switch.h>
#include <nsss/shadow-all.h>
#include "nsss-all-internal.h"

void nsss_all_endspent (void)
{
  if (nsss_all_errno) goto fallback ;
  nsss_switch_endspent() ;
  return ;

 fallback:
  nsss_unix_endspent() ;
  nsss_all_errno = 0 ;
}
