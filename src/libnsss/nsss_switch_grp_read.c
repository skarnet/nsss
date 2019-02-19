/* ISC license. */


#include <stdint.h>
#include <string.h>
#include <errno.h>

#include <skalibs/posixishard.h>
#include <skalibs/uint32.h>
#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <skalibs/unix-timed.h>
#include <nsss/grp-def.h>
#include "nsss-switch-internal.h"

/*
   Expects:
     4 bytes gr_gid
     4 bytes total length of strings (including \0's)
     4 bytes number of strings in gr_mem (n)
     \0-terminated gr_name
     \0-terminated gr_passwd
     sequence of n \0-terminated elements in gr_mem
*/

int nsss_switch_grp_read (buffer *b, struct group *gr, stralloc *sa, genalloc *ga, tain_t const *deadline, tain_t *stamp)
{
  struct group grtmp ;
  uint32_t total, len, n, x ;
  char **q ;
  char *p ;
  char buf[12] ;
  if (!buffer_timed_get(b, buf, 12, deadline, stamp)) return 0 ;
  uint32_unpack_big(buf, &x) ; grtmp.gr_gid = x ;
  uint32_unpack_big(buf + 4, &total) ;
  uint32_unpack_big(buf + 8, &n) ;
  if (total < 2 || n >= 0x30000000u) return (errno = EPROTO, 0) ;
  if (!stralloc_readyplus(sa, total)) return 0 ;
  if (!genalloc_readyplus(char *, ga, n+1)) return 0 ;
  if (!buffer_timed_get(b, sa->s + sa->len, total, deadline, stamp)) return 0 ;
  if (sa->s[sa->len + total - 1]) return (errno = EPROTO, 0) ;
  p = sa->s + sa->len ; len = total ;
  q = genalloc_s(char *, ga) + genalloc_len(char *, ga) ;
  grtmp.gr_mem = q ;
  grtmp.gr_name = p ; x = strnlen(p, len) + 1 ; p += x ; len -= x ;
  if (!len) return (errno = EPROTO, 0) ;
  grtmp.gr_passwd = p ; x = strnlen(p, len) + 1 ; p += x ; len -= x ;
  for (uint32_t i = 0 ; i < n ; i++)
  {
    if (!len) return (errno = EPROTO, 0) ;
    q[i] = p ; x = strnlen(p, len) + 1 ; p += x ; len -= x ;
  }
  if (len) return (errno = EPROTO, 0) ;
  q[n] = 0 ;
  sa->len += total ;
  genalloc_setlen(char *, ga, genalloc_len(char *, ga) + n + 1) ;
  *gr = grtmp ;
  return 1 ;
}
