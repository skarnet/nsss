/* ISC license. */

#include <skalibs/genalloc.h>
#include <nsss/config.h>
#include <nsss/grp-switch.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"

struct group *nsss_switch_getgrgid (gid_t gid)
{
  nsss_switch_t a = NSSS_SWITCH_ZERO ;
  if (!nsss_switch_start(&a, NSSS_SWITCH_GRP, NSSS_NSSSD_PATH, 0, 0)) return 0 ;
  nsss_grp_sa_here.len = 0 ;
  genalloc_setlen(char *, &nsss_grp_ga_here, 0) ;
  if (!nsss_switch_grp_getbygid(&a, &nsss_grp_here, &nsss_grp_sa_here, &nsss_grp_ga_here, gid, 0, 0))
  {
    nsss_switch_end(&a, NSSS_SWITCH_GRP) ;
    return 0 ;
  }
  nsss_switch_end(&a, NSSS_SWITCH_GRP) ;
  return &nsss_grp_here ;
}
