/* ISC license. */

#include <errno.h>
#include <nsss/config.h>
#include <nsss/shadow-unix.h>
#include <nsss/shadow-all.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"

struct spwd *nsss_all_getspnam (char const *name)
{
  nsss_switch_t a = NSSS_SWITCH_ZERO ;
  int e = errno ;
  if (!nsss_switch_start(&a, NSSS_SWITCH_SHADOW, NSSS_NSSSD_PATH, 0, 0)) goto fallback ;
  nsss_shadow_sa_here.len = 0 ;
  if (!nsss_switch_shadow_getbyname(&a, &nsss_shadow_here, &nsss_shadow_sa_here, name, 0, 0))
  {
    nsss_switch_end(&a, NSSS_SWITCH_SHADOW) ;
    return 0 ;
  }
  nsss_switch_end(&a, NSSS_SWITCH_SHADOW) ;
  return &nsss_shadow_here ;

 fallback:
  errno = e ;
  return nsss_unix_getspnam(name) ;
}
