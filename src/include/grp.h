/* ISC license. */

/*
  This file is part of the nsss package.
  See https://skarnet.org/software/nsss/
*/

#ifndef GRP_H
#define GRP_H

#include <nsss/grp.h>

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
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

#endif
