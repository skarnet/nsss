/* ISC license. */

#include <errno.h>
#include <nsss/config.h>
#include <nsss/shadow-unix.h>
#include <nsss/shadow-all.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"
#include "nsss-switch-internal.h"
#include "nsss-all-internal.h"

struct spwd *nsss_all_getspent (void)
{
  int e = errno ;
  if (nsss_all_errno) goto fallback ;
  if (!nsss_switch_start(&nsss_switch_here, NSSS_SWITCH_SHADOW, NSSS_NSSSD_PATH, 0, 0)) goto efallback ;
  nsss_shadow_sa_here.len = 0 ;
  if (!nsss_switch_shadow_get(&nsss_switch_here, &nsss_shadow_here, &nsss_shadow_sa_here, 0, 0)) return 0 ;
  return &nsss_shadow_here ;

 efallback:
  nsss_all_errno = errno ;
  errno = e ;
 fallback:
  return nsss_unix_getspent() ;
}
