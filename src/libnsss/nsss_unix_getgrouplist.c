/* ISC license. */

#include <stddef.h>
#include <errno.h>

#include <nsss/nsss-unix.h>
#include <nsss/grp-unix.h>
#include "nsss-internal.h"

int nsss_unix_getgrouplist (char const *user, gid_t gid, gid_t *gids, int *ngids)
{
  int e = errno ;
  size_t r = 0 ;
  size_t n ;
  if (*ngids < 0) return (errno = EINVAL, -1) ;
  n = *ngids ;
  if (!nsss_unix_getgrouplist_preadjust(user, gids, n, &r)) return -1 ;
  return nsss_grouplist_adjust(n, r, gid, gids, ngids, e) ;
}
