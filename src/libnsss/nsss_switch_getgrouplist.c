/* ISC license. */

#include <stddef.h>
#include <errno.h>

#include <skalibs/stralloc.h>

#include <nsss/config.h>
#include <nsss/nsss-switch.h>
#include <nsss/grp-switch.h>
#include "nsss-internal.h"

int nsss_switch_getgrouplist (char const *user, gid_t gid, gid_t *gids, int *ngids)
{
  stralloc sa = STRALLOC_ZERO ;
  int e = errno ;
  size_t r = 0 ;
  size_t n ;
  nsss_switch_t a = NSSS_SWITCH_ZERO ;
  if (*ngids < 0) return (errno = EINVAL, -1) ;
  n = *ngids ;
  if (!nsss_switch_start(&a, NSSS_SWITCH_GRP, NSSS_NSSSD_PATH, 0, 0)) return -1 ;
  if (!nsss_switch_grp_getlist(&a, user, gids, n, &r, &sa, 0, 0))
  {
    nsss_switch_end(&a, NSSS_SWITCH_GRP) ;
    return -1 ;
  }
  nsss_switch_end(&a, NSSS_SWITCH_GRP) ;
  return nsss_grouplist_adjust(n, r, gid, gids, ngids, e) ;
}
