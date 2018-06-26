/* ISC license. */

#include <errno.h>
#include <skalibs/buffer.h>
#include <skalibs/unix-timed.h>
#include <nsss/nsss-switch.h>
#include "nsss-switch-internal.h"

int nsss_switch_grp_get (nsss_switch_t *a, struct group *gr, stralloc *sa, genalloc *ga, tain_t const *deadline, tain_t *stamp)
{
  char c = NSSS_SWITCH_GRP_GET ;
  if (!ipc_timed_send(buffer_fd(&a->b), &c, 1, deadline, stamp)) return 0 ;
  if (!buffer_timed_get(&a->b, &c, 1, deadline, stamp)) return 0 ;
  if ((unsigned char)c == 255) return 0 ;
  if (c) return (errno = c, 0) ;
  return nsss_switch_grp_read(&a->b, gr, sa, ga, deadline, stamp) ;
}
