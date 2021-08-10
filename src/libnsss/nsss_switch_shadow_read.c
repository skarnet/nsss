/* ISC license. */

#include <stdint.h>
#include <string.h>
#include <errno.h>

#include <skalibs/uint32.h>
#include <skalibs/uint64.h>
#include <skalibs/stralloc.h>
#include <skalibs/unix-timed.h>
#include <skalibs/posixishard.h>

#include <nsss/shadow-def.h>
#include "nsss-switch-internal.h"

/*
   Expects:
     8 bytes sp_lstchg
     8 bytes sp_min
     8 bytes sp_max
     8 bytes sp_warn
     8 bytes sp_inact
     8 bytes sp_expire
     8 bytes sp_flag
     4 bytes total length of strings (including \0's)
     \0-terminated sp_namp
     \0-terminated sp_pwdp
*/

int nsss_switch_shadow_read (buffer *b, struct spwd *sp, stralloc *sa, tain const *deadline, tain *stamp)
{
  struct spwd sptmp ;
  uint64_t x ;
  uint32_t total, len ;
  char *p ;
  char buf[60] ;
  if (!buffer_timed_get(b, buf, 60, deadline, stamp)) return 0 ;
  uint64_unpack_big(buf, &x) ; sptmp.sp_lstchg = x ;
  uint64_unpack_big(buf + 8, &x) ; sptmp.sp_min = x ;
  uint64_unpack_big(buf + 16, &x) ; sptmp.sp_max = x ;
  uint64_unpack_big(buf + 24, &x) ; sptmp.sp_warn = x ;
  uint64_unpack_big(buf + 32, &x) ; sptmp.sp_inact = x ;
  uint64_unpack_big(buf + 40, &x) ; sptmp.sp_expire = x ;
  uint64_unpack_big(buf + 48, &x) ; sptmp.sp_flag = x ;
  uint32_unpack_big(buf + 56, &total) ;
  if (!stralloc_readyplus(sa, total)) return 0 ;
  if (!buffer_timed_get(b, sa->s + sa->len, total, deadline, stamp)) return 0 ;
  if (sa->s[sa->len + total - 1]) return (errno = EPROTO, 0) ;
  p = sa->s + sa->len ; len = total ;
  sptmp.sp_namp = p ; x = strnlen(p, len) + 1 ; p += x ; len -= x ;
  if (!len) return (errno = EPROTO, 0) ;
  sptmp.sp_pwdp = p ; x = strnlen(p, len) + 1 ; p += x ; len -= x ;
  if (len) return (errno = EPROTO, 0) ;
  sa->len += total ;
  *sp = sptmp ;
  return 1 ;
}
