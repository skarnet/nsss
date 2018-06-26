/* ISC license. */

#include <errno.h>
#include <skalibs/stralloc.h>
#include <nsss/config.h>
#include <nsss/shadow-switch.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"
#include "nsss-switch-internal.h"

int nsss_switch_getspent_r (struct spwd *sp, char *buf, size_t buflen, struct spwd **spp)
{
  struct spwd sp2 ;
  stralloc sa = STRALLOC_ZERO ;
  int e ;
  if (!nsss_switch_start(&nsss_switch_here, NSSS_SWITCH_SHADOW, NSSS_NSSSD_PATH, 0, 0)) return errno ;
  e = errno ;
  errno = 0 ;
  if (!nsss_switch_shadow_get(&nsss_switch_here, &sp2, &sa, 0, 0))
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
