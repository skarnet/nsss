/* ISC license. */

#include <skalibs/buffer.h>
#include <skalibs/djbunix.h>
#include <nsss/nsss-switch.h>

static inline void nsss_switch_disconnect (nsss_switch_t *a)
{
  fd_close(buffer_fd(&a->b)) ;
  a->b.fd = -1 ;
}

void nsss_switch_end (nsss_switch_t *a, unsigned int what)
{
  a->held &= ~(1U << what) ;
  if (!a->held) nsss_switch_disconnect(a) ;
}
