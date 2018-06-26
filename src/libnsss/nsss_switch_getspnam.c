/* ISC license. */

#include <nsss/config.h>
#include <nsss/shadow-switch.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"

struct spwd *nsss_switch_getspnam (char const *name)
{
  nsss_switch_t a = NSSS_SWITCH_ZERO ;
  if (!nsss_switch_start(&a, NSSS_SWITCH_SHADOW, NSSS_NSSSD_PATH, 0, 0)) return 0 ;
  nsss_shadow_sa_here.len = 0 ;
  if (!nsss_switch_shadow_getbyname(&a, &nsss_shadow_here, &nsss_shadow_sa_here, name, 0, 0))
  {
    nsss_switch_end(&a, NSSS_SWITCH_SHADOW) ;
    return 0 ;
  }
  nsss_switch_end(&a, NSSS_SWITCH_SHADOW) ;
  return &nsss_shadow_here ;
}
