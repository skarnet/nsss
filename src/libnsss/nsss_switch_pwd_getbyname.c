/* ISC license. */

#include <string.h>
#include <sys/uio.h>
#include <errno.h>
#include <skalibs/uint32.h>
#include <skalibs/buffer.h>
#include <skalibs/unix-timed.h>
#include <nsss/nsss-switch.h>
#include "nsss-switch-internal.h"

int nsss_switch_pwd_getbyname (nsss_switch_t *a, struct passwd *pw, stralloc *sa, char const *name, tain const *deadline, tain *stamp)
{
  char buf[5] = { NSSS_SWITCH_PWD_GETBYNAME } ;
  size_t len = strlen(name) ;
  struct iovec v[2] = { { .iov_base = buf, .iov_len = 5 }, { .iov_base = (char *)name, .iov_len = len + 1 } } ;
  if (len > NSSS_SWITCH_NAME_MAXLEN - 1) return (errno = EINVAL, 0) ;
  uint32_pack_big(buf + 1, len + 1) ;
  if (!ipc_timed_sendv(buffer_fd(&a->b), v, 2, deadline, stamp)) return 0 ;
  if (!buffer_timed_get(&a->b, &buf[0], 1, deadline, stamp)) return 0 ;
  if ((unsigned char)buf[0] == 255) return 0 ;
  if (buf[0]) return (errno = buf[0], 0) ;
  return nsss_switch_pwd_read(&a->b, pw, sa, deadline, stamp) ;
}
