/* ISC license. */

#ifndef NSSS_PWD_ALL_H
#define NSSS_PWD_ALL_H

#include <nsss/pwd-def.h>

 /* switch then fallback on unix */

extern void nsss_all_setpwent (void) ;
extern struct passwd *nsss_all_getpwent (void) ;
extern int nsss_all_getpwent_r (struct passwd *, char *, size_t, struct passwd **) ;
extern void nsss_all_endpwent (void) ;

extern struct passwd *nsss_all_getpwuid (uid_t) ;
extern int nsss_all_getpwuid_r (uid_t, struct passwd *, char *, size_t, struct passwd **) ;
extern struct passwd *nsss_all_getpwnam (char const *) ;
extern int nsss_all_getpwnam_r (char const *, struct passwd *, char *, size_t, struct passwd **) ;

#endif
