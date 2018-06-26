/* ISC license. */

#ifndef NSSS_SHADOW_DEF_H
#define NSSS_SHADOW_DEF_H

#include <sys/types.h>

struct spwd
{
  char *sp_namp ;
  char *sp_pwdp ;
  long sp_lstchg ;
  long sp_min ;
  long sp_max ;
  long sp_warn ;
  long sp_inact ;
  long sp_expire ;
  unsigned long sp_flag ;
} ;

#endif
