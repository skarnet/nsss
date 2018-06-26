/* ISC license. */

#include <nsss/shadow-unix.h>
#include <nsss/nsss-unix.h>
#include "nsss-unix-internal.h"

void nsss_unix_setspent (void)
{
  if (!nsss_unix_shadow_maybe_start(&nsss_unix_shadow_here)) return ;
  nsss_unix_shadow_rewind(&nsss_unix_shadow_here) ;
}
