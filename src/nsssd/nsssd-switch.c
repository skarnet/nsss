/* ISC license. */

#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

#include <skalibs/types.h>
#include <skalibs/buffer.h>
#include <skalibs/strerr.h>
#include <skalibs/sgetopt.h>
#include <skalibs/tai.h>
#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>

#include <nsss/nsssd.h>
#include <nsss/nsss-switch.h>

#define USAGE "nsssd-switch bitfield1 backend1... \"\" bitfield2 backend2... \"\""
#define dieusage() strerr_dieusage(100, USAGE)

#define MAX_BACKENDS 8

static tain tto = TAIN_INFINITE_RELATIVE ;
static stralloc storagesa = STRALLOC_ZERO ;
static genalloc storagega = GENALLOC_ZERO ;


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
  nsss_switch_t handle ;
  uint8_t flags : 3 ;
  uint8_t failed : 1 ;
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
    unsigned int bitfield ;
    int argc1 ;
    if (!uint0_scan(args[argc++], &bitfield)) dieusage() ;
    if (!args[argc]) strerr_dief1x(100, "missing block") ;
    argc1 = el_semicolon(args + argc) ;
    if (!argc1) strerr_dief1x(100, "empty block") ;
    if (!args[argc + argc1]) strerr_dief1x(100, "unterminated block") ;
    args[argc + argc1] = 0 ;
    be->handle = nsss_switch_zero ;
    be->flags = 0 ;
    be->failed = !nsss_switch_startf(&be->handle, NSSS_SWITCH_PWD | NSSS_SWITCH_GRP | NSSS_SWITCH_SHADOW, args + argc, 0, 0) ;
    if (a->n++ >= MAX_BACKENDS) strerr_dief1x(100, "too many defined backends") ;
    be->flags |= bitfield & 0x7 ;
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
  handle_t *a = handle ;
  for (unsigned int i = 0 ; i < a->n ; i++)
  {
    tain deadline ;
    if (a->tab[i].failed)
    {
      if (a->tab[i].flags & 1) return 0 ;
      else continue ;
    }
    tain_add_g(&deadline, &tto) ;
    if (nsss_switch_pwd_rewind_g(&a->tab[i].handle, &deadline)) return 1 ;
    if (errno == ETIMEDOUT)
    {
      nsss_switch_end(&a->tab[i].handle, NSSS_SWITCH_PWD | NSSS_SWITCH_GRP | NSSS_SWITCH_SHADOW) ;
      a->tab[i].failed = 1 ;
    }
    if (a->tab[i].flags & 2) return 0 ;
  }
  return 0 ;
}

int nsssd_pwd_get (void *handle, struct passwd *pw)
{
  handle_t *a = handle ;
  for (unsigned int i = 0 ; i < a->n ; i++)
  {
    tain deadline ;
    if (a->tab[i].failed)
    {
      if (a->tab[i].flags & 1) return 0 ;
      else continue ;
    }
    tain_add_g(&deadline, &tto) ;
    storagesa.len = 0 ;
    errno = 0 ;
    if (nsss_switch_pwd_get_g(&a->tab[i].handle, pw, &storagesa, &deadline)) return 1 ;
    if (errno == ETIMEDOUT)
    {
      nsss_switch_end(&a->tab[i].handle, NSSS_SWITCH_PWD | NSSS_SWITCH_GRP | NSSS_SWITCH_SHADOW) ;
      a->tab[i].failed = 1 ;
    }
    if (a->tab[i].flags & (errno ? 2 : 4)) return 0 ;
  }
  return 0 ;
}

int nsssd_pwd_getbyuid (void *handle, struct passwd *pw, uid_t uid)
{
  handle_t *a = handle ;
  for (unsigned int i = 0 ; i < a->n ; i++)
  {
    tain deadline ;
    if (a->tab[i].failed)
    {
      if (a->tab[i].flags & 1) return 0 ;
      else continue ;
    }
    tain_add_g(&deadline, &tto) ;
    storagesa.len = 0 ;
    errno = 0 ;
    if (nsss_switch_pwd_getbyuid_g(&a->tab[i].handle, pw, &storagesa, uid, &deadline)) return 1 ;
    if (errno == ETIMEDOUT)
    {
      nsss_switch_end(&a->tab[i].handle, NSSS_SWITCH_PWD | NSSS_SWITCH_GRP | NSSS_SWITCH_SHADOW) ;
      a->tab[i].failed = 1 ;
    }
    if (a->tab[i].flags & (errno ? 2 : 4)) return 0 ;
  }
  return 0 ;
}

int nsssd_pwd_getbyname (void *handle, struct passwd *pw, char const *name)
{
  handle_t *a = handle ;
  for (unsigned int i = 0 ; i < a->n ; i++)
  {
    tain deadline ;
    if (a->tab[i].failed)
    {
      if (a->tab[i].flags & 1) return 0 ;
      else continue ;
    }
    tain_add_g(&deadline, &tto) ;
    storagesa.len = 0 ;
    errno = 0 ;
    if (nsss_switch_pwd_getbyname_g(&a->tab[i].handle, pw, &storagesa, name, &deadline)) return 1 ;
    if (errno == ETIMEDOUT)
    {
      nsss_switch_end(&a->tab[i].handle, NSSS_SWITCH_PWD | NSSS_SWITCH_GRP | NSSS_SWITCH_SHADOW) ;
      a->tab[i].failed = 1 ;
    }
    if (a->tab[i].flags & (errno ? 2 : 4)) return 0 ;
  }
  return 0 ;
}

void nsssd_pwd_end (void *handle)
{
  handle_t *a = handle ;
  for (unsigned int i = 0 ; i < a->n ; i++)
  {
    tain deadline ;
    if (a->tab[i].failed)
    {
      if (a->tab[i].flags & 1) return ;
      else continue ;
    }
    tain_add_g(&deadline, &tto) ;
    if (nsss_switch_pwd_end_g(&a->tab[i].handle, &deadline)) continue ;
    if (errno == ETIMEDOUT)
    {
      nsss_switch_end(&a->tab[i].handle, NSSS_SWITCH_PWD | NSSS_SWITCH_GRP | NSSS_SWITCH_SHADOW) ;
      a->tab[i].failed = 1 ;
    }
  }
}

int nsssd_grp_start (void *handle)
{
  (void)handle ;
  return 1 ;
}

int nsssd_grp_rewind (void *handle)
{
  handle_t *a = handle ;
  for (unsigned int i = 0 ; i < a->n ; i++)
  {
    tain deadline ;
    if (a->tab[i].failed)
    {
      if (a->tab[i].flags & 1) return 0 ;
      else continue ;
    }
    tain_add_g(&deadline, &tto) ;
    if (nsss_switch_grp_rewind_g(&a->tab[i].handle, &deadline)) return 1 ;
    if (errno == ETIMEDOUT)
    {
      nsss_switch_end(&a->tab[i].handle, NSSS_SWITCH_PWD | NSSS_SWITCH_GRP | NSSS_SWITCH_SHADOW) ;
      a->tab[i].failed = 1 ;
    }
    if (a->tab[i].flags & 2) return 0 ;
  }
  return 0 ;
}

int nsssd_grp_get (void *handle, struct group *gr)
{
  handle_t *a = handle ;
  for (unsigned int i = 0 ; i < a->n ; i++)
  {
    tain deadline ;
    if (a->tab[i].failed)
    {
      if (a->tab[i].flags & 1) return 0 ;
      else continue ;
    }
    tain_add_g(&deadline, &tto) ;
    storagesa.len = 0 ;
    genalloc_setlen(char *, &storagega, 0) ;
    errno = 0 ;
    if (nsss_switch_grp_get_g(&a->tab[i].handle, gr, &storagesa, &storagega, &deadline)) return 1 ;
    if (errno == ETIMEDOUT)
    {
      nsss_switch_end(&a->tab[i].handle, NSSS_SWITCH_PWD | NSSS_SWITCH_GRP | NSSS_SWITCH_SHADOW) ;
      a->tab[i].failed = 1 ;
    }
    if (a->tab[i].flags & (errno ? 2 : 4)) return 0 ;
  }
  return 0 ;
}

int nsssd_grp_getbygid (void *handle, struct group *gr, gid_t gid)
{
  handle_t *a = handle ;
  for (unsigned int i = 0 ; i < a->n ; i++)
  {
    tain deadline ;
    if (a->tab[i].failed)
    {
      if (a->tab[i].flags & 1) return 0 ;
      else continue ;
    }
    tain_add_g(&deadline, &tto) ;
    storagesa.len = 0 ;
    genalloc_setlen(char *, &storagega, 0) ;
    errno = 0 ;
    if (nsss_switch_grp_getbygid_g(&a->tab[i].handle, gr, &storagesa, &storagega, gid, &deadline)) return 1 ;
    if (errno == ETIMEDOUT)
    {
      nsss_switch_end(&a->tab[i].handle, NSSS_SWITCH_PWD | NSSS_SWITCH_GRP | NSSS_SWITCH_SHADOW) ;
      a->tab[i].failed = 1 ;
    }
    if (a->tab[i].flags & (errno ? 2 : 4)) return 0 ;
  }
  return 0 ;
}

int nsssd_grp_getbyname (void *handle, struct group *gr, char const *name)
{
  handle_t *a = handle ;
  for (unsigned int i = 0 ; i < a->n ; i++)
  {
    tain deadline ;
    if (a->tab[i].failed)
    {
      if (a->tab[i].flags & 1) return 0 ;
      else continue ;
    }
    tain_add_g(&deadline, &tto) ;
    storagesa.len = 0 ;
    genalloc_setlen(char *, &storagega, 0) ;
    errno = 0 ;
    if (nsss_switch_grp_getbyname_g(&a->tab[i].handle, gr, &storagesa, &storagega, name, &deadline)) return 1 ;
    if (errno == ETIMEDOUT)
    {
      nsss_switch_end(&a->tab[i].handle, NSSS_SWITCH_PWD | NSSS_SWITCH_GRP | NSSS_SWITCH_SHADOW) ;
      a->tab[i].failed = 1 ;
    }
    if (a->tab[i].flags & (errno ? 2 : 4)) return 0 ;
  }
  return 0 ;
}

int nsssd_grp_getlist (void *handle, char const *user, gid_t *gids, size_t n, size_t *r)
{
  handle_t *a = handle ;
  for (unsigned int i = 0 ; i < a->n ; i++)
  {
    tain deadline ;
    if (a->tab[i].failed)
    {
      if (a->tab[i].flags & 1) return 0 ;
      else continue ;
    }
    tain_add_g(&deadline, &tto) ;
    storagesa.len = 0 ;
    errno = 0 ;
    if (nsss_switch_grp_getlist_g(&a->tab[i].handle, user, gids, n, r, &storagesa, &deadline)) return 1 ;
    if (errno == ETIMEDOUT)
    {
      nsss_switch_end(&a->tab[i].handle, NSSS_SWITCH_PWD | NSSS_SWITCH_GRP | NSSS_SWITCH_SHADOW) ;
      a->tab[i].failed = 1 ;
    }
    if (a->tab[i].flags & (errno ? 2 : 4)) return 0 ;
  }
  return 0 ;
}

void nsssd_grp_end (void *handle)
{
  handle_t *a = handle ;
  for (unsigned int i = 0 ; i < a->n ; i++)
  {
    tain deadline ;
    if (a->tab[i].failed)
    {
      if (a->tab[i].flags & 1) return ;
      else continue ;
    }
    tain_add_g(&deadline, &tto) ;
    if (nsss_switch_grp_end_g(&a->tab[i].handle, &deadline)) continue ;
    if (errno == ETIMEDOUT)
    {
      nsss_switch_end(&a->tab[i].handle, NSSS_SWITCH_PWD | NSSS_SWITCH_GRP | NSSS_SWITCH_SHADOW) ;
      a->tab[i].failed = 1 ;
    }
  }
}

int nsssd_shadow_start (void *handle)
{
  (void)handle ;
  return 1 ;
}

int nsssd_shadow_rewind (void *handle)
{
  handle_t *a = handle ;
  for (unsigned int i = 0 ; i < a->n ; i++)
  {
    tain deadline ;
    if (a->tab[i].failed)
    {
      if (a->tab[i].flags & 1) return 0 ;
      else continue ;
    }
    tain_add_g(&deadline, &tto) ;
    if (nsss_switch_shadow_rewind_g(&a->tab[i].handle, &deadline)) return 1 ;
    if (errno == ETIMEDOUT)
    {
      nsss_switch_end(&a->tab[i].handle, NSSS_SWITCH_PWD | NSSS_SWITCH_GRP | NSSS_SWITCH_SHADOW) ;
      a->tab[i].failed = 1 ;
    }
    if (a->tab[i].flags & 2) return 0 ;
  }
  return 0 ;
}

int nsssd_shadow_get (void *handle, struct spwd *sp)
{
  handle_t *a = handle ;
  for (unsigned int i = 0 ; i < a->n ; i++)
  {
    tain deadline ;
    if (a->tab[i].failed)
    {
      if (a->tab[i].flags & 1) return 0 ;
      else continue ;
    }
    tain_add_g(&deadline, &tto) ;
    storagesa.len = 0 ;
    errno = 0 ;
    if (nsss_switch_shadow_get_g(&a->tab[i].handle, sp, &storagesa, &deadline)) return 1 ;
    if (errno == ETIMEDOUT)
    {
      nsss_switch_end(&a->tab[i].handle, NSSS_SWITCH_PWD | NSSS_SWITCH_GRP | NSSS_SWITCH_SHADOW) ;
      a->tab[i].failed = 1 ;
    }
    if (a->tab[i].flags & (errno ? 2 : 4)) return 0 ;
  }
  return 0 ;
}

int nsssd_shadow_getbyname (void *handle, struct spwd *sp, char const *name)
{
  handle_t *a = handle ;
  for (unsigned int i = 0 ; i < a->n ; i++)
  {
    tain deadline ;
    if (a->tab[i].failed)
    {
      if (a->tab[i].flags & 1) return 0 ;
      else continue ;
    }
    tain_add_g(&deadline, &tto) ;
    storagesa.len = 0 ;
    errno = 0 ;
    if (nsss_switch_shadow_getbyname_g(&a->tab[i].handle, sp, &storagesa, name, &deadline)) return 1 ;
    if (errno == ETIMEDOUT)
    {
      nsss_switch_end(&a->tab[i].handle, NSSS_SWITCH_PWD | NSSS_SWITCH_GRP | NSSS_SWITCH_SHADOW) ;
      a->tab[i].failed = 1 ;
    }
    if (a->tab[i].flags & (errno ? 2 : 4)) return 0 ;
  }
  return 0 ;
}

void nsssd_shadow_end (void *handle)
{
  handle_t *a = handle ;
  for (unsigned int i = 0 ; i < a->n ; i++)
  {
    tain deadline ;
    if (a->tab[i].failed)
    {
      if (a->tab[i].flags & 1) return ;
      else continue ;
    }
    tain_add_g(&deadline, &tto) ;
    if (nsss_switch_pwd_end_g(&a->tab[i].handle, &deadline)) continue ;
    if (errno == ETIMEDOUT)
    {
      nsss_switch_end(&a->tab[i].handle, NSSS_SWITCH_PWD | NSSS_SWITCH_GRP | NSSS_SWITCH_SHADOW) ;
      a->tab[i].failed = 1 ;
    }
  }
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
