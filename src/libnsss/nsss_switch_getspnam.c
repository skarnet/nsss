/* ISC license. */

#include <nsss/config.h>
#include <nsss/shadow-switch.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"
#include "nsss-switch-internal.h"

struct spwd *nsss_switch_getspnam (char const *name)
{
  if (!nsss_switch_query_start(NSSS_NSSSD_PATH, NSSS_SWITCH_SHADOW, 30000, 0, 0)) return 0 ;
  nsss_shadow_sa_here.len = 0 ;
  return nsss_switch_shadow_getbyname(&nsss_switch_query, &nsss_shadow_here, &nsss_shadow_sa_here, name, 0, 0) ? &nsss_shadow_here : 0 ;
}
