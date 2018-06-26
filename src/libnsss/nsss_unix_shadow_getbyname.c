/* ISC license. */

#include <string.h>
#include <nsss/shadow-def.h>
#include <nsss/nsss-unix.h>

int nsss_unix_shadow_getbyname (nsss_unix_t *a, struct spwd *sp, stralloc *sa, char const *name)
{
  struct spwd sp2 ;
  for (;;)
  {
    size_t base = sa->len ;
    if (!nsss_unix_shadow_get(a, &sp2, sa)) return 0 ;
    if (!strcmp(name, sp2.sp_namp)) break ;
    sa->len = base ;
  }
  *sp = sp2 ;
  return 1 ;
}
