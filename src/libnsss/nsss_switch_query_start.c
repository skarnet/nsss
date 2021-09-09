/* ISC license. */

#include <nsss/nsss-switch.h>
#include "nsss-switch-internal.h"

int nsss_switch_query_start (char const *path, unsigned int what, unsigned int timeout, tain const *deadline, tain *stamp) 
{
  unsigned int held = nsss_switch_query.held ;
  if (!nsss_switch_start(&nsss_switch_query, what, path, deadline, stamp)) return 0 ;
  if (!held && !nsss_switch_set_timeout(&nsss_switch_query, timeout, deadline, stamp)) return 0 ;
  return 1 ;
}
