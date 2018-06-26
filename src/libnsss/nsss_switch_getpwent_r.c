/* ISC license. */

#include <errno.h>
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
  int e ;
  if (!nsss_switch_start(&nsss_switch_here, NSSS_SWITCH_PWD, NSSS_NSSSD_PATH, 0, 0)) return errno ;
  e = errno ;
  errno = 0 ;
  if (!nsss_switch_pwd_get(&nsss_switch_here, &pw2, &sa, 0, 0))
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
}
