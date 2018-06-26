/* ISC license. */

#include <errno.h>
#include <skalibs/stralloc.h>
#include <nsss/shadow-unix.h>
#include <nsss/nsss-unix.h>
#include "nsss-internal.h"

int nsss_unix_getspnam_r (char const *name, struct spwd *sp, char *buf, size_t buflen, struct spwd **spp)
{
  struct spwd sp2 ;
  stralloc sa = STRALLOC_ZERO ;
  nsss_unix_t a = NSSS_UNIX_ZERO ;
  int e = errno ;
  if (!nsss_unix_shadow_start(&a)) return errno ;
  errno = 0 ;
  if (!nsss_unix_shadow_getbyname(&a, &sp2, &sa, name))
  {
    nsss_unix_shadow_end(&a) ;
    *spp = 0 ;
    return errno ? errno : (errno = e, 0) ;
  }
  nsss_unix_shadow_end(&a) ;
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
