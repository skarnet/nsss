/* ISC license. */

#include <errno.h>
#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <nsss/config.h>
#include <nsss/grp-unix.h>
#include <nsss/grp-all.h>
#include <nsss/nsss-switch.h>
#include "nsss-internal.h"
#include "nsss-switch-internal.h"
#include "nsss-all-internal.h"

int nsss_all_getgrent_r (struct group *gr, char *buf, size_t buflen, struct group **grp)
{
  struct group gr2 ;
  stralloc sa = STRALLOC_ZERO ;
  genalloc ga = GENALLOC_ZERO ;
  int e = errno ;
  if (nsss_all_errno) goto fallback ;
  if (!nsss_switch_start(&nsss_switch_here, NSSS_SWITCH_GRP, NSSS_NSSSD_PATH, 0, 0)) goto efallback ;
  errno = 0 ;
  if (!nsss_switch_grp_get(&nsss_switch_here, &gr2, &sa, &ga, 0, 0))
  {
    *grp = 0 ;
    if (!errno) errno = ENOENT ;
    return errno ;
  }
  if (!nsss_grp_copy(gr, buf, buflen, &gr2, sa.s, sa.len, genalloc_s(char *, &ga), genalloc_len(char *, &ga)))
  {
    stralloc_free(&sa) ;
    *grp = 0 ;
    return errno ;
  }
  stralloc_free(&sa) ;
  *grp = gr ;
  return (errno = e, 0) ;

 efallback:
  nsss_all_errno = errno ;
  errno = e ;
 fallback:
  return nsss_unix_getgrent_r(gr, buf, buflen, grp) ;
}
