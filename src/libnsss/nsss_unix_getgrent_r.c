/* ISC license. */

#include <errno.h>
#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <nsss/grp-unix.h>
#include <nsss/nsss-unix.h>
#include "nsss-internal.h"
#include "nsss-unix-internal.h"

int nsss_unix_getgrent_r (struct group *gr, char *buf, size_t buflen, struct group **grp)
{
  struct group gr2 ;
  stralloc sa = STRALLOC_ZERO ;
  genalloc ga = GENALLOC_ZERO ;
  int e ;
  if (!nsss_unix_grp_maybe_start(&nsss_unix_grp_here)) return errno ;
  e = errno ;
  errno = 0 ;
  if (!nsss_unix_grp_get(&nsss_unix_grp_here, &gr2, &sa, &ga))
  {
    *grp = 0 ;
    if (!errno) errno = ENOENT ;
    return errno ;
  }
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
