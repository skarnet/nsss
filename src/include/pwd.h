/* ISC license. */

/*
  This file is part of the nsss package.
  See https://skarnet.org/software/nsss/
*/

#ifndef PWD_H
#define PWD_H

#include <nsss/pwd.h>

#ifdef _GNU_SOURCE
#include <stdio.h>
extern struct passwd *fgetpwent (FILE *) ;
extern int fgetpwent_r (FILE *, struct passwd *, char *, size_t, struct passwd **) ;
extern int putpwent (struct passwd const *, FILE *) ;
#endif

#endif
