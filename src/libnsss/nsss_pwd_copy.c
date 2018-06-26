/* ISC license. */

#include <string.h>
#include <errno.h>
#include "nsss-internal.h"

int nsss_pwd_copy (struct passwd *pw, char *buf, size_t buflen, struct passwd const *pw2, char const *s, size_t len)
{
  if (len > buflen) return (errno = ERANGE, 0) ;
  memcpy(buf, s, len) ;
  pw->pw_name = buf + (pw2->pw_name - s) ;
  pw->pw_passwd = buf + (pw2->pw_passwd - s) ;
  pw->pw_uid = pw2->pw_uid ;
  pw->pw_gid = pw2->pw_gid ;
  pw->pw_gecos = buf + (pw2->pw_gecos - s) ;
  pw->pw_dir = buf + (pw2->pw_dir - s) ;
  pw->pw_shell = buf + (pw2->pw_shell - s) ;
  return 1 ;
}
