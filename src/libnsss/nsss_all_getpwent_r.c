/* ISC license. */

#include <errno.h>
#include <skalibs/stralloc.h>
#include <nsss/config.h>
#include <nsss/pwd-unix.h>
#include <nsss/pwd-all.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"
#include "nsss-switch-internal.h"
#include "nsss-all-internal.h"

int nsss_all_getpwent_r (struct passwd *pw, char *buf, size_t buflen, struct passwd **pwp)
{
  struct passwd pw2 ;
  stralloc sa = STRALLOC_ZERO ;
  int e = errno ;
  if (nsss_all_errno) goto fallback ;
  if (!nsss_switch_start(&nsss_switch_enumerator, NSSS_SWITCH_PWD, NSSS_NSSSD_PATH, 0, 0)) goto efallback ;
  errno = 0 ;
  if (!nsss_switch_pwd_get(&nsss_switch_enumerator, &pw2, &sa, 0, 0))
  {
    *pwp = 0 ;
    if (!errno) errno = ENOENT ;
    return errno ;
  }
  if (!nsss_pwd_copy(pw, buf, buflen, &pw2, sa.s, sa.len))
  {
    stralloc_free(&sa) ;
    *pwp = 0 ;
    return errno ;
  }
  stralloc_free(&sa) ;
  *pwp = pw ;
  return (errno = e, 0) ;

 efallback:
  nsss_all_errno = errno ;
  errno = e ;
 fallback:
  return nsss_unix_getpwent_r(pw, buf, buflen, pwp) ;
}
