/* ISC license. */

#include <skalibs/buffer.h>
#include <skalibs/djbunix.h>
#include <skalibs/webipc.h>
#include <nsss/nsss-switch.h>

static inline int nsss_switch_connect (nsss_switch_t *a, char const *path, tain_t const *deadline, tain_t *stamp)
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

int nsss_switch_start (nsss_switch_t *a, unsigned int what, char const *path, tain_t const *deadline, tain_t *stamp)
{
  if (!a->held && !nsss_switch_connect(a, path, deadline, stamp)) return 0 ;
  a->held |= (1U << what) ;
  return 1 ;
}
