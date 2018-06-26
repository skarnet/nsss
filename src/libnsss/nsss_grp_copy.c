/* ISC license. */

#include <stdint.h>
#include <string.h>
#include <errno.h>
#include "nsss-internal.h"

int nsss_grp_copy (struct group *gr, char *buf, size_t buflen, struct group const *gr2, char const *s, size_t len, char *const *p, size_t n)
{
  char **q ;
  size_t offset = (uintptr_t)buf % 16 ;
  offset = offset ? 16 - offset : 0 ;
  if (buflen < offset) return (errno = ERANGE, 0) ;
  buf += offset ; buflen -= offset ;
  offset = (n+1) * sizeof(char *) ;
  if (buflen < offset || buflen - offset < len) return (errno = ERANGE, 0) ;
  q = (char **)buf ;
  gr->gr_mem = q ;
  buf += offset ;
  memcpy(buf, s, len) ;
  for (size_t i = 0 ; i < n ; i++) q[i] = buf + (p[i] - s) ;
  q[n] = 0 ;
  gr->gr_name = buf + (gr2->gr_name - s) ;
  gr->gr_passwd = buf + (gr2->gr_passwd - s) ;
  gr->gr_gid = gr2->gr_gid ;
  return 1 ;
}
