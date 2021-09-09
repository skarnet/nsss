/* ISC license. */

#include <pthread.h>

#include <nsss/grp-switch.h>
#include "nsss-switch-internal.h"

void nsss_switch_endgrent (void)
{
  pthread_mutex_lock(&nsss_switch_enumerator_mutex) ;
  nsss_switch_grp_end(&nsss_switch_enumerator, 0, 0) ;
  nsss_switch_end(&nsss_switch_enumerator, NSSS_SWITCH_GRP) ;
  pthread_mutex_unlock(&nsss_switch_enumerator_mutex) ;
}
