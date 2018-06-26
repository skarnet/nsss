/* ISC license. */

#include <errno.h>
#include <skalibs/genalloc.h>
#include <nsss/config.h>
#include <nsss/grp-unix.h>
#include <nsss/grp-all.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"
#include "nsss-switch-internal.h"
#include "nsss-all-internal.h"

struct group *nsss_all_getgrent (void)
{
  int e = errno ;
  if (nsss_all_errno) goto fallback ;
  if (!nsss_switch_start(&nsss_switch_here, NSSS_SWITCH_GRP, NSSS_NSSSD_PATH, 0, 0)) goto efallback ;
  nsss_grp_sa_here.len = 0 ;
  genalloc_setlen(char *, &nsss_grp_ga_here, 0) ;
  if (!nsss_switch_grp_get(&nsss_switch_here, &nsss_grp_here, &nsss_grp_sa_here, &nsss_grp_ga_here, 0, 0)) return 0 ;
  return &nsss_grp_here ;

 efallback:
  nsss_all_errno = errno ;
  errno = e ;
 fallback:
  return nsss_unix_getgrent() ;
}
