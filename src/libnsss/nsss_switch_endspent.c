/* ISC license. */

#include <pthread.h>

#include <nsss/shadow-switch.h>
#include "nsss-switch-internal.h"

void nsss_switch_endspent (void)
{
  pthread_mutex_lock(&nsss_switch_enumerator_mutex) ;
  nsss_switch_shadow_end(&nsss_switch_enumerator, 0, 0) ;
  nsss_switch_end(&nsss_switch_enumerator, NSSS_SWITCH_SHADOW) ;
  pthread_mutex_unlock(&nsss_switch_enumerator_mutex) ;
}
