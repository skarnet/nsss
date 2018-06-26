/* ISC license. */

#include <skalibs/strerr2.h>
#include <nsss/pwd-unix.h>
#include <nsss/grp-unix.h>
#include <nsss/shadow-unix.h>
#include <nsss/nsssd.h>

void *nsssd_handle_init (void)
{
  return 0 ;
}

int nsssd_handle_start (void *handle, char const *const *argv, char const *const *envp)
{
  (void)handle ;
  (void)argv ;
  (void)envp ;
  return 1 ;
}

void nsssd_handle_end (void *handle)
{
  (void)handle ;
}

int nsssd_pwd_start (void *handle)
{
  (void)handle ;
  return 1 ;
}

int nsssd_pwd_rewind (void *handle)
{
  nsss_unix_setpwent() ;
  (void)handle ;
  return 1 ;
}

int nsssd_pwd_get (void *handle, struct passwd *pw)
{
  struct passwd *pw2 = nsss_unix_getpwent() ;
  if (!pw2) return 0 ;
  *pw = *pw2 ;
  (void)handle ;
  return 1 ;
}

int nsssd_pwd_getbyuid (void *handle, struct passwd *pw, uid_t uid)
{
  struct passwd *pw2 = nsss_unix_getpwuid(uid) ;
  if (!pw2) return 0 ;
  *pw = *pw2 ;
  (void)handle ;
  return 1 ;
}

int nsssd_pwd_getbyname (void *handle, struct passwd *pw, char const *name)
{
  struct passwd *pw2 = nsss_unix_getpwnam(name) ;
  if (!pw2) return 0 ;
  *pw = *pw2 ;
  (void)handle ;
  return 1 ;
}

void nsssd_pwd_end (void *handle)
{
  nsss_unix_endpwent() ;
  (void)handle ;
}

void nsssd_grp_handle_init (void *handle)
{
  (void)handle ;
}

int nsssd_grp_start (void *handle)
{
  (void)handle ;
  return 1 ;
}

int nsssd_grp_rewind (void *handle)
{
  nsss_unix_setgrent() ;
  (void)handle ;
  return 1 ;
}

int nsssd_grp_get (void *handle, struct group *gr)
{
  struct group *gr2 = nsss_unix_getgrent() ;
  if (!gr2) return 0 ;
  *gr = *gr2 ;
  (void)handle ;
  return 1 ;
}

int nsssd_grp_getbygid (void *handle, struct group *gr, gid_t gid)
{
  struct group *gr2 = nsss_unix_getgrgid(gid) ;
  if (!gr2) return 0 ;
  *gr = *gr2 ;
  (void)handle ;
  return 1 ;
}

int nsssd_grp_getbyname (void *handle, struct group *gr, char const *name)
{
  struct group *gr2 = nsss_unix_getgrnam(name) ;
  if (!gr2) return 0 ;
  *gr = *gr2 ;
  (void)handle ;
  return 1 ;
}

void nsssd_grp_end (void *handle)
{
  nsss_unix_endgrent() ;
  (void)handle ;
}

void nsssd_shadow_handle_init (void *handle)
{
  (void)handle ;
}

int nsssd_shadow_start (void *handle)
{
  (void)handle ;
  return 1 ;
}

int nsssd_shadow_rewind (void *handle)
{
  nsss_unix_setspent() ;
  (void)handle ;
  return 1 ;
}

int nsssd_shadow_get (void *handle, struct spwd *sp)
{
  struct spwd *sp2 = nsss_unix_getspent() ;
  if (!sp2) return 0 ;
  *sp = *sp2 ;
  (void)handle ;
  return 1 ;
}

int nsssd_shadow_getbyname (void *handle, struct spwd *sp, char const *name)
{
  struct spwd *sp2 = nsss_unix_getspnam(name) ;
  if (!sp2) return 0 ;
  *sp = *sp2 ;
  (void)handle ;
  return 1 ;
}

void nsssd_shadow_end (void *handle)
{
  nsss_unix_endspent() ;
  (void)handle ;
}

int main (int argc, char const *const *argv, char const *const *envp)
{
  PROG = "nsssd-unix" ;
  return nsssd_main(argv+1, envp) ;
}
