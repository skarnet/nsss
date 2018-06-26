/* ISC license. */

#include <skalibs/buffer.h>
#include <nsss/nsss-unix.h>

int nsss_unix_maybe_start (nsss_unix_t *a, char const *path)
{
  return buffer_fd(&a->b) >= 0 || nsss_unix_start(a, path) ;
}
