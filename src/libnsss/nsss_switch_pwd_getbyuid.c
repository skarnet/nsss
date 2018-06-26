/* ISC license. */

#include <errno.h>
#include <skalibs/uint32.h>
#include <skalibs/buffer.h>
#include <skalibs/unix-timed.h>
#include <nsss/nsss-switch.h>
#include "nsss-switch-internal.h"

int nsss_switch_pwd_getbyuid (nsss_switch_t *a, struct passwd *pw, stralloc *sa, uid_t uid, tain_t const *deadline, tain_t *stamp)
{
  char buf[5] = { NSSS_SWITCH_PWD_GETBYUID } ;
  uint32_pack_big(buf + 1, uid) ;
  if (!ipc_timed_send(buffer_fd(&a->b), buf, 5, deadline, stamp)) return 0 ;
  if (!buffer_timed_get(&a->b, &buf[0], 1, deadline, stamp)) return 0 ;
  if ((unsigned char)buf[0] == 255) return 0 ;
  if (buf[0]) return (errno = buf[0], 0) ;
  return nsss_switch_pwd_read(&a->b, pw, sa, deadline, stamp) ;
}
