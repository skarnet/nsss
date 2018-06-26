/* ISC license. */

#include <skalibs/genalloc.h>
#include <nsss/grp-unix.h>
#include <nsss/nsss-unix.h>
#include "nsss-internal.h"
#include "nsss-unix-internal.h"

struct group *nsss_unix_getgrent (void)
{
  if (!nsss_unix_grp_maybe_start(&nsss_unix_grp_here)) return 0 ;
  nsss_grp_sa_here.len = 0 ;
  genalloc_setlen(char *, &nsss_grp_ga_here, 0) ;
  if (!nsss_unix_grp_get(&nsss_unix_grp_here, &nsss_grp_here, &nsss_grp_sa_here, &nsss_grp_ga_here)) return 0 ;
  return &nsss_grp_here ;
}
