/* ISC license. */

#ifndef NSSS_PWD_UNIX_H
#define NSSS_PWD_UNIX_H

#include <nsss/pwd-def.h>

 /* /etc/passwd backend */

extern void nsss_unix_setpwent (void) ;
extern struct passwd *nsss_unix_getpwent (void) ;
extern int nsss_unix_getpwent_r (struct passwd *, char *, size_t, struct passwd **) ;
extern void nsss_unix_endpwent (void) ;

extern struct passwd *nsss_unix_getpwuid (uid_t) ;
extern int nsss_unix_getpwuid_r (uid_t, struct passwd *, char *, size_t, struct passwd **) ;
extern struct passwd *nsss_unix_getpwnam (char const *) ;
extern int nsss_unix_getpwnam_r (char const *, struct passwd *, char *, size_t, struct passwd **) ;

#endif
