/* ISC license. */

#include <errno.h>
#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <nsss/grp-unix.h>
#include <nsss/nsss-unix.h>
#include "nsss-internal.h"

int nsss_unix_getgrgid_r (gid_t gid, struct group *gr, char *buf, size_t buflen, struct group **grp)
{
  struct group gr2 ;
  stralloc sa = STRALLOC_ZERO ;
  genalloc ga = GENALLOC_ZERO ;
  nsss_unix_t a = NSSS_UNIX_ZERO ;
  int e = errno ;
  if (!nsss_unix_grp_start(&a)) return errno ;
  errno = 0 ;
  if (!nsss_unix_grp_getbygid(&a, &gr2, &sa, &ga, gid))
  {
    nsss_unix_grp_end(&a) ;
    *grp = 0 ;
    return errno ? errno : (errno = e, 0) ;
  }
  nsss_unix_grp_end(&a) ;
  if (!nsss_grp_copy(gr, buf, buflen, &gr2, sa.s, sa.len, genalloc_s(char *, &ga), genalloc_len(char *, &ga)))
  {
    genalloc_free(char *, &ga) ;
    stralloc_free(&sa) ;
    *grp = 0 ;
    return errno ;
  }
  genalloc_free(char *, &ga) ;
  stralloc_free(&sa) ;
  *grp = gr ;
  return (errno = e, 0) ;
}
