/* ISC license. */

#include <nsss/config.h>
#include <nsss/pwd-switch.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"
#include "nsss-switch-internal.h"

struct passwd *nsss_switch_getpwent (void)
{
  if (!nsss_switch_start(&nsss_switch_enumerator, NSSS_SWITCH_PWD, NSSS_NSSSD_PATH, 0, 0)) return 0 ;
  nsss_pwd_sa_here.len = 0 ;
  if (!nsss_switch_pwd_get(&nsss_switch_enumerator, &nsss_pwd_here, &nsss_pwd_sa_here, 0, 0)) return 0 ;
  return &nsss_pwd_here ;
}
