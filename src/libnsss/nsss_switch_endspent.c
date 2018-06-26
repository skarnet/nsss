/* ISC license. */

#include <nsss/shadow-switch.h>
#include "nsss-switch-internal.h"

void nsss_switch_endspent (void)
{
  nsss_switch_shadow_end(&nsss_switch_here, 0, 0) ;
  nsss_switch_end(&nsss_switch_here, NSSS_SWITCH_SHADOW) ;
}
