/* ISC license. */

#ifndef NSSS_SWITCH_INTERNAL_H
#define NSSS_SWITCH_INTERNAL_H

#include <skalibs/tai.h>
#include <skalibs/buffer.h>
#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <nsss/pwd-def.h>
#include <nsss/grp-def.h>
#include <nsss/shadow-def.h>
#include <nsss/nsss-switch.h>

extern nsss_switch_t nsss_switch_here ;
extern int nsss_switch_op (nsss_switch_t *, char, tain_t const *, tain_t *) ;
extern int nsss_switch_pwd_read (buffer *, struct passwd *, stralloc *, tain_t const *, tain_t *) ;
extern int nsss_switch_grp_read (buffer *, struct group *, stralloc *, genalloc *, tain_t const *, tain_t *) ;
extern int nsss_switch_shadow_read (buffer *, struct spwd *, stralloc *, tain_t const *, tain_t *) ;

#endif
