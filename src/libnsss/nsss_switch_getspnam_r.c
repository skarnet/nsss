/* ISC license. */

#include <errno.h>
#include <pthread.h>

#include <skalibs/stralloc.h>

#include <nsss/config.h>
#include <nsss/shadow-switch.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"
#include "nsss-switch-internal.h"

int nsss_switch_getspnam_r (char const *name, struct spwd *sp, char *buf, size_t buflen, struct spwd **spp)
{
  struct spwd sp2 ;
  stralloc sa = STRALLOC_ZERO ;
  int e = pthread_mutex_lock(&nsss_switch_query_mutex) ;
  if (e) return e ;
  e = errno ;
  if (!nsss_switch_query_start(NSSS_NSSSD_PATH, NSSS_SWITCH_SHADOW, 30000, 0, 0))
  {
    pthread_mutex_unlock(&nsss_switch_query_mutex) ;
    return errno ;
  }
  errno = 0 ;
  if (!nsss_switch_shadow_getbyname(&nsss_switch_query, &sp2, &sa, name, 0, 0))
  {
    pthread_mutex_unlock(&nsss_switch_query_mutex) ;
    *spp = 0 ;
    return errno ? errno : (errno = e, 0) ;
  }
  pthread_mutex_unlock(&nsss_switch_query_mutex) ;
  if (!nsss_shadow_copy(sp, buf, buflen, &sp2, sa.s, sa.len))
  {
    stralloc_free(&sa) ;
    *spp = 0 ;
    return errno ;
  }
  stralloc_free(&sa) ;
  *spp = sp ;
  return (errno = e, 0) ;
}
