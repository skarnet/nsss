/* ISC license. */

#include <errno.h>
#include <skalibs/stralloc.h>
#include <nsss/pwd-unix.h>
#include <nsss/nsss-unix.h>
#include "nsss-internal.h"
#include "nsss-unix-internal.h"

int nsss_unix_getpwent_r (struct passwd *pw, char *buf, size_t buflen, struct passwd **pwp)
{
  struct passwd pw2 ;
  stralloc sa = STRALLOC_ZERO ;
  int e ;
  if (!nsss_unix_pwd_maybe_start(&nsss_unix_pwd_here)) return errno ;
  e = errno ;
  errno = 0 ;
  if (!nsss_unix_pwd_get(&nsss_unix_pwd_here, &pw2, &sa))
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
