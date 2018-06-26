/* ISC license. */

#include <string.h>
#include <errno.h>
#include "nsss-internal.h"

int nsss_shadow_copy (struct spwd *sp, char *buf, size_t buflen, struct spwd const *sp2, char const *s, size_t len)
{
  if (len > buflen) return (errno = ERANGE, 0) ;
  memcpy(buf, s, len) ;
  sp->sp_namp = buf + (sp2->sp_namp - s) ;
  sp->sp_pwdp = buf + (sp2->sp_pwdp - s) ;
  sp->sp_lstchg = sp2->sp_lstchg ;
  sp->sp_min = sp2->sp_min ;
  sp->sp_max = sp2->sp_max ;
  sp->sp_warn = sp2->sp_warn ;
  sp->sp_inact = sp2->sp_inact ;
  sp->sp_expire = sp2->sp_expire ;
  sp->sp_flag = sp2->sp_flag ;
  return 1 ;
}
