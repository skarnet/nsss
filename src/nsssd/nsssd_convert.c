/* ISC license. */

#include <string.h>
#include <nsss/pwd-def.h>
#include <nsss/grp-def.h>
#include <nsss/shadow-def.h>
#include <nsss/nsssd.h>

void nsssd_passwd_convert (struct passwd *pw, nsssd_passwd_t const *p, char const *s)
{
  pw->pw_name = (char *)s + p->pw_name ;
  pw->pw_passwd = (char *)s + p->pw_passwd ;
  pw->pw_uid = p->pw_uid ;
  pw->pw_gid = p->pw_gid ;
  pw->pw_gecos = (char *)s + p->pw_gecos ;
  pw->pw_dir = (char *)s + p->pw_dir ;
  pw->pw_shell = (char *)s + p->pw_shell ; 
}

void nsssd_group_convert (struct group *gr, char **q, nsssd_group_t const *p, char const *s, size_t const *membase)
{
  gr->gr_name = (char *)s + p->gr_name ;
  gr->gr_passwd = (char *)s + p->gr_passwd ;
  gr->gr_gid = p->gr_gid ;
  gr->gr_mem = q ;
  for (size_t i = 0 ; i < p->gr_mem_n ; i++) *q++ = (char *)s + membase[p->gr_mem + i] ;
  *q++ = 0 ;
}

void nsssd_spwd_convert (struct spwd *sp, nsssd_spwd_t const *p, char const *s)
{
  sp->sp_namp = (char *)s + p->sp_namp ;
  sp->sp_pwdp = (char *)s + p->sp_pwdp ;
  sp->sp_lstchg = p->sp_lstchg ;
  sp->sp_min = p->sp_min ;
  sp->sp_max = p->sp_max ;
  sp->sp_warn = p->sp_warn ;
  sp->sp_inact = p->sp_inact ;
  sp->sp_expire = p->sp_expire ;
  sp->sp_flag = p->sp_flag ;
}
