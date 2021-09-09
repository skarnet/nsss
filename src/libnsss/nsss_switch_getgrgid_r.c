/* ISC license. */

#include <errno.h>
#include <pthread.h>

#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>

#include <nsss/config.h>
#include <nsss/grp-switch.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"
#include "nsss-switch-internal.h"

int nsss_switch_getgrgid_r (gid_t gid, struct group *gr, char *buf, size_t buflen, struct group **grp)
{
  struct group gr2 ;
  stralloc sa = STRALLOC_ZERO ;
  genalloc ga = GENALLOC_ZERO ;
  int e = pthread_mutex_lock(&nsss_switch_query_mutex) ;
  if (e) return e ;
  e = errno ;
  if (!nsss_switch_query_start(NSSS_NSSSD_PATH, NSSS_SWITCH_GRP, 30000, 0, 0))
  {
    pthread_mutex_unlock(&nsss_switch_query_mutex) ;
    return errno ;
  }
  errno = 0 ;
  if (!nsss_switch_grp_getbygid(&nsss_switch_query, &gr2, &sa, &ga, gid, 0, 0))
  {
    pthread_mutex_unlock(&nsss_switch_query_mutex) ;
    *grp = 0 ;
    return errno ? errno : (errno = e, 0) ;
  }
  pthread_mutex_unlock(&nsss_switch_query_mutex) ;
  if (!nsss_grp_copy(gr, buf, buflen, &gr2, sa.s, sa.len, genalloc_s(char *, &ga), genalloc_len(char *, &ga)))
  {
    genalloc_free(char *, &ga) ;
    stralloc_free(&sa) ;
    *grp = 0 ;
    return errno ;
  }
  genalloc_free(char *, &ga) ;
  stralloc_free(&sa) ;
  *grp = gr ;
  return (errno = e, 0) ;
}
