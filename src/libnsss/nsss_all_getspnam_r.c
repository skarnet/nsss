/* ISC license. */

#include <errno.h>
#include <skalibs/stralloc.h>
#include <nsss/config.h>
#include <nsss/shadow-unix.h>
#include <nsss/shadow-all.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"

int nsss_all_getspnam_r (char const *name, struct spwd *sp, char *buf, size_t buflen, struct spwd **spp)
{
  struct spwd sp2 ;
  stralloc sa = STRALLOC_ZERO ;
  nsss_switch_t a = NSSS_SWITCH_ZERO ;
  int e = errno ;
  if (!nsss_switch_start(&a, NSSS_SWITCH_SHADOW, NSSS_NSSSD_PATH, 0, 0)) goto fallback ;
  errno = 0 ;
  if (!nsss_switch_shadow_getbyname(&a, &sp2, &sa, name, 0, 0))
  {
    nsss_switch_end(&a, NSSS_SWITCH_SHADOW) ;
    *spp = 0 ;
    return errno ? errno : (errno = e, 0) ;
  }
  nsss_switch_end(&a, NSSS_SWITCH_SHADOW) ;
  if (!nsss_shadow_copy(sp, buf, buflen, &sp2, sa.s, sa.len))
  {
    stralloc_free(&sa) ;
    *spp = 0 ;
    return errno ;
  }
  stralloc_free(&sa) ;
  *spp = sp ;
  return (errno = e, 0) ;

 fallback:
  errno = e ;
  return nsss_unix_getspnam_r(name, sp, buf, buflen, spp) ;
}
