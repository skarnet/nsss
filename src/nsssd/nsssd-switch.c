/* ISC license. */

#include <stdint.h>
#include <stdlib.h>

#include <skalibs/types.h>
#include <skalibs/buffer.h>
#include <skalibs/strerr2.h>
#include <skalibs/sgetopt.h>
#include <skalibs/tai.h>

#include <nsss/nsssd.h>
#include <nsss/nsss-switch.h>
#include <nsss/nsss-unix.h>

#define USAGE "nsssd-switch flag1 backend1... \"\" flag2 backend2... \"\""
#define dieusage() strerr_dieusage(100, USAGE)

#define MAX_BACKENDS 16

static tain tto = TAIN_INFINITE_RELATIVE ;


 /* We cannot depend on execline so we duplicate functions here */

static unsigned int el_getstrict (void)
{
  static unsigned int strict = 0 ;
  static int first = 1 ;
  if (first)
  {
    char const *x = getenv("EXECLINE_STRICT") ;
    first = 0 ;
    if (x) uint0_scan(x, &strict) ;
  }
  return strict ;
}

static int el_semicolon (char const **argv)
{
  static unsigned int nblock = 0 ;
  int argc1 = 0 ;
  nblock++ ;
  for (;; argc1++, argv++)
  {
    char const *arg = *argv ;
    if (!arg) return argc1 + 1 ;
    if (!arg[0]) return argc1 ;
    else if (arg[0] == ' ') ++*argv ;
    else
    {
      unsigned int strict = el_getstrict() ;
      if (strict)
      {
        char fmt1[UINT_FMT] ;
        char fmt2[UINT_FMT] ;
        fmt1[uint_fmt(fmt1, nblock)] = 0 ;
        fmt2[uint_fmt(fmt2, (unsigned int)argc1)] = 0 ;
        if (strict >= 2)
          strerr_dief6x(100, "unquoted argument ", arg, " at block ", fmt1, " position ", fmt2) ;
        else
          strerr_warnw6x("unquoted argument ", arg, " at block ", fmt1, " position ", fmt2) ;
      }
    }
  }
}


 /* Real code here */

typedef struct backend_s backend_t, *backend_t_ref ;
struct backend_s
{
  char const *const *argv ;
  nsss_switch_t handle ;
  uint8_t flags ;
} ;

typedef struct handle_s handle_t, *handle_t_ref ;
struct handle_s
{
  backend_t tab[MAX_BACKENDS] ;
  unsigned int n ;
} ;

void *nsssd_handle_init (void)
{
  static handle_t a = { .n = 0 } ;
  return &a ;
}

int nsssd_handle_start (void *handle, char const *const *argv)
{
  static nsss_switch_t const nsss_switch_zero = NSSS_SWITCH_ZERO ;
  handle_t *a = handle ;
  char const **args = (char const **)argv ;
  unsigned int argc = 0 ;
  while (args[argc])
  {
    backend_t *be = &a->tab[a->n] ;
    int argc1 ;
    unsigned int flags ;
    if (!uint0_scan(args[argc++], &flags)) dieusage() ;
    if (!args[argc]) strerr_dief1x(100, "missing block") ;
    argc1 = el_semicolon(args + argc) ;
    if (!argc1) strerr_dief1x(100, "empty block") ;
    if (!args[argc + argc1]) strerr_dief1x(100, "unterminated block") ;
    args[argc + argc1] = 0 ;
    if (a->n++ >= MAX_BACKENDS) strerr_dief1x(100, "too many defined backends") ;
    be->flags = flags & 0x7 ;
    be->argv = args + argc ;
    be->handle = nsss_switch_zero ;
    argc += argc1 ;
  }
  if (!a->n) strerr_dief1x(100, "no defined backends") ;
  return 1 ;
}

void nsssd_handle_end (void *handle)
{
  handle_t *a = handle ;
  for (unsigned int i = 0 ; i < a->n ; i++)
    nsss_switch_end(&a->tab[i].handle, NSSS_SWITCH_PWD | NSSS_SWITCH_GRP | NSSS_SWITCH_SHADOW) ;
  a->n = 0 ;
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

int nsssd_grp_getlist (void *handle, char const *user, gid_t *gids, size_t n, size_t *r)
{
  (void)handle ;
  return nsss_unix_getgrouplist_preadjust(user, gids, n, r) ;
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

int main (int argc, char const *const *argv)
{
  PROG = "nsssd-switch" ;
  {
    subgetopt l = SUBGETOPT_ZERO ;
    unsigned int t = 0 ;
    for (;;)
    {
      int opt = subgetopt_r(argc, argv, "t:", &l) ;
      if (opt == -1) break ;
      switch (opt)
      {
        case 't' : if (!uint0_scan(l.arg, &t)) dieusage() ; break ;
        default : dieusage() ;
      }
    }
    argc -= l.ind ; argv += l.ind ;
    if (t) tain_from_millisecs(&tto, t) ;
  }
  return nsssd_main(argv) ;
}
