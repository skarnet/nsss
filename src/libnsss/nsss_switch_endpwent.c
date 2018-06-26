/* ISC license. */

#include <nsss/pwd-switch.h>
#include "nsss-switch-internal.h"

void nsss_switch_endpwent (void)
{
  nsss_switch_pwd_end(&nsss_switch_here, 0, 0) ;
  nsss_switch_end(&nsss_switch_here, NSSS_SWITCH_PWD) ;
}
