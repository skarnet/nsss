/* ISC license. */

#include <errno.h>
#include <skalibs/buffer.h>
#include <skalibs/unix-timed.h>
#include <nsss/nsss-switch.h>
#include "nsss-switch-internal.h"

int nsss_switch_op (nsss_switch_t *a, char op, tain_t const *deadline, tain_t *stamp)
{
  char c ;
  if (!ipc_timed_send(buffer_fd(&a->b), &op, 1, deadline, stamp)) return 0 ;
  if (!buffer_timed_get(&a->b, &c, 1, deadline, stamp)) return 0 ;
  if (c) return (errno = c, 0) ;
  return 1 ;
}
