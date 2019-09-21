/* ISC license. */

#include <string.h>
#include <errno.h>

#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>

#include <nsss/grp-unix.h>
#include <nsss/nsss-unix.h>

int nsss_unix_grp_getlist (nsss_unix_t *a, char const *user, gid_t *gids, size_t n, size_t *r, stralloc *sa, genalloc *ga)
{
  int sawasnull = !sa->s ;
  int gawasnull = !genalloc_s(char *, ga) ;
  size_t sabase = sa->len ;
  size_t gabase = genalloc_len(char *, ga) ;
  size_t m = 0 ;

  for (;;)
  {
    struct group gr ;
    sa->len = sabase ;
    genalloc_setlen(char *, ga, gabase) ;
    errno = 0 ;
    if (!nsss_unix_grp_get(a, &gr, sa, ga))
    {
      if (errno) goto err ;
      else break ;
    }
    for (char **p = gr.gr_mem ; *p ; p++)
      if (!strcmp(user, *p))
      {
        if (m < n) gids[m] = gr.gr_gid ;
        m++ ;
        break ;
      }
  }

  if (gawasnull) genalloc_free(char *, ga) ;
  else genalloc_setlen(char *, ga, gabase) ;
  if (sawasnull) stralloc_free(sa) ;
  else sa->len = sabase ;
  *r = m ;
  return 1 ;

 err:
  if (gawasnull) genalloc_free(char *, ga) ;
  else genalloc_setlen(char *, ga, gabase) ;
  if (sawasnull) stralloc_free(sa) ;
  else sa->len = sabase ;
  return 0 ;
}
