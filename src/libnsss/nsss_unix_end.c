/* ISC license. */

#include <skalibs/buffer.h>
#include <skalibs/djbunix.h>
#include <nsss/nsss-unix.h>

void nsss_unix_end (nsss_unix_t *a)
{
  fd_close(buffer_fd(&a->b)) ;
  a->b.fd = -1 ;
}
