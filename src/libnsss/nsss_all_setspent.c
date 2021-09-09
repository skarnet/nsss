/* ISC license. */

#include <errno.h>
#include <nsss/config.h>
#include <nsss/shadow-unix.h>
#include <nsss/shadow-all.h>
#include <nsss/nsss-switch.h>
#include "nsss-switch-internal.h"
#include "nsss-all-internal.h"

void nsss_all_setspent (void)
{
  int e = errno ;
  if (!nsss_switch_start(&nsss_switch_enumerator, NSSS_SWITCH_SHADOW, NSSS_NSSSD_PATH, 0, 0)) goto fallback ;
  nsss_switch_shadow_rewind(&nsss_switch_enumerator, 0, 0) ;
  return ;

 fallback:
  nsss_all_errno = errno ;
  errno = e ;
  nsss_unix_setspent() ;
}
