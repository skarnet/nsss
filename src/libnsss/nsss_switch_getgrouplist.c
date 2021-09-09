/* ISC license. */

#include <stddef.h>
#include <errno.h>
#include <pthread.h>

#include <skalibs/stralloc.h>

#include <nsss/config.h>
#include <nsss/nsss-switch.h>
#include <nsss/grp-switch.h>
#include "nsss-internal.h"
#include "nsss-switch-internal.h"

int nsss_switch_getgrouplist (char const *user, gid_t gid, gid_t *gids, int *ngids)
{
  stralloc sa = STRALLOC_ZERO ;
  size_t r = 0 ;
  size_t n ;
  int e ;
  if (*ngids < 0) return (errno = EINVAL, -1) ;
  n = *ngids ;
  e = pthread_mutex_lock(&nsss_switch_query_mutex) ;
  if (e) return (errno = e, -1) ; 
  e = errno ;
  if (!nsss_switch_query_start(NSSS_NSSSD_PATH, NSSS_SWITCH_GRP, 30000, 0, 0)
   || !nsss_switch_grp_getlist(&nsss_switch_query, user, gids, n, &r, &sa, 0, 0))
  {
    pthread_mutex_unlock(&nsss_switch_query_mutex) ;
    return -1 ;
  }
  pthread_mutex_unlock(&nsss_switch_query_mutex) ;
  return nsss_grouplist_adjust(n, r, gid, gids, ngids, e) ;
}
