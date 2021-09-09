/* ISC license. */

#include <nsss/config.h>
#include <nsss/pwd-switch.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"
#include "nsss-switch-internal.h"

struct passwd *nsss_switch_getpwnam (char const *name)
{
  if (!nsss_switch_query_start(NSSS_NSSSD_PATH, NSSS_SWITCH_PWD, 30000, 0, 0)) return 0 ;
  nsss_pwd_sa_here.len = 0 ;
  return nsss_switch_pwd_getbyname(&nsss_switch_query, &nsss_pwd_here, &nsss_pwd_sa_here, name, 0, 0) ? &nsss_pwd_here : 0 ;
}
