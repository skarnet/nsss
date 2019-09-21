/* ISC license. */

#ifndef NSSSD_H
#define NSSSD_H

#include <sys/types.h>
#include <nsss/pwd-def.h>
#include <nsss/grp-def.h>
#include <nsss/shadow-def.h>

#define NSSSD_EOF 255

typedef struct nsssd_passwd_s nsssd_passwd_t, *nsssd_passwd_t_ref ;
struct nsssd_passwd_s
{
  size_t pw_name ;
  size_t pw_passwd ;
  uid_t pw_uid ;
  uid_t pw_gid ;
  size_t pw_gecos ;
  size_t pw_dir ;
  size_t pw_shell ;
} ;

typedef struct nsssd_group_s nsssd_group_t, *nsssd_group_t_ref ;
struct nsssd_group_s
{
  size_t gr_name ;
  size_t gr_passwd ;
  gid_t gr_gid ;
  size_t gr_mem ;
  size_t gr_mem_n ;
} ;

typedef struct nsssd_spwd_s nsssd_spwd_t, *nsssd_spwd_t_ref ;
struct nsssd_spwd_s
{
  size_t sp_namp ;
  size_t sp_pwdp ;
  long sp_lstchg ;
  long sp_min ;
  long sp_max ;
  long sp_warn ;
  long sp_inact ;
  long sp_expire ;
  unsigned long sp_flag ;
} ;


/* Functions provided by libnsssd */

extern int nsssd_main (char const *const *, char const *const *) ;
extern void nsssd_passwd_convert (struct passwd *, nsssd_passwd_t const *, char const *) ;
extern void nsssd_group_convert (struct group *, char **, nsssd_group_t const *, char const *, size_t const *) ;
extern void nsssd_spwd_convert (struct spwd *, nsssd_spwd_t const *, char const *) ;


/* Functions that must be provided by the backend */

extern void *nsssd_handle_init (void) ;
extern int nsssd_handle_start (void *, char const *const *, char const *const *) ;
extern void nsssd_handle_end (void *) ;

extern int nsssd_pwd_start (void *) ;
extern int nsssd_pwd_rewind (void *) ;
extern int nsssd_pwd_get (void *, struct passwd *) ;
extern int nsssd_pwd_getbyuid (void *, struct passwd *, uid_t) ;
extern int nsssd_pwd_getbyname (void *, struct passwd *, char const *) ;
extern void nsssd_pwd_end (void *) ;

extern int nsssd_grp_start (void *) ;
extern int nsssd_grp_rewind (void *) ;
extern int nsssd_grp_get (void *, struct group *) ;
extern int nsssd_grp_getbygid (void *, struct group *, gid_t) ;
extern int nsssd_grp_getbyname (void *, struct group *, char const *) ;
extern int nsssd_grp_getlist (void *, char const *, gid_t *, size_t, size_t *) ;
extern void nsssd_grp_end (void *) ;

extern int nsssd_shadow_start (void *) ;
extern int nsssd_shadow_rewind (void *) ;
extern int nsssd_shadow_get (void *, struct spwd *) ;
extern int nsssd_shadow_getbyname (void *, struct spwd *, char const *) ;
extern void nsssd_shadow_end (void *) ;

#endif
