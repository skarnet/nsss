/* ISC license. */

#ifndef NSSS_SWITCH_H
#define NSSS_SWITCH_H

#include <sys/types.h>
#include <limits.h>
#include <unistd.h>
#include <skalibs/tai.h>
#include <skalibs/buffer.h>
#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <nsss/pwd-switch.h>
#include <nsss/grp-switch.h>
#include <nsss/shadow-switch.h>

#define NSSS_SWITCH_BUFSIZE 4096

#ifdef LOGIN_NAME_MAX
#define NSSS_SWITCH_NAME_MAXLEN LOGIN_NAME_MAX
#else
#define NSSS_SWITCH_NAME_MAXLEN _SC_LOGIN_NAME_MAX
#endif

typedef struct nsss_switch_s nsss_switch_t, *nsss_switch_t_ref ;
struct nsss_switch_s
{
  unsigned int held ;
  buffer b ;
  char buf[NSSS_SWITCH_BUFSIZE] ;
} ;
#define NSSS_SWITCH_ZERO { .held = 0, .b = BUFFER_ZERO }

#define NSSS_SWITCH_PWD 0
#define NSSS_SWITCH_GRP 1
#define NSSS_SWITCH_SHADOW 2

extern int nsss_switch_start (nsss_switch_t *, unsigned int, char const *, tain_t const *, tain_t *) ;
#define nsss_switch_start_g(a, what, s, deadline) nsss_switch_start(a, what, s, (deadline), &STAMP)
extern void nsss_switch_end (nsss_switch_t *, unsigned int) ;


 /* Password */

#define NSSS_SWITCH_PWD_END '\0'
#define NSSS_SWITCH_PWD_REWIND '\001'
#define NSSS_SWITCH_PWD_GET '\002'
#define NSSS_SWITCH_PWD_GETBYNAME '\003'
#define NSSS_SWITCH_PWD_GETBYUID '\004'

extern int nsss_switch_pwd_end (nsss_switch_t *, tain_t const *, tain_t *) ;
#define nsss_switch_pwd_end_g(a, deadline) nsss_switch_pwd_end(a, (deadline), &STAMP)
extern int nsss_switch_pwd_rewind (nsss_switch_t *, tain_t const *, tain_t *) ;
#define nsss_switch_pwd_rewind_g(a, deadline) nsss_switch_pwd_rewind(a, (deadline), &STAMP)
extern int nsss_switch_pwd_get (nsss_switch_t *, struct passwd *, stralloc *, tain_t const *, tain_t *) ;
#define nsss_switch_pwd_get_g(a, b, sa, deadline) nsss_switch_pwd_get(a, b, sa, (deadline), &STAMP)
extern int nsss_switch_pwd_getbyname (nsss_switch_t *, struct passwd *, stralloc *, char const *, tain_t const *, tain_t *) ;
#define nsss_switch_pwd_getbyname_g(a, b, sa, name, deadline) nsss_switch_pwd_getbyname(a, b, sa, name, (deadline), &STAMP)
extern int nsss_switch_pwd_getbyuid (nsss_switch_t *, struct passwd *, stralloc *, uid_t, tain_t const *, tain_t *) ;
#define nsss_switch_pwd_getbyuid_g(a, b, sa, u, deadline) nsss_switch_pwd_getbyuid(a, b, sa, u, (deadline), &STAMP)


 /* Group */

#define NSSS_SWITCH_GRP_END '\020'
#define NSSS_SWITCH_GRP_REWIND '\021'
#define NSSS_SWITCH_GRP_GET '\022'
#define NSSS_SWITCH_GRP_GETBYNAME '\023'
#define NSSS_SWITCH_GRP_GETBYGID '\024'
#define NSSS_SWITCH_GRP_GETLIST '\025'

extern int nsss_switch_grp_end (nsss_switch_t *, tain_t const *, tain_t *) ;
#define nsss_switch_grp_end_g(a, deadline) nsss_switch_grp_end(a, (deadline), &STAMP)
extern int nsss_switch_grp_rewind (nsss_switch_t *, tain_t const *, tain_t *) ;
#define nsss_switch_grp_rewind_g(a, deadline) nsss_switch_grp_rewind(a, (deadline), &STAMP)
extern int nsss_switch_grp_get (nsss_switch_t *, struct group *, stralloc *, genalloc *, tain_t const *, tain_t *) ;
#define nsss_switch_grp_get_g(a, b, sa, ga, deadline) nsss_switch_grp_get(a, b, sa, ga, (deadline), &STAMP)
extern int nsss_switch_grp_getbyname (nsss_switch_t *, struct group *, stralloc *, genalloc *, char const *, tain_t const *, tain_t *) ;
#define nsss_switch_grp_getbyname_g(a, b, sa, ga, name, deadline) nsss_switch_grp_getbyname(a, b, sa, ga, name, (deadline), &STAMP)
extern int nsss_switch_grp_getbygid (nsss_switch_t *, struct group *, stralloc *, genalloc *, gid_t, tain_t const *, tain_t *) ;
#define nsss_switch_grp_getbygid_g(a, b, sa, ga, g, deadline) nsss_switch_grp_getbygid(a, b, sa, ga, g, (deadline), &STAMP)
extern int nsss_switch_grp_getlist (nsss_switch_t *, char const *, gid_t, genalloc *, tain_t const *, tain_t *) ;
#define nsss_switch_grp_getlist_g(a, user, g, ga, deadline) nsss_switch_grp_getlist(a, user, g, ga, (deadline), &STAMP)


 /* Shadow */

#define NSSS_SWITCH_SHADOW_END '\040'
#define NSSS_SWITCH_SHADOW_REWIND '\041'
#define NSSS_SWITCH_SHADOW_GET '\042'
#define NSSS_SWITCH_SHADOW_GETBYNAME '\043'

extern int nsss_switch_shadow_end (nsss_switch_t *, tain_t const *, tain_t *) ;
#define nsss_switch_shadow_end_g(a, deadline) nsss_switch_shadow_end(a, (deadline), &STAMP)
extern int nsss_switch_shadow_rewind (nsss_switch_t *, tain_t const *, tain_t *) ;
#define nsss_switch_shadow_rewind_g(a, deadline) nsss_switch_shadow_rewind(a, (deadline), &STAMP)
extern int nsss_switch_shadow_get (nsss_switch_t *, struct spwd *, stralloc *, tain_t const *, tain_t *) ;
#define nsss_switch_shadow_get_g(a, b, sa, deadline) nsss_switch_shadow_get(a, b, sa, (deadline), &STAMP)
extern int nsss_switch_shadow_getbyname (nsss_switch_t *, struct spwd *, stralloc *, char const *, tain_t const *, tain_t *) ;
#define nsss_switch_shadow_getbyname_g(a, b, sa, name, deadline) nsss_switch_shadow_getbyname(a, b, sa, name, (deadline), &STAMP)

#endif
