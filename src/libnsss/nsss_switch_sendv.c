/* ISC license. */

#include <errno.h>

#include <skalibs/buffer.h>
#include <skalibs/unix-timed.h>

#include <nsss/nsss-switch.h>
#include "nsss-switch-internal.h"

int nsss_switch_sendv (nsss_switch_t *a, struct iovec const *v, unsigned int n, tain const *deadline, tain *stamp)
{
  if (!ipc_timed_sendv(buffer_fd(&a->b), v, n, deadline, stamp))
  {
    unsigned int what ;
    char const *path ;
    if (errno != ECONNRESET || !a->path) return 0 ;
    what = a->held ;
    path = a->path ;
    nsss_switch_end(a, what) ;
    if (!nsss_switch_start(a, what, path, deadline, stamp)) return 0 ;
    if (!ipc_timed_sendv(buffer_fd(&a->b), v, n, deadline, stamp)) return 0 ;
  }
  return 1 ;
}
