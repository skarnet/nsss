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

#endif
#endif


#ifdef __cplusplus
}
#endif

#endif
