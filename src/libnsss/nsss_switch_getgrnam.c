/* ISC license. */

#include <skalibs/genalloc.h>

#include <nsss/config.h>
#include <nsss/grp-switch.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"
#include "nsss-switch-internal.h"

struct group *nsss_switch_getgrnam (char const *name)
{
  if (!nsss_switch_query_start(NSSS_NSSSD_PATH, NSSS_SWITCH_GRP, 30000, 0, 0)) return 0 ;
  nsss_grp_sa_here.len = 0 ;
  genalloc_setlen(char *, &nsss_grp_ga_here, 0) ;
  return nsss_switch_grp_getbyname(&nsss_switch_query, &nsss_grp_here, &nsss_grp_sa_here, &nsss_grp_ga_here, name, 0, 0) ? &nsss_grp_here : 0 ;
}
