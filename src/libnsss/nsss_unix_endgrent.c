/* ISC license. */

#include <nsss/grp-unix.h>
#include "nsss-unix-internal.h"

void nsss_unix_endgrent (void)
{
  nsss_unix_grp_end(&nsss_unix_grp_here) ;
}
