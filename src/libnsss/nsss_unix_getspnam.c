/* ISC license. */

#include <nsss/shadow-unix.h>
#include <nsss/nsss-unix.h>
#include "nsss-internal.h"

struct spwd *nsss_unix_getspnam (char const *name)
{
  nsss_unix_t a = NSSS_UNIX_ZERO ;
  if (!nsss_unix_shadow_start(&a)) return 0 ;
  nsss_shadow_sa_here.len = 0 ;
  if (!nsss_unix_shadow_getbyname(&a, &nsss_shadow_here, &nsss_shadow_sa_here, name))
  {
    nsss_unix_shadow_end(&a) ;
    return 0 ;
  }
  nsss_unix_shadow_end(&a) ;
  return &nsss_shadow_here ;
}
