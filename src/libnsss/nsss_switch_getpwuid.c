/* ISC license. */

#include <nsss/config.h>
#include <nsss/pwd-switch.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"
#include "nsss-switch-internal.h"

struct passwd *nsss_switch_getpwuid (uid_t uid)
{
  if (!nsss_switch_query_start(NSSS_NSSSD_PATH, NSSS_SWITCH_PWD, 30000, 0, 0)) return 0 ;
  nsss_pwd_sa_here.len = 0 ;
  return nsss_switch_pwd_getbyuid(&nsss_switch_query, &nsss_pwd_here, &nsss_pwd_sa_here, uid, 0, 0) ? &nsss_pwd_here : 0 ;
}
