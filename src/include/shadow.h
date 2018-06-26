/* ISC license. */

/*
  This file is part of the nsss package.
  See https://skarnet.org/software/nsss/
*/

#ifndef SHADOW_H
#define SHADOW_H

#include <nsss/shadow.h>

#include <stdio.h>

extern struct spwd *fgetspent (FILE *) ;
extern struct spwd *sgetspent (char const *) ;
extern int putspent (struct spwd const *, FILE *) ;
extern int lckpwdf (void) ;
extern int ulckpwdf (void) ;

#ifdef _DEFAULT_SOURCE
extern int fgetspent_r(FILE *, struct spwd *, char *, size_t, struct spwd **) ;
extern int sgetspent_r (char const *, struct spwd *, char *, size_t, struct spwd **) ;
#endif

#endif
