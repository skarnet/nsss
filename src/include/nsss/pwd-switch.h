/* ISC license. */

#ifndef NSSS_PWD_SWITCH_H
#define NSSS_PWD_SWITCH_H

#include <nsss/pwd-def.h>

 /* Password functions contacting the nsssd daemon */

extern void nsss_switch_setpwent (void) ;
extern struct passwd *nsss_switch_getpwent (void) ;
extern int nsss_switch_getpwent_r (struct passwd *, char *, size_t, struct passwd **) ;
extern void nsss_switch_endpwent (void) ;

extern struct passwd *nsss_switch_getpwuid (uid_t) ;
extern int nsss_switch_getpwuid_r (uid_t, struct passwd *, char *, size_t, struct passwd **) ;
extern struct passwd *nsss_switch_getpwnam (char const *) ;
extern int nsss_switch_getpwnam_r (char const *, struct passwd *, char *, size_t, struct passwd **) ;

#endif
