/* ISC license. */

#include <errno.h>

#include <skalibs/unix-timed.h>

#include <nsss/nsss-switch.h>
#include "nsss-switch-internal.h"

int nsss_switch_op (nsss_switch_t *a, char op, tain const *deadline, tain *stamp)
{
  unsigned char c ;
  if (!nsss_switch_send(a, &op, 1, deadline, stamp)) return 0 ;
  if (!buffer_timed_get(&a->b, (char *)&c, 1, deadline, stamp)) return 0 ;
  if (c) return (errno = c, 0) ;
  return 1 ;
}
