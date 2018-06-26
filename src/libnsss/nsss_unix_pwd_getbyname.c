/* ISC license. */

#include <string.h>
#include <nsss/pwd-def.h>
#include <nsss/nsss-unix.h>

int nsss_unix_pwd_getbyname (nsss_unix_t *a, struct passwd *pw, stralloc *sa, char const *name)
{
  struct passwd pw2 ;
  for (;;)
  {
    size_t base = sa->len ;
    if (!nsss_unix_pwd_get(a, &pw2, sa)) return 0 ;
    if (!strcmp(name, pw2.pw_name)) break ;
    sa->len = base ;
  }
  *pw = pw2 ;
  return 1 ;
}
