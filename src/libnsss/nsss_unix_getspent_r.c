/* ISC license. */

#include <errno.h>
#include <skalibs/stralloc.h>
#include <nsss/shadow-unix.h>
#include <nsss/nsss-unix.h>
#include "nsss-internal.h"
#include "nsss-unix-internal.h"

int nsss_unix_getspent_r (struct spwd *sp, char *buf, size_t buflen, struct spwd **spp)
{
  struct spwd sp2 ;
  stralloc sa = STRALLOC_ZERO ;
  int e ;
  if (!nsss_unix_shadow_maybe_start(&nsss_unix_shadow_here)) return errno ;
  e = errno ;
  errno = 0 ;
  if (!nsss_unix_shadow_get(&nsss_unix_shadow_here, &sp2, &sa))
  {
    *spp = 0 ;
    if (!errno) errno = ENOENT ;
    return errno ;
  }
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
