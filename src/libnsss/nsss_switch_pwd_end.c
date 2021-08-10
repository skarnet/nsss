/* ISC license. */

#include <nsss/nsss-switch.h>
#include "nsss-switch-internal.h"

int nsss_switch_pwd_end (nsss_switch_t *a, tain const *deadline, tain *stamp)
{
  return nsss_switch_op(a, NSSS_SWITCH_PWD_END, deadline, stamp) ;
}
