/* ISC license. */

#include <pthread.h>
#include <skalibs/types.h>
#include <skalibs/skamisc.h>
#include <nsss/pwd-def.h>
#include <nsss/nsss-unix.h>
#include "nsss-unix-internal.h"

static inline int pwd_parseline (struct passwd *pw, char *s, size_t max)
{
  struct passwd pw2 ;
  char *p ;
  s[max-1] = 0 ;
  if (!nsss_unix_field(&pw2.pw_name, &s)) return 0 ;
  if (!nsss_unix_field(&pw2.pw_passwd, &s)) return 0 ;
  if (!nsss_unix_field(&p, &s)) return 0 ;
  if (!uid0_scan(p, &pw2.pw_uid)) return 0 ;
  if (!nsss_unix_field(&p, &s)) return 0 ;
  if (!gid0_scan(p, &pw2.pw_gid)) return 0 ;
  if (!nsss_unix_field(&pw2.pw_gecos, &s)) return 0 ;
  if (!nsss_unix_field(&pw2.pw_dir, &s)) return 0 ;
  pw2.pw_shell = s ;
  *pw = pw2 ;
  return 1 ;
}

int nsss_unix_pwd_get (nsss_unix_t *a, struct passwd *pw, stralloc *sa)
{
  int cs ;
  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs) ;
  for (;;)
  {
    size_t base = sa->len ;
    if (skagetln_loose(&a->b, sa, '\n') <= 0) goto err ;
    if (pwd_parseline(pw, sa->s + base, sa->len - base)) break ;
    sa->len = base ;
  }
  pthread_setcancelstate(cs, 0) ;
  return 1 ;

 err:
  pthread_setcancelstate(cs, 0) ;
  return 0 ;
}
