/* ISC license. */

#include <errno.h>
#include <nsss/config.h>
#include <nsss/pwd-unix.h>
#include <nsss/pwd-all.h>
#include <nsss/nsss-switch.h>
#include "nsss-switch-internal.h"
#include "nsss-all-internal.h"

void nsss_all_setpwent (void)
{
  int e = errno ;
  if (!nsss_switch_start(&nsss_switch_here, NSSS_SWITCH_PWD, NSSS_NSSSD_PATH, 0, 0)) goto fallback ;
  nsss_switch_pwd_rewind(&nsss_switch_here, 0, 0) ;
  return ;

 fallback:
  nsss_all_errno = errno ;
  errno = e ;
  nsss_unix_setpwent() ;
}
