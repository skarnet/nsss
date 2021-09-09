/* ISC license. */

#include <sys/types.h>

#include <skalibs/posixplz.h>
#include <skalibs/buffer.h>
#include <skalibs/djbunix.h>

#include <nsss/nsss-switch.h>

static inline pid_t nsss_switch_spawn (nsss_switch_t *a, char const *const *argv, tain const *deadline, tain *stamp)
{
  int fd ;
  pid_t pid = child_spawn1_socket(argv[0], argv, (char const *const *)environ, &fd) ;
  if (!pid) return 0 ;
  buffer_init(&a->b, &buffer_read, fd, a->buf, NSSS_SWITCH_BUFSIZE) ;
  return pid ;
}

int nsss_switch_startf (nsss_switch_t *a, unsigned int what, char const *const *argv, tain const *deadline, tain *stamp)
{
  if (!a->held && !nsss_switch_spawn(a, argv, deadline, stamp)) return 0 ;
  a->held |= what & 0x7u ;
  a->path = 0 ;
  return 1 ;
}
