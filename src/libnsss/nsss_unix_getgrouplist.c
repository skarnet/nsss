/* ISC license. */

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <skalibs/skamisc.h>

#include <nsss/grp-def.h>
#include <nsss/grp-unix.h>
#include <nsss/nsss-unix.h>
#include "nsss-unix-internal.h"

int nsss_unix_getgrouplist (char const *user, gid_t gid, gid_t *gids, int *ngids)
{
  nsss_unix_t a = NSSS_UNIX_ZERO ;
  stralloc sa = STRALLOC_ZERO ;
  genalloc ga = GENALLOC_ZERO ;  /* char * */
  int e = errno ;
  size_t r = 0 ;
  size_t n ;
  if (*ngids < 0) return (errno = EINVAL, -1) ;
  n = *ngids ;
  if (!nsss_unix_grp_start(&a)) return -1 ;
  if (!nsss_unix_grp_getlist(&a, gids, n, &r, &sa, &ga, user)) return -1 ;
  nsss_unix_grp_end(&a) ;
  if (r > INT_MAX) return (errno = EMSGSIZE, -1) ;
  if (r > n) return (*ngids = (int)r, errno = ENOBUFS, -1) ;
  for (size_t i = 0 ; i < r ; i++)
    if (gid == gids[i]) goto ok ;
  r++ ;
  if (r > INT_MAX) return (errno = EMSGSIZE, -1) ;
  if (r > n) return (*ngids = (int)r, errno = ENOBUFS, -1) ;
  memmove(gids + 1, gids, (r-1) * sizeof(gid_t)) ;
  gids[0] = gid ;
 ok:
  *ngids = (int)r ;
  errno = e ;
  return (int)n ;
}
