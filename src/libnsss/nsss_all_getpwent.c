/* ISC license. */

#include <errno.h>
#include <nsss/config.h>
#include <nsss/pwd-unix.h>
#include <nsss/pwd-all.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"
#include "nsss-switch-internal.h"
#include "nsss-all-internal.h"

struct passwd *nsss_all_getpwent (void)
{
  int e = errno ;
  if (nsss_all_errno) goto fallback ;
  if (!nsss_switch_start(&nsss_switch_here, NSSS_SWITCH_PWD, NSSS_NSSSD_PATH, 0, 0)) goto efallback ;
  nsss_pwd_sa_here.len = 0 ;
  if (!nsss_switch_pwd_get(&nsss_switch_here, &nsss_pwd_here, &nsss_pwd_sa_here, 0, 0)) return 0 ;
  return &nsss_pwd_here ;

 efallback:
  nsss_all_errno = errno ;
  errno = e ;
 fallback:
  return nsss_unix_getpwent() ;
}
