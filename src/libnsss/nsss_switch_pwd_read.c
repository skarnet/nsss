/* ISC license. */

#include <stdint.h>
#include <string.h>
#include <errno.h>

#include <skalibs/uint32.h>
#include <skalibs/stralloc.h>
#include <skalibs/unix-timed.h>
#include <skalibs/posixishard.h>

#include <nsss/pwd-def.h>
#include "nsss-switch-internal.h"

/*
   Expects:
     4 bytes pw_uid
     4 bytes pw_gid
     4 bytes total length of strings (including \0's)
     \0-terminated pw_name
     \0-terminated pw_passwd
     \0-terminated pw_gecos
     \0-terminated pw_dir
     \0-terminated pw_shell
*/

int nsss_switch_pwd_read (buffer *b, struct passwd *pw, stralloc *sa, tain const *deadline, tain *stamp)
{
  struct passwd pwtmp ;
  uint32_t total, len, x ;
  char *p ;
  char buf[12] ;
  if (!buffer_timed_get(b, buf, 12, deadline, stamp)) return 0 ;
  uint32_unpack_big(buf, &x) ; pwtmp.pw_uid = x ;
  uint32_unpack_big(buf + 4, &x) ; pwtmp.pw_gid = x ;
  uint32_unpack_big(buf + 8, &total) ;
  if (!stralloc_readyplus(sa, total)) return 0 ;
  if (!buffer_timed_get(b, sa->s + sa->len, total, deadline, stamp)) return 0 ;
  if (sa->s[sa->len + total - 1]) return (errno = EPROTO, 0) ;
  p = sa->s + sa->len ; len = total ;
  pwtmp.pw_name = p ; x = strnlen(p, len) + 1 ; p += x ; len -= x ;
  if (!len) return (errno = EPROTO, 0) ;
  pwtmp.pw_passwd = p ; x = strnlen(p, len) + 1 ; p += x ; len -= x ;
  if (!len) return (errno = EPROTO, 0) ;
  pwtmp.pw_gecos = p ; x = strnlen(p, len) + 1 ; p += x ; len -= x ;
  if (!len) return (errno = EPROTO, 0) ;
  pwtmp.pw_dir = p ; x = strnlen(p, len) + 1 ; p += x ; len -= x ;
  if (!len) return (errno = EPROTO, 0) ;
  pwtmp.pw_shell = p ; x = strnlen(p, len) + 1 ; p += x ; len -= x ;
  if (len) return (errno = EPROTO, 0) ;
  sa->len += total ;
  *pw = pwtmp ;
  return 1 ;
}
