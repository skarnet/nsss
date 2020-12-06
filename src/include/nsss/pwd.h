/* ISC license. */

#ifndef NSSS_PWD_H
#define NSSS_PWD_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef NSSS_DISABLE_SWITCH

#include <nsss/pwd-unix.h>

#define setpwent nsss_unix_setpwent
#define getpwent nsss_unix_getpwent
#define getpwent_r nsss_unix_getpwent_r
#define endpwent nsss_unix_endpwent
#define getpwuid nsss_unix_getpwuid
#define getpwuid_r nsss_unix_getpwuid_r
#define getpwnam nsss_unix_getpwnam
#define getpwnam_r nsss_unix_getpwnam_r

#else
#ifdef NSSS_DISABLE_UNIX

#include <nsss/pwd-switch.h>

#define setpwent nsss_switch_setpwent
#define getpwent nsss_switch_getpwent
#define getpwent_r nsss_switch_getpwent_r
#define endpwent nsss_switch_endpwent
#define getpwuid nsss_switch_getpwuid
#define getpwuid_r nsss_switch_getpwuid_r
#define getpwnam nsss_switch_getpwnam
#define getpwnam_r nsss_switch_getpwnam_r

#else

#include <nsss/pwd-all.h>

#define setpwent nsss_all_setpwent
#define getpwent nsss_all_getpwent
#define getpwent_r nsss_all_getpwent_r
#define endpwent nsss_all_endpwent
#define getpwuid nsss_all_getpwuid
#define getpwuid_r nsss_all_getpwuid_r
#define getpwnam nsss_all_getpwnam
#define getpwnam_r nsss_all_getpwnam_r

#endif
#endif

 /*
   The following functions are not implemented by nsss.
   However, the libc may implement them, so we still need to
   declare them. Of course, we only declare functions that
   do not conflict with nsss operation.
 */

#ifdef _GNU_SOURCE
#include <stdio.h>
extern struct passwd *fgetpwent (FILE *) ;
extern int fgetpwent_r (FILE *, struct passwd *, char *, size_t, struct passwd **) ;
extern int putpwent (struct passwd const *, FILE *) ;
#endif

#ifdef __cplusplus
}
#endif

#endif
