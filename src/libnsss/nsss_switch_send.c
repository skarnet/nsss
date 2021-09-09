/* ISC license. */

#include <errno.h>

#include <skalibs/buffer.h>
#include <skalibs/unix-timed.h>

#include <nsss/nsss-switch.h>
#include "nsss-switch-internal.h"

int nsss_switch_send (nsss_switch_t *a, char const *s, size_t len, tain const *deadline, tain *stamp)
{
  if (!ipc_timed_send(buffer_fd(&a->b), s, len, deadline, stamp))
  {
    unsigned int what ;
    char const *path ;
    if (errno != ECONNRESET || !a->path) return 0 ;
    what = a->held ;
    path = a->path ;
    nsss_switch_end(a, what) ;
    if (!nsss_switch_start(a, what, path, deadline, stamp)) return 0 ;
    if (!ipc_timed_send(buffer_fd(&a->b), s, len, deadline, stamp)) return 0 ;
  }
  return 1 ;
}
