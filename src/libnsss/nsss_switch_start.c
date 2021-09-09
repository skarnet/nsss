/* ISC license. */

#include <skalibs/buffer.h>
#include <skalibs/djbunix.h>
#include <skalibs/socket.h>

#include <nsss/nsss-switch.h>

static inline int nsss_switch_connect (nsss_switch_t *a, char const *path, tain const *deadline, tain *stamp)
{
  int fd = ipc_stream_nbcoe() ;
  if (fd < 0) return 0 ;
  if (!ipc_timed_connect(fd, path, deadline, stamp))
  {
    fd_close(fd) ;
    return 0 ;
  }
  buffer_init(&a->b, &buffer_read, fd, a->buf, NSSS_SWITCH_BUFSIZE) ;
  return 1 ;
}

int nsss_switch_start (nsss_switch_t *a, unsigned int what, char const *path, tain const *deadline, tain *stamp)
{
  if (!a->held && !nsss_switch_connect(a, path, deadline, stamp)) return 0 ;
  a->held |= what & 0x7u ;
  a->path = path ;
  return 1 ;
}
