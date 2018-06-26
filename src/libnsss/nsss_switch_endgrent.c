/* ISC license. */

#include <nsss/grp-switch.h>
#include "nsss-switch-internal.h"

void nsss_switch_endgrent (void)
{
  nsss_switch_grp_end(&nsss_switch_here, 0, 0) ;
  nsss_switch_end(&nsss_switch_here, NSSS_SWITCH_GRP) ;
}
