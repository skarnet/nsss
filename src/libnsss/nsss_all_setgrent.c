/* ISC license. */

#include <errno.h>
#include <nsss/config.h>
#include <nsss/grp-unix.h>
#include <nsss/grp-all.h>
#include <nsss/nsss-switch.h>
#include "nsss-switch-internal.h"
#include "nsss-all-internal.h"

void nsss_all_setgrent (void)
{
  int e = errno ;
  if (!nsss_switch_start(&nsss_switch_enumerator, NSSS_SWITCH_GRP, NSSS_NSSSD_PATH, 0, 0)) goto fallback ;
  nsss_switch_grp_rewind(&nsss_switch_enumerator, 0, 0) ;
  return ;

 fallback:
  nsss_all_errno = errno ;
  errno = e ;
  nsss_unix_setgrent() ;
}
