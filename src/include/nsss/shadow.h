/* ISC license. */

#ifndef NSSS_SHADOW_H
#define NSSS_SHADOW_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef NSSS_DISABLE_SWITCH

#include <nsss/shadow-unix.h>

#define setspent nsss_unix_setspent
#define getspent nsss_unix_getspent
#define getspent_r nsss_unix_getspent_r
#define endspent nsss_unix_endspent
#define getspnam nsss_unix_getspnam
#define getspnam_r nsss_unix_getspnam_r

#else
#ifdef NSSS_DISABLE_UNIX

#include <nsss/shadow-switch.h>

#define setspent nsss_switch_setspent
#define getspent nsss_switch_getspent
#define getspent_r nsss_switch_getspent_r
#define endspent nsss_switch_endspent
#define getspnam nsss_switch_getspnam
#define getspnam_r nsss_switch_getspnam_r

#else

#include <nsss/shadow-all.h>

#define setspent nsss_all_setspent
#define getspent nsss_all_getspent
#define getspent_r nsss_all_getspent_r
#define endspent nsss_all_endspent
#define getspnam nsss_all_getspnam
#define getspnam_r nsss_all_getspnam_r

#endif
#endif


#ifdef __cplusplus
}
#endif

#endif
