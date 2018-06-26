/* ISC license. */

#include <skalibs/buffer.h>
#include <skalibs/djbunix.h>
#include <nsss/nsss-unix.h>

int nsss_unix_start (nsss_unix_t *a, char const *path)
{
  int fd = open_readb(path) ;
  if (fd < 0) return 0 ;
  buffer_init(&a->b, &buffer_read, fd, a->buf, NSSS_UNIX_BUFSIZE) ;
  return 1 ;
}
