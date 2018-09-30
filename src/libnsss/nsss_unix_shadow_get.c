/* ISC license. */

#include <pthread.h>
#include <skalibs/types.h>
#include <skalibs/skamisc.h>
#include <nsss/shadow-def.h>
#include <nsss/nsss-unix.h>
#include "nsss-unix-internal.h"

static int lscan (char const *s, long *l)
{
  if (*s) return !!ulong0_scan(s, (unsigned long *)l) ;
  *l = -1 ;
  return 1 ;
}

static inline int shadow_parseline (struct spwd *sp, char *s, size_t max)
{
  struct spwd sp2 ;
  char *p ;
  s[max-1] = 0 ;
  if (!nsss_unix_field(&sp2.sp_namp, &s)) return 0 ;
  if (!nsss_unix_field(&sp2.sp_pwdp, &s)) return 0 ;
  if (!nsss_unix_field(&p, &s)) return 0 ;
  if (!lscan(p, &sp2.sp_lstchg)) return 0 ;
  if (!nsss_unix_field(&p, &s)) return 0 ;
  if (!lscan(p, &sp2.sp_min)) return 0 ;
  if (!nsss_unix_field(&p, &s)) return 0 ;
  if (!lscan(p, &sp2.sp_max)) return 0 ;
  if (!nsss_unix_field(&p, &s)) return 0 ;
  if (!lscan(p, &sp2.sp_warn)) return 0 ;
  if (!nsss_unix_field(&p, &s)) return 0 ;
  if (!lscan(p, &sp2.sp_inact)) return 0 ;
  if (!nsss_unix_field(&p, &s)) return 0 ;
  if (!lscan(p, &sp2.sp_expire)) return 0 ;
  if (!nsss_unix_field(&p, &s)) return 0 ;
  if (!lscan(p, (long *)&sp2.sp_flag)) return 0 ;
  *sp = sp2 ;
  return 1 ;
}

int nsss_unix_shadow_get (nsss_unix_t *a, struct spwd *sp, stralloc *sa)
{
  int cs ;
  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs) ;
  for (;;)
  {
    size_t base = sa->len ;
    if (skagetln_loose(&a->b, sa, '\n') <= 0) goto err ;
    if (shadow_parseline(sp, sa->s + base, sa->len - base)) break ;
    sa->len = base ;
  }
  pthread_setcancelstate(cs, 0) ;
  return 1 ;

 err:
  pthread_setcancelstate(cs, 0) ;
  return 0 ;
}
