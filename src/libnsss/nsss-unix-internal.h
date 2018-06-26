/* ISC license. */

#ifndef NSSS_UNIX_INTERNAL_H
#define NSSS_UNIX_INTERNAL_H

#include <nsss/nsss-unix.h>

extern int nsss_unix_field (char **, char **) ;
extern nsss_unix_t nsss_unix_pwd_here ;
extern nsss_unix_t nsss_unix_grp_here ;
extern nsss_unix_t nsss_unix_shadow_here ;

#endif
