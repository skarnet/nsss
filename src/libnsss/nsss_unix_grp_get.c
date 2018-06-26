/* ISC license. */

#include <string.h>
#include <pthread.h>
#include <skalibs/types.h>
#include <skalibs/genalloc.h>
#include <skalibs/skamisc.h>
#include <nsss/grp-def.h>
#include <nsss/nsss-unix.h>
#include "nsss-unix-internal.h"

static inline char **grp_parsemem (char *s, genalloc *ga)
{
  char **grmem ;
  char **p ;
  size_t n = 0 ;
  for (char *t = s ; *t ; t++) if (*t == ',') { n++ ; *t = 0 ; } ;
  if (*s) n++ ;
  if (!genalloc_readyplus(char *, ga, n+1)) return 0 ;
  p = genalloc_s(char *, ga) + genalloc_len(char *, ga) ;
  grmem = p ;
  for (size_t i = 0 ; i < n ; i++) { *p++ = s ; s += strlen(s) + 1 ; }
  *p++ = 0 ;
  genalloc_setlen(char *, ga, genalloc_len(char *, ga) + n+1) ;
  return grmem ;
}

static inline int grp_parseline (struct group *gr, char *s, size_t max, genalloc *ga)
{
  struct group gr2 ;
  char *p ;
  s[max-1] = 0 ;
  if (!nsss_unix_field(&gr2.gr_name, &s)) return 0 ;
  if (!nsss_unix_field(&gr2.gr_passwd, &s)) return 0 ;
  if (!nsss_unix_field(&p, &s)) return 0 ;
  if (!gid0_scan(p, &gr2.gr_gid)) return 0 ;
  gr2.gr_mem = grp_parsemem(s, ga) ;
  if (!gr2.gr_mem) return 0 ;
  *gr = gr2 ;
  return 1 ;
}

int nsss_unix_grp_get (nsss_unix_t *a, struct group *gr, stralloc *sa, genalloc *ga)
{
  int cs ;
  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs) ;
  for (;;)
  {
    size_t sabase = sa->len ;
    size_t gabase = genalloc_len(char *, ga) ;
    if (skagetln_loose(&a->b, sa, '\n') <= 0) goto err ;
    if (grp_parseline(gr, sa->s + sabase, sa->len - sabase, ga)) break ;
    sa->len = sabase ;
    genalloc_setlen(char *, ga, gabase) ;
  }
  pthread_setcancelstate(cs, 0) ;
  return 1 ;

 err:
  pthread_setcancelstate(cs, 0) ;
  return 0 ;
}
