/* ISC license. */

#include <pthread.h>

#include <nsss/nsss-switch.h>
#include "nsss-switch-internal.h"

nsss_switch_t nsss_switch_enumerator = NSSS_SWITCH_ZERO ;
pthread_mutex_t nsss_switch_enumerator_mutex = PTHREAD_MUTEX_INITIALIZER ;
