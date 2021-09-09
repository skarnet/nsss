/* ISC license. */

#include <skalibs/genalloc.h>
#include <nsss/config.h>
#include <nsss/grp-switch.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"
#include "nsss-switch-internal.h"

struct group *nsss_switch_getgrent (void)
{
  if (!nsss_switch_start(&nsss_switch_enumerator, NSSS_SWITCH_GRP, NSSS_NSSSD_PATH, 0, 0)) return 0 ;
  nsss_grp_sa_here.len = 0 ;
  genalloc_setlen(char *, &nsss_grp_ga_here, 0) ;
  if (!nsss_switch_grp_get(&nsss_switch_enumerator, &nsss_grp_here, &nsss_grp_sa_here, &nsss_grp_ga_here, 0, 0)) return 0 ;
  return &nsss_grp_here ;
}
