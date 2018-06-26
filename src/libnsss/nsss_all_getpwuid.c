/* ISC license. */

#include <errno.h>
#include <nsss/config.h>
#include <nsss/pwd-unix.h>
#include <nsss/pwd-all.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"

struct passwd *nsss_all_getpwuid (uid_t uid)
{
  nsss_switch_t a = NSSS_SWITCH_ZERO ;
  int e = errno ;
  if (!nsss_switch_start(&a, NSSS_SWITCH_PWD, NSSS_NSSSD_PATH, 0, 0)) goto fallback ;
  nsss_pwd_sa_here.len = 0 ;
  if (!nsss_switch_pwd_getbyuid(&a, &nsss_pwd_here, &nsss_pwd_sa_here, uid, 0, 0))
  {
    nsss_switch_end(&a, NSSS_SWITCH_PWD) ;
    return 0 ;
  }
  nsss_switch_end(&a, NSSS_SWITCH_PWD) ;
  return &nsss_pwd_here ;

 fallback:
  errno = e ;
  return nsss_unix_getpwuid(uid) ;
}
