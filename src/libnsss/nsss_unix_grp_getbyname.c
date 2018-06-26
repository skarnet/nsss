/* ISC license. */

#include <string.h>
#include <skalibs/genalloc.h>
#include <nsss/grp-def.h>
#include <nsss/nsss-unix.h>

int nsss_unix_grp_getbyname (nsss_unix_t *a, struct group *gr, stralloc *sa, genalloc *ga, char const *name)
{
  struct group gr2 ;
  for (;;)
  {
    size_t sabase = sa->len ;
    size_t gabase = genalloc_len(char *, ga) ;
    if (!nsss_unix_grp_get(a, &gr2, sa, ga)) return 0 ;
    if (!strcmp(name, gr2.gr_name)) break ;
    sa->len = sabase ;
    genalloc_setlen(char *, ga, gabase) ;
  }
  *gr = gr2 ;
  return 1 ;
}
