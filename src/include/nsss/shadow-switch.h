/* ISC license. */

#ifndef NSSS_SHADOW_SWITCH_H
#define NSSS_SHADOW_SWITCH_H

#include <nsss/shadow-def.h>

 /* Shadow functions contacting the nsssd daemon */

extern void nsss_switch_setspent (void) ;
extern struct spwd *nsss_switch_getspent (void) ;
extern int nsss_switch_getspent_r (struct spwd *, char *, size_t, struct spwd **) ;
extern void nsss_switch_endspent (void) ;

extern struct spwd *nsss_switch_getspnam (char const *) ;
extern int nsss_switch_getspnam_r (char const *, struct spwd *, char *, size_t, struct spwd **) ;

#endif
