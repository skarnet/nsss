/* ISC license. */

#ifndef NSSS_GRP_UNIX_H
#define NSSS_GRP_UNIX_H

#include <nsss/grp-def.h>

 /* /etc/group backend */

extern void nsss_unix_setgrent (void) ;
extern struct group *nsss_unix_getgrent (void) ;
extern int nsss_unix_getgrent_r (struct group *, char *, size_t, struct group **) ;
extern void nsss_unix_endgrent (void) ;

extern struct group *nsss_unix_getgrgid (gid_t) ;
extern struct group *nsss_unix_getgrnam (char const *) ;
extern int nsss_unix_getgrgid_r (gid_t, struct group *, char *, size_t, struct group **) ;
extern int nsss_unix_getgrnam_r (char const *, struct group *, char *, size_t, struct group **) ;

#endif
