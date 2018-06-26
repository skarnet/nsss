/* ISC license. */

#include <errno.h>
#include <skalibs/stralloc.h>
#include <nsss/config.h>
#include <nsss/pwd-switch.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"

int nsss_switch_getpwnam_r (char const *name, struct passwd *pw, char *buf, size_t buflen, struct passwd **pwp)
{
  struct passwd pw2 ;
  stralloc sa = STRALLOC_ZERO ;
  nsss_switch_t a = NSSS_SWITCH_ZERO ;
  int e = errno ;
  if (!nsss_switch_start(&a, NSSS_SWITCH_PWD, NSSS_NSSSD_PATH, 0, 0)) return errno ;
  errno = 0 ;
  if (!nsss_switch_pwd_getbyname(&a, &pw2, &sa, name, 0, 0))
  {
    nsss_switch_end(&a, NSSS_SWITCH_PWD) ;
    *pwp = 0 ;
    return errno ? errno : (errno = e, 0) ;
  }
  nsss_switch_end(&a, NSSS_SWITCH_PWD) ;
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
