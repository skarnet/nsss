/* ISC license. */

#include <unistd.h>
#include <skalibs/buffer.h>
#include <nsss/nsss-unix.h>

int nsss_unix_rewind (nsss_unix_t *a)
{
  int fd = buffer_fd(&a->b) ;
  if (lseek(fd, 0, SEEK_SET) < 0) return 0 ;
  buffer_init(&a->b, &buffer_read, fd, a->buf, NSSS_UNIX_BUFSIZE) ;
  return 1 ;
}
