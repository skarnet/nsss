/* ISC license. */

#include <string.h>
#include "nsss-unix-internal.h"

int nsss_unix_field (char **field, char **s)
{
  char *p = strchr(*s, ':') ;
  if (!p) return 0 ;
  *p++ = 0 ;
  *field = *s ;
  *s = p ;
  return 1 ;
}
