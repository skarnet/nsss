/* ISC license. */

#ifndef NSSS_GRP_SWITCH_H
#define NSSS_GRP_SWITCH_H

#include <nsss/grp-def.h>

 /* Group functions contacting the nsssd daemon */

extern void nsss_switch_setgrent (void) ;
extern struct group *nsss_switch_getgrent (void) ;
extern int nsss_switch_getgrent_r (struct group *, char *, size_t, struct group **) ;
extern void nsss_switch_endgrent (void) ;

extern struct group *nsss_switch_getgrgid (gid_t) ;
extern struct group *nsss_switch_getgrnam (char const *) ;
extern int nsss_switch_getgrgid_r (gid_t, struct group *, char *, size_t, struct group **) ;
extern int nsss_switch_getgrnam_r (char const *, struct group *, char *, size_t, struct group **) ;
extern int nsss_switch_getgrouplist (char const *, gid_t, gid_t *, int *) ;

#endif
