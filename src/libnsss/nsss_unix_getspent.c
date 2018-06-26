/* ISC license. */

#include <nsss/shadow-unix.h>
#include <nsss/nsss-unix.h>
#include "nsss-internal.h"
#include "nsss-unix-internal.h"

struct spwd *nsss_unix_getspent (void)
{
  if (!nsss_unix_shadow_maybe_start(&nsss_unix_shadow_here)) return 0 ;
  nsss_shadow_sa_here.len = 0 ;
  if (!nsss_unix_shadow_get(&nsss_unix_shadow_here, &nsss_shadow_here, &nsss_shadow_sa_here)) return 0 ;
  return &nsss_shadow_here ;
}
