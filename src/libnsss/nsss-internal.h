/* ISC license. */

#ifndef NSSS_INTERNAL_H
#define NSSS_INTERNAL_H

#include <sys/types.h>
#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <nsss/pwd-def.h>
#include <nsss/grp-def.h>
#include <nsss/shadow-def.h>


 /* Password */

extern struct passwd nsss_pwd_here ;
extern stralloc nsss_pwd_sa_here ;
extern int nsss_pwd_copy (struct passwd *, char *, size_t, struct passwd const *, char const *, size_t) ;


 /* Group */

extern struct group nsss_grp_here ;
extern stralloc nsss_grp_sa_here ;
extern genalloc nsss_grp_ga_here ;
extern int nsss_grp_copy (struct group *, char *, size_t, struct group const *, char const *, size_t, char *const *, size_t) ;


 /* Shadow */

extern struct spwd nsss_shadow_here ;
extern stralloc nsss_shadow_sa_here ;
extern int nsss_shadow_copy (struct spwd *, char *, size_t, struct spwd const *, char const *, size_t) ;

#endif
