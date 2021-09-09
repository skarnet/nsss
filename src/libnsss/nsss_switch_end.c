/* ISC license. */

#include <skalibs/buffer.h>
#include <skalibs/djbunix.h>
#include <nsss/nsss-switch.h>

static inline void nsss_switch_disconnect (nsss_switch_t *a)
{
  fd_close(buffer_fd(&a->b)) ;
  a->b.fd = -1 ;
  a->path = 0 ;
}

void nsss_switch_end (nsss_switch_t *a, unsigned int what)
{
  a->held &= ~(what & 0x7u) ;
  if (!a->held) nsss_switch_disconnect(a) ;
}
