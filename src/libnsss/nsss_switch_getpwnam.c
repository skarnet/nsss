/* ISC license. */

#include <nsss/config.h>
#include <nsss/pwd-switch.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"

struct passwd *nsss_switch_getpwnam (char const *name)
{
  nsss_switch_t a = NSSS_SWITCH_ZERO ;
  if (!nsss_switch_start(&a, NSSS_SWITCH_PWD, NSSS_NSSSD_PATH, 0, 0)) return 0 ;
  nsss_pwd_sa_here.len = 0 ;
  if (!nsss_switch_pwd_getbyname(&a, &nsss_pwd_here, &nsss_pwd_sa_here, name, 0, 0))
  {
    nsss_switch_end(&a, NSSS_SWITCH_PWD) ;
    return 0 ;
  }
  nsss_switch_end(&a, NSSS_SWITCH_PWD) ;
  return &nsss_pwd_here ;
}
