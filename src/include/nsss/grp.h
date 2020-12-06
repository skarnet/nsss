/* ISC license. */

#ifndef NSSS_GRP_H
#define NSSS_GRP_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef NSSS_DISABLE_SWITCH

#include <nsss/grp-unix.h>

#define setgrent nsss_unix_setgrent
#define getgrent nsss_unix_getgrent
#define getgrent_r nsss_unix_getgrent_r
#define endgrent nsss_unix_endgrent
#define getgrgid nsss_unix_getgrgid
#define getgrgid_r nsss_unix_getgrgid_r
#define getgrnam nsss_unix_getgrnam
#define getgrnam_r nsss_unix_getgrnam_r

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
# define getgrouplist nsss_unix_getgrouplist
#endif

#else
#ifdef NSSS_DISABLE_UNIX

#include <nsss/grp-switch.h>

#define setgrent nsss_switch_setgrent
#define getgrent nsss_switch_getgrent
#define getgrent_r nsss_switch_getgrent_r
#define endgrent nsss_switch_endgrent
#define getgrgid nsss_switch_getgrgid
#define getgrgid_r nsss_switch_getgrgid_r
#define getgrnam nsss_switch_getgrnam
#define getgrnam_r nsss_switch_getgrnam_r

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
# define getgrouplist nsss_switch_getgrouplist
#endif

#else

#include <nsss/grp-all.h>

#define setgrent nsss_all_setgrent
#define getgrent nsss_all_getgrent
#define getgrent_r nsss_all_getgrent_r
#define endgrent nsss_all_endgrent
#define getgrgid nsss_all_getgrgid
#define getgrgid_r nsss_all_getgrgid_r
#define getgrnam nsss_all_getgrnam
#define getgrnam_r nsss_all_getgrnam_r

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
# define getgrouplist nsss_all_getgrouplist
#endif

#endif
#endif

 /*
   The following functions are not implemented by nsss.
   However, the libc may implement them, so we still need to
   declare them. Of course, we only declare functions that
   do not conflict with nsss operation.
 */

#if defined(_GNU_SOURCE) || defined(_DEFAULT_SOURCE)
#include <sys/types.h>
extern int setgroups (size_t, gid_t const *) ;
extern int initgroups (char const *, gid_t) ;
#endif

#ifdef _GNU_SOURCE
#include <stdio.h>
extern struct group *fgetgrent (FILE *) ;
extern int fgetgrent_r (FILE *, struct group *, char *, size_t, struct group **) ;
extern int putgrent (struct group const *, FILE *) ;
#endif

#ifdef __cplusplus
}
#endif

#endif
