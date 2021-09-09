/* ISC license. */

#include <errno.h>
#include <pthread.h>

#include <skalibs/stralloc.h>

#include <nsss/config.h>
#include <nsss/pwd-switch.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"
#include "nsss-switch-internal.h"

int nsss_switch_getpwent_r (struct passwd *pw, char *buf, size_t buflen, struct passwd **pwp)
{
  struct passwd pw2 ;
  stralloc sa = STRALLOC_ZERO ;
  int e = pthread_mutex_lock(&nsss_switch_enumerator_mutex) ;
  if (e) return e ;
  if (!nsss_switch_start(&nsss_switch_enumerator, NSSS_SWITCH_PWD, NSSS_NSSSD_PATH, 0, 0)) goto err ;
  e = errno ;
  errno = 0 ;
  if (!nsss_switch_pwd_get(&nsss_switch_enumerator, &pw2, &sa, 0, 0))
  {
    *pwp = 0 ;
    if (!errno) errno = ENOENT ;
    goto err ;
  }
  pthread_mutex_unlock(&nsss_switch_enumerator_mutex) ;
  if (!nsss_pwd_copy(pw, buf, buflen, &pw2, sa.s, sa.len))
  {
    stralloc_free(&sa) ;
    *pwp = 0 ;
    return errno ;
  }
  stralloc_free(&sa) ;
  *pwp = pw ;
  return (errno = e, 0) ;

 err:
  pthread_mutex_unlock(&nsss_switch_enumerator_mutex) ;
  return errno ;
}
