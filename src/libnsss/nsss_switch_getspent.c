/* ISC license. */

#include <nsss/config.h>
#include <nsss/shadow-switch.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"
#include "nsss-switch-internal.h"

struct spwd *nsss_switch_getspent (void)
{
  if (!nsss_switch_start(&nsss_switch_here, NSSS_SWITCH_SHADOW, NSSS_NSSSD_PATH, 0, 0)) return 0 ;
  nsss_shadow_sa_here.len = 0 ;
  if (!nsss_switch_shadow_get(&nsss_switch_here, &nsss_shadow_here, &nsss_shadow_sa_here, 0, 0)) return 0 ;
  return &nsss_shadow_here ;
}
