/* ISC license. */

#include <stdint.h>
#include <errno.h>

#include <skalibs/uint32.h>
#include <skalibs/unix-timed.h>

#include <nsss/nsss-switch.h>
#include "nsss-switch-internal.h"

int nsss_switch_set_timeout (nsss_switch_t *a, unsigned int t, tain const *deadline, tain *stamp)
{
  char buf[5] = { NSSS_SWITCH_SET_TIMEOUT } ;
  uint32_pack_big(buf + 1, (uint32_t)t) ;
  if (!nsss_switch_send(a, buf, 5, deadline, stamp)) return 0 ;
  if (!buffer_timed_get(&a->b, &buf[0], 1, deadline, stamp)) return 0 ;
  if ((unsigned char)buf[0] == 255) return 0 ;
  if (buf[0]) return (errno = (unsigned char)buf[0], 0) ;
  return 1 ;
}
