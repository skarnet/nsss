/* ISC license. */

#ifndef NSSS_GRP_ALL_H
#define NSSS_GRP_ALL_H

#include <nsss/grp-def.h>

/* switch then fallback on unix */

extern void nsss_all_setgrent (void) ;
extern struct group *nsss_all_getgrent (void) ;
extern int nsss_all_getgrent_r (struct group *, char *, size_t, struct group **) ;
extern void nsss_all_endgrent (void) ;

extern struct group *nsss_all_getgrgid (gid_t) ;
extern struct group *nsss_all_getgrnam (char const *) ;
extern int nsss_all_getgrgid_r (gid_t, struct group *, char *, size_t, struct group **) ;
extern int nsss_all_getgrnam_r (char const *, struct group *, char *, size_t, struct group **) ;
extern int nsss_all_getgrouplist (char const *, gid_t, gid_t *, int *) ;

#endif
