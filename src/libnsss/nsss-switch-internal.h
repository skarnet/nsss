/* ISC license. */

#ifndef NSSS_SWITCH_INTERNAL_H
#define NSSS_SWITCH_INTERNAL_H

#include <stddef.h>
#include <sys/uio.h>
#include <pthread.h>

#include <skalibs/tai.h>
#include <skalibs/buffer.h>
#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>

#include <nsss/pwd-def.h>
#include <nsss/grp-def.h>
#include <nsss/shadow-def.h>
#include <nsss/nsss-switch.h>

extern nsss_switch_t nsss_switch_enumerator ;
extern pthread_mutex_t nsss_switch_enumerator_mutex ;

extern nsss_switch_t nsss_switch_query ;
extern pthread_mutex_t nsss_switch_query_mutex ;

extern int nsss_switch_query_start (char const *, unsigned int, unsigned int, tain const *, tain *) ;

extern int nsss_switch_op (nsss_switch_t *, char, tain const *, tain *) ;
extern int nsss_switch_pwd_read (buffer *, struct passwd *, stralloc *, tain const *, tain *) ;
extern int nsss_switch_grp_read (buffer *, struct group *, stralloc *, genalloc *, tain const *, tain *) ;
extern int nsss_switch_shadow_read (buffer *, struct spwd *, stralloc *, tain const *, tain *) ;

extern int nsss_switch_send (nsss_switch_t *, char const *, size_t, tain const *, tain *) ;
extern int nsss_switch_sendv (nsss_switch_t *, struct iovec const *, unsigned int, tain const *, tain *) ;

#endif
