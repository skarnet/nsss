/* ISC license. */

#include <skalibs/genalloc.h>
#include <nsss/grp-unix.h>
#include <nsss/nsss-unix.h>
#include "nsss-internal.h"

struct group *nsss_unix_getgrnam (char const *name)
{
  nsss_unix_t a = NSSS_UNIX_ZERO ;
  if (!nsss_unix_grp_start(&a)) return 0 ;
  nsss_grp_sa_here.len = 0 ;
  genalloc_setlen(char *, &nsss_grp_ga_here, 0) ;
  if (!nsss_unix_grp_getbyname(&a, &nsss_grp_here, &nsss_grp_sa_here, &nsss_grp_ga_here, name))
  {
    nsss_unix_grp_end(&a) ;
    return 0 ;
  }
  nsss_unix_grp_end(&a) ;
  return &nsss_grp_here ;
}
