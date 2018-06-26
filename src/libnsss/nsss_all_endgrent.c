/* ISC license. */

#include <nsss/grp-unix.h>
#include <nsss/grp-switch.h>
#include <nsss/grp-all.h>
#include "nsss-all-internal.h"

void nsss_all_endgrent (void)
{
  if (nsss_all_errno) goto fallback ;
  nsss_switch_endgrent() ;
  return ;

 fallback:
  nsss_unix_endgrent() ;
  nsss_all_errno = 0 ;
}
