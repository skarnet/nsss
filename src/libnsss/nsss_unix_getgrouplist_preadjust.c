/* ISC license. */

#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>

#include <nsss/nsss-unix.h>
#include <nsss/grp-unix.h>

int nsss_unix_getgrouplist_preadjust (char const *user, gid_t *gids, size_t n, size_t *r)
{
  stralloc sa = STRALLOC_ZERO ;
  genalloc ga = GENALLOC_ZERO ;  /* char * */
  nsss_unix_t a = NSSS_UNIX_ZERO ;
  if (!nsss_unix_grp_start(&a)) return 0 ;
  if (!nsss_unix_grp_getlist(&a, user, gids, n, r, &sa, &ga))
  {
    nsss_unix_grp_end(&a) ;
    return 0 ;
  }
  nsss_unix_grp_end(&a) ;
  return 1 ;
}
