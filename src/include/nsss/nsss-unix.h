/* ISC license. */

#ifndef NSSS_UNIX_H
#define NSSS_UNIX_H

#include <sys/types.h>

#include <skalibs/buffer.h>
#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <nsss/pwd-unix.h>
#include <nsss/grp-unix.h>
#include <nsss/shadow-unix.h>

#define NSSS_UNIX_BUFSIZE 4096

typedef struct nsss_unix_s nsss_unix_t, *nsss_unix_t_ref ;
struct nsss_unix_s
{
  buffer b ;
  char buf[NSSS_UNIX_BUFSIZE] ;
} ;
#define NSSS_UNIX_ZERO { .b = BUFFER_ZERO }

extern int nsss_unix_start (nsss_unix_t *, char const *) ;
extern int nsss_unix_maybe_start (nsss_unix_t *, char const *) ;
extern void nsss_unix_end (nsss_unix_t *) ;
extern int nsss_unix_rewind (nsss_unix_t *) ;


 /* Password */

#define nsss_unix_pwd_start(a) nsss_unix_start(a, "/etc/passwd")
#define nsss_unix_pwd_maybe_start(a) nsss_unix_maybe_start(a, "/etc/passwd")
#define nsss_unix_pwd_end(a) nsss_unix_end(a)
#define nsss_unix_pwd_rewind(a) nsss_unix_rewind(a)
extern int nsss_unix_pwd_get (nsss_unix_t *, struct passwd *, stralloc *) ;
extern int nsss_unix_pwd_getbyname (nsss_unix_t *, struct passwd *, stralloc *, char const *) ;
extern int nsss_unix_pwd_getbyuid (nsss_unix_t *, struct passwd *, stralloc *, uid_t) ;


 /* Group */

#define nsss_unix_grp_start(a) nsss_unix_start(a, "/etc/group")
#define nsss_unix_grp_maybe_start(a) nsss_unix_maybe_start(a, "/etc/group")
#define nsss_unix_grp_end(a) nsss_unix_end(a)
#define nsss_unix_grp_rewind(a) nsss_unix_rewind(a)
extern int nsss_unix_grp_get (nsss_unix_t *, struct group *, stralloc *, genalloc *) ;
extern int nsss_unix_grp_getbyname (nsss_unix_t *, struct group *, stralloc *, genalloc *, char const *) ;
extern int nsss_unix_grp_getbygid (nsss_unix_t *, struct group *, stralloc *, genalloc *, gid_t) ;
extern int nsss_unix_grp_getlist (nsss_unix_t *, gid_t *, size_t, size_t *, stralloc *, genalloc *, char const *) ;


 /* Shadow */

#define nsss_unix_shadow_start(a) nsss_unix_start(a, "/etc/shadow")
#define nsss_unix_shadow_maybe_start(a) nsss_unix_maybe_start(a, "/etc/shadow")
#define nsss_unix_shadow_end(a) nsss_unix_end(a)
#define nsss_unix_shadow_rewind(a) nsss_unix_rewind(a)
extern int nsss_unix_shadow_get (nsss_unix_t *, struct spwd *, stralloc *) ;
extern int nsss_unix_shadow_getbyname (nsss_unix_t *, struct spwd *, stralloc *, char const *) ;

#endif
