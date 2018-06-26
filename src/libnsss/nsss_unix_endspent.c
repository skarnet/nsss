/* ISC license. */

#include <nsss/shadow-unix.h>
#include "nsss-unix-internal.h"

void nsss_unix_endspent (void)
{
  nsss_unix_shadow_end(&nsss_unix_shadow_here) ;
}
