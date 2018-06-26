/* ISC license. */

#include <nsss/config.h>
#include <nsss/pwd-switch.h>
#include <nsss/nsss-switch.h>
#include "nsss-switch-internal.h"

void nsss_switch_setpwent (void)
{
  if (!nsss_switch_start(&nsss_switch_here, NSSS_SWITCH_PWD, NSSS_NSSSD_PATH, 0, 0)) return ;
  nsss_switch_pwd_rewind(&nsss_switch_here, 0, 0) ;
}
