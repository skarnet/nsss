/* ISC license. */

#include <nsss/nsss-switch.h>
#include "nsss-switch-internal.h"

int nsss_switch_shadow_rewind (nsss_switch_t *a, tain_t const *deadline, tain_t *stamp)
{
  return nsss_switch_op(a, NSSS_SWITCH_SHADOW_REWIND, deadline, stamp) ;
}
