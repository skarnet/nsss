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

 /*
   The following functions are not implemented by nsss.
   However, the libc may implement them, so we still need to
   declare them. Of course, we only declare functions that
   do not conflict with nsss operation.
 */

#define SHADOW "/etc/shadow"

#include <stdio.h>

extern struct spwd *fgetspent (FILE *) ;
extern struct spwd *sgetspent (char const *) ;
extern int putspent (struct spwd const *, FILE *) ;
extern int lckpwdf (void) ;
extern int ulckpwdf (void) ;

#ifdef _DEFAULT_SOURCE
extern int fgetspent_r(FILE *, struct spwd *, char *, size_t, struct spwd **) ;
extern int sgetspent_r (char const *, struct spwd *, char *, size_t, struct spwd **) ;
#endif

#ifdef __cplusplus
}
#endif

#endif
