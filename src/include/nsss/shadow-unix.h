/* ISC license. */

#ifndef NSSS_SHADOW_UNIX_H
#define NSSS_SHADOW_UNIX_H

#include <nsss/shadow-def.h>

 /* /etc/shadow functions */

extern void nsss_unix_setspent (void) ;
extern struct spwd *nsss_unix_getspent (void) ;
extern int nsss_unix_getspent_r (struct spwd *, char *, size_t, struct spwd **) ;
extern void nsss_unix_endspent (void) ;

extern struct spwd *nsss_unix_getspnam (char const *) ;
extern int nsss_unix_getspnam_r (char const *, struct spwd *, char *, size_t, struct spwd **) ;

#endif
