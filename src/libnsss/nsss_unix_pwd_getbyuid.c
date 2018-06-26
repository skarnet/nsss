/* ISC license. */

#include <sys/types.h>
#include <nsss/pwd-def.h>
#include <nsss/nsss-unix.h>

int nsss_unix_pwd_getbyuid (nsss_unix_t *a, struct passwd *pw, stralloc *sa, uid_t uid)
{
  struct passwd pw2 ;
  for (;;)
  {
    size_t base = sa->len ;
    if (!nsss_unix_pwd_get(a, &pw2, sa)) return 0 ;
    if (uid == pw2.pw_uid) break ;
    sa->len = base ;
  }
  *pw = pw2 ;
  return 1 ;
}
