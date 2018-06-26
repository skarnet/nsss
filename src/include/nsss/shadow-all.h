/* ISC license. */

#ifndef NSSS_SHADOW_ALL_H
#define NSSS_SHADOW_ALL_H

#include <nsss/shadow-def.h>

/* switch then fallback on unix */

extern void nsss_all_setspent (void) ;
extern struct spwd *nsss_all_getspent (void) ;
extern int nsss_all_getspent_r (struct spwd *, char *, size_t, struct spwd **) ;
extern void nsss_all_endspent (void) ;

extern struct spwd *nsss_all_getspnam (char const *) ;
extern int nsss_all_getspnam_r (char const *, struct spwd *, char *, size_t, struct spwd **) ;

#endif
