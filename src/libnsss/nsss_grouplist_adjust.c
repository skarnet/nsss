/* ISC license. */

#include <string.h>
#include <errno.h>
#include <limits.h>

#include <nsss/grp-def.h>
#include "nsss-internal.h"

int nsss_grouplist_adjust (size_t n, size_t r, gid_t gid, gid_t *gids, int *ngids, int e)
{
  if (r > INT_MAX) return (errno = EMSGSIZE, -1) ;
  if (r > n) return (*ngids = (int)r, errno = ENOBUFS, -1) ;
  for (size_t i = 0 ; i < r ; i++) if (gid == gids[i]) goto ok ;
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
