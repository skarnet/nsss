/* ISC license. */

#include <errno.h>
#include <skalibs/stralloc.h>
#include <nsss/config.h>
#include <nsss/shadow-unix.h>
#include <nsss/shadow-all.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"
#include "nsss-switch-internal.h"
#include "nsss-all-internal.h"

int nsss_all_getspent_r (struct spwd *sp, char *buf, size_t buflen, struct spwd **spp)
{
  struct spwd sp2 ;
  stralloc sa = STRALLOC_ZERO ;
  int e = errno ;
  if (nsss_all_errno) goto fallback ;
  if (!nsss_switch_start(&nsss_switch_enumerator, NSSS_SWITCH_SHADOW, NSSS_NSSSD_PATH, 0, 0)) goto efallback ;
  errno = 0 ;
  if (!nsss_switch_shadow_get(&nsss_switch_enumerator, &sp2, &sa, 0, 0))
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

 efallback:
  nsss_all_errno = errno ;
  errno = e ;
 fallback:
  return nsss_unix_getspent_r(sp, buf, buflen, spp) ;
}
