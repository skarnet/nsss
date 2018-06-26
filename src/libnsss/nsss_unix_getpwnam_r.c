/* ISC license. */

#include <errno.h>
#include <skalibs/stralloc.h>
#include <nsss/pwd-unix.h>
#include <nsss/nsss-unix.h>
#include "nsss-internal.h"

int nsss_unix_getpwnam_r (char const *name, struct passwd *pw, char *buf, size_t buflen, struct passwd **pwp)
{
  struct passwd pw2 ;
  stralloc sa = STRALLOC_ZERO ;
  nsss_unix_t a = NSSS_UNIX_ZERO ;
  int e = errno ;
  if (!nsss_unix_pwd_start(&a)) return errno ;
  errno = 0 ;
  if (!nsss_unix_pwd_getbyname(&a, &pw2, &sa, name))
  {
    nsss_unix_pwd_end(&a) ;
    *pwp = 0 ;
    return errno ? errno : (errno = e, 0) ;
  }
  nsss_unix_pwd_end(&a) ;
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
