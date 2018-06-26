/* ISC license. */

#include <errno.h>
#include <skalibs/genalloc.h>
#include <nsss/config.h>
#include <nsss/grp-unix.h>
#include <nsss/grp-all.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"

struct group *nsss_all_getgrnam (char const *name)
{
  nsss_switch_t a = NSSS_SWITCH_ZERO ;
  int e = errno ;
  if (!nsss_switch_start(&a, NSSS_SWITCH_GRP, NSSS_NSSSD_PATH, 0, 0)) goto fallback ;
  nsss_grp_sa_here.len = 0 ;
  genalloc_setlen(char *, &nsss_grp_ga_here, 0) ;
  if (!nsss_switch_grp_getbyname(&a, &nsss_grp_here, &nsss_grp_sa_here, &nsss_grp_ga_here, name, 0, 0))
  {
    nsss_switch_end(&a, NSSS_SWITCH_GRP) ;
    return 0 ;
  }
  nsss_switch_end(&a, NSSS_SWITCH_GRP) ;
  return &nsss_grp_here ;

 fallback:
  errno = e ;
  return nsss_unix_getgrnam(name) ;
}
