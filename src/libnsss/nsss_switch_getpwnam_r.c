/* ISC license. */

#include <errno.h>
#include <pthread.h>

#include <skalibs/stralloc.h>

#include <nsss/config.h>
#include <nsss/pwd-switch.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"
#include "nsss-switch-internal.h"

int nsss_switch_getpwnam_r (char const *name, struct passwd *pw, char *buf, size_t buflen, struct passwd **pwp)
{
  struct passwd pw2 ;
  stralloc sa = STRALLOC_ZERO ;
  int e = pthread_mutex_lock(&nsss_switch_query_mutex) ;
  if (e) return e ;
  e = errno ;
  if (!nsss_switch_query_start(NSSS_NSSSD_PATH, NSSS_SWITCH_PWD, 30000, 0, 0))
  {
    pthread_mutex_unlock(&nsss_switch_query_mutex) ;
    return errno ;
  }
  errno = 0 ;
  if (!nsss_switch_pwd_getbyname(&nsss_switch_query, &pw2, &sa, name, 0, 0))
  {
    pthread_mutex_unlock(&nsss_switch_query_mutex) ;
    *pwp = 0 ;
    return errno ? errno : (errno = e, 0) ;
  }
  pthread_mutex_unlock(&nsss_switch_query_mutex) ;
  if (!nsss_pwd_copy(pw, buf, buflen, &pw2, sa.s, sa.len))
  {
    stralloc_free(&sa) ;
    *pwp = 0 ;
    return errno ;
  }
  stralloc_free(&sa) ;
  *pwp = pw ;
  return (errno = e, 0) ;
}
