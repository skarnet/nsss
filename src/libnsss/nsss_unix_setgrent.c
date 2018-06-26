/* ISC license. */

#include <nsss/grp-unix.h>
#include <nsss/nsss-unix.h>
#include "nsss-unix-internal.h"

void nsss_unix_setgrent (void)
{
  if (!nsss_unix_grp_maybe_start(&nsss_unix_grp_here)) return ;
  nsss_unix_grp_rewind(&nsss_unix_grp_here) ;
}
