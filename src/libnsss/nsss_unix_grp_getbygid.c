/* ISC license. */

#include <sys/types.h>
#include <skalibs/genalloc.h>
#include <nsss/grp-def.h>
#include <nsss/nsss-unix.h>

int nsss_unix_grp_getbygid (nsss_unix_t *a, struct group *gr, stralloc *sa, genalloc *ga, gid_t gid)
{
  struct group gr2 ;
  for (;;)
  {
    size_t sabase = sa->len ;
    size_t gabase = genalloc_len(char *, ga) ;
    if (!nsss_unix_grp_get(a, &gr2, sa, ga)) return 0 ;
    if (gid == gr2.gr_gid) break ;
    sa->len = sabase ;
    genalloc_setlen(char *, ga, gabase) ;
  }
  *gr = gr2 ;
  return 1 ;
}
