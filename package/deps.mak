#
# This file has been generated by tools/gen-deps.sh
#

src/include/nsss/grp-all.h: src/include/nsss/grp-def.h
src/include/nsss/grp-switch.h: src/include/nsss/grp-def.h
src/include/nsss/grp-unix.h: src/include/nsss/grp-def.h
src/include/nsss/grp.h: src/include/nsss/grp-all.h src/include/nsss/grp-switch.h src/include/nsss/grp-unix.h
src/include/nsss/nsss-all.h: src/include/nsss/grp-all.h src/include/nsss/pwd-all.h src/include/nsss/shadow-all.h
src/include/nsss/nsss-switch.h: src/include/nsss/grp-switch.h src/include/nsss/pwd-switch.h src/include/nsss/shadow-switch.h
src/include/nsss/nsss-unix.h: src/include/nsss/grp-unix.h src/include/nsss/pwd-unix.h src/include/nsss/shadow-unix.h
src/include/nsss/nsss.h: src/include/nsss/nsss-all.h src/include/nsss/nsss-switch.h src/include/nsss/nsss-unix.h
src/include/nsss/nsssd.h: src/include/nsss/grp-def.h src/include/nsss/pwd-def.h src/include/nsss/shadow-def.h
src/include/nsss/pwd-all.h: src/include/nsss/pwd-def.h
src/include/nsss/pwd-switch.h: src/include/nsss/pwd-def.h
src/include/nsss/pwd-unix.h: src/include/nsss/pwd-def.h
src/include/nsss/pwd.h: src/include/nsss/pwd-all.h src/include/nsss/pwd-switch.h src/include/nsss/pwd-unix.h
src/include/nsss/shadow-all.h: src/include/nsss/shadow-def.h
src/include/nsss/shadow-switch.h: src/include/nsss/shadow-def.h
src/include/nsss/shadow-unix.h: src/include/nsss/shadow-def.h
src/include/nsss/shadow.h: src/include/nsss/shadow-all.h src/include/nsss/shadow-switch.h src/include/nsss/shadow-unix.h
src/include/grp.h: src/include/nsss/grp.h
src/include/pwd.h: src/include/nsss/pwd.h
src/include/shadow.h: src/include/nsss/shadow.h
src/libnsss/nsss-internal.h: src/include/nsss/grp-def.h src/include/nsss/pwd-def.h src/include/nsss/shadow-def.h
src/libnsss/nsss-switch-internal.h: src/include/nsss/grp-def.h src/include/nsss/nsss-switch.h src/include/nsss/pwd-def.h src/include/nsss/shadow-def.h
src/libnsss/nsss-unix-internal.h: src/include/nsss/nsss-unix.h
src/libnsss/nsss_all_endgrent.o src/libnsss/nsss_all_endgrent.lo: src/libnsss/nsss_all_endgrent.c src/libnsss/nsss-all-internal.h src/include/nsss/grp-all.h src/include/nsss/grp-switch.h src/include/nsss/grp-unix.h
src/libnsss/nsss_all_endpwent.o src/libnsss/nsss_all_endpwent.lo: src/libnsss/nsss_all_endpwent.c src/libnsss/nsss-all-internal.h src/include/nsss/pwd-all.h src/include/nsss/pwd-switch.h src/include/nsss/pwd-unix.h
src/libnsss/nsss_all_endspent.o src/libnsss/nsss_all_endspent.lo: src/libnsss/nsss_all_endspent.c src/libnsss/nsss-all-internal.h src/include/nsss/shadow-all.h src/include/nsss/shadow-switch.h src/include/nsss/shadow-unix.h
src/libnsss/nsss_all_errno.o src/libnsss/nsss_all_errno.lo: src/libnsss/nsss_all_errno.c src/libnsss/nsss-all-internal.h
src/libnsss/nsss_all_getgrent.o src/libnsss/nsss_all_getgrent.lo: src/libnsss/nsss_all_getgrent.c src/libnsss/nsss-all-internal.h src/libnsss/nsss-internal.h src/libnsss/nsss-switch-internal.h src/include/nsss/config.h src/include/nsss/grp-all.h src/include/nsss/grp-unix.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_all_getgrent_r.o src/libnsss/nsss_all_getgrent_r.lo: src/libnsss/nsss_all_getgrent_r.c src/libnsss/nsss-all-internal.h src/libnsss/nsss-internal.h src/libnsss/nsss-switch-internal.h src/include/nsss/config.h src/include/nsss/grp-all.h src/include/nsss/grp-unix.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_all_getgrgid.o src/libnsss/nsss_all_getgrgid.lo: src/libnsss/nsss_all_getgrgid.c src/libnsss/nsss-internal.h src/include/nsss/config.h src/include/nsss/grp-all.h src/include/nsss/grp-unix.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_all_getgrgid_r.o src/libnsss/nsss_all_getgrgid_r.lo: src/libnsss/nsss_all_getgrgid_r.c src/libnsss/nsss-internal.h src/include/nsss/config.h src/include/nsss/grp-all.h src/include/nsss/grp-unix.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_all_getgrnam.o src/libnsss/nsss_all_getgrnam.lo: src/libnsss/nsss_all_getgrnam.c src/libnsss/nsss-internal.h src/include/nsss/config.h src/include/nsss/grp-all.h src/include/nsss/grp-unix.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_all_getgrnam_r.o src/libnsss/nsss_all_getgrnam_r.lo: src/libnsss/nsss_all_getgrnam_r.c src/libnsss/nsss-internal.h src/include/nsss/config.h src/include/nsss/grp-all.h src/include/nsss/grp-unix.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_all_getpwent.o src/libnsss/nsss_all_getpwent.lo: src/libnsss/nsss_all_getpwent.c src/libnsss/nsss-all-internal.h src/libnsss/nsss-internal.h src/libnsss/nsss-switch-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/pwd-all.h src/include/nsss/pwd-unix.h
src/libnsss/nsss_all_getpwent_r.o src/libnsss/nsss_all_getpwent_r.lo: src/libnsss/nsss_all_getpwent_r.c src/libnsss/nsss-all-internal.h src/libnsss/nsss-internal.h src/libnsss/nsss-switch-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/pwd-all.h src/include/nsss/pwd-unix.h
src/libnsss/nsss_all_getpwnam.o src/libnsss/nsss_all_getpwnam.lo: src/libnsss/nsss_all_getpwnam.c src/libnsss/nsss-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/pwd-all.h src/include/nsss/pwd-unix.h
src/libnsss/nsss_all_getpwnam_r.o src/libnsss/nsss_all_getpwnam_r.lo: src/libnsss/nsss_all_getpwnam_r.c src/libnsss/nsss-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/pwd-all.h src/include/nsss/pwd-unix.h
src/libnsss/nsss_all_getpwuid.o src/libnsss/nsss_all_getpwuid.lo: src/libnsss/nsss_all_getpwuid.c src/libnsss/nsss-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/pwd-all.h src/include/nsss/pwd-unix.h
src/libnsss/nsss_all_getpwuid_r.o src/libnsss/nsss_all_getpwuid_r.lo: src/libnsss/nsss_all_getpwuid_r.c src/libnsss/nsss-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/pwd-all.h src/include/nsss/pwd-unix.h
src/libnsss/nsss_all_getspent.o src/libnsss/nsss_all_getspent.lo: src/libnsss/nsss_all_getspent.c src/libnsss/nsss-all-internal.h src/libnsss/nsss-internal.h src/libnsss/nsss-switch-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/shadow-all.h src/include/nsss/shadow-unix.h
src/libnsss/nsss_all_getspent_r.o src/libnsss/nsss_all_getspent_r.lo: src/libnsss/nsss_all_getspent_r.c src/libnsss/nsss-all-internal.h src/libnsss/nsss-internal.h src/libnsss/nsss-switch-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/shadow-all.h src/include/nsss/shadow-unix.h
src/libnsss/nsss_all_getspnam.o src/libnsss/nsss_all_getspnam.lo: src/libnsss/nsss_all_getspnam.c src/libnsss/nsss-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/shadow-all.h src/include/nsss/shadow-unix.h
src/libnsss/nsss_all_getspnam_r.o src/libnsss/nsss_all_getspnam_r.lo: src/libnsss/nsss_all_getspnam_r.c src/libnsss/nsss-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/shadow-all.h src/include/nsss/shadow-unix.h
src/libnsss/nsss_all_setgrent.o src/libnsss/nsss_all_setgrent.lo: src/libnsss/nsss_all_setgrent.c src/libnsss/nsss-all-internal.h src/libnsss/nsss-switch-internal.h src/include/nsss/config.h src/include/nsss/grp-all.h src/include/nsss/grp-unix.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_all_setpwent.o src/libnsss/nsss_all_setpwent.lo: src/libnsss/nsss_all_setpwent.c src/libnsss/nsss-all-internal.h src/libnsss/nsss-switch-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/pwd-all.h src/include/nsss/pwd-unix.h
src/libnsss/nsss_all_setspent.o src/libnsss/nsss_all_setspent.lo: src/libnsss/nsss_all_setspent.c src/libnsss/nsss-all-internal.h src/libnsss/nsss-switch-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/shadow-all.h src/include/nsss/shadow-unix.h
src/libnsss/nsss_grp_copy.o src/libnsss/nsss_grp_copy.lo: src/libnsss/nsss_grp_copy.c src/libnsss/nsss-internal.h
src/libnsss/nsss_grp_here.o src/libnsss/nsss_grp_here.lo: src/libnsss/nsss_grp_here.c src/libnsss/nsss-internal.h src/include/nsss/grp-def.h
src/libnsss/nsss_pwd_copy.o src/libnsss/nsss_pwd_copy.lo: src/libnsss/nsss_pwd_copy.c src/libnsss/nsss-internal.h
src/libnsss/nsss_pwd_here.o src/libnsss/nsss_pwd_here.lo: src/libnsss/nsss_pwd_here.c src/libnsss/nsss-internal.h src/include/nsss/pwd-def.h
src/libnsss/nsss_shadow_copy.o src/libnsss/nsss_shadow_copy.lo: src/libnsss/nsss_shadow_copy.c src/libnsss/nsss-internal.h
src/libnsss/nsss_shadow_here.o src/libnsss/nsss_shadow_here.lo: src/libnsss/nsss_shadow_here.c src/libnsss/nsss-internal.h src/include/nsss/shadow-def.h
src/libnsss/nsss_switch_end.o src/libnsss/nsss_switch_end.lo: src/libnsss/nsss_switch_end.c src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_endgrent.o src/libnsss/nsss_switch_endgrent.lo: src/libnsss/nsss_switch_endgrent.c src/libnsss/nsss-switch-internal.h src/include/nsss/grp-switch.h
src/libnsss/nsss_switch_endpwent.o src/libnsss/nsss_switch_endpwent.lo: src/libnsss/nsss_switch_endpwent.c src/libnsss/nsss-switch-internal.h src/include/nsss/pwd-switch.h
src/libnsss/nsss_switch_endspent.o src/libnsss/nsss_switch_endspent.lo: src/libnsss/nsss_switch_endspent.c src/libnsss/nsss-switch-internal.h src/include/nsss/shadow-switch.h
src/libnsss/nsss_switch_getgrent.o src/libnsss/nsss_switch_getgrent.lo: src/libnsss/nsss_switch_getgrent.c src/libnsss/nsss-internal.h src/libnsss/nsss-switch-internal.h src/include/nsss/config.h src/include/nsss/grp-switch.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_getgrent_r.o src/libnsss/nsss_switch_getgrent_r.lo: src/libnsss/nsss_switch_getgrent_r.c src/libnsss/nsss-internal.h src/libnsss/nsss-switch-internal.h src/include/nsss/config.h src/include/nsss/grp-switch.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_getgrgid.o src/libnsss/nsss_switch_getgrgid.lo: src/libnsss/nsss_switch_getgrgid.c src/libnsss/nsss-internal.h src/include/nsss/config.h src/include/nsss/grp-switch.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_getgrgid_r.o src/libnsss/nsss_switch_getgrgid_r.lo: src/libnsss/nsss_switch_getgrgid_r.c src/libnsss/nsss-internal.h src/include/nsss/config.h src/include/nsss/grp-switch.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_getgrnam.o src/libnsss/nsss_switch_getgrnam.lo: src/libnsss/nsss_switch_getgrnam.c src/libnsss/nsss-internal.h src/include/nsss/config.h src/include/nsss/grp-switch.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_getgrnam_r.o src/libnsss/nsss_switch_getgrnam_r.lo: src/libnsss/nsss_switch_getgrnam_r.c src/libnsss/nsss-internal.h src/include/nsss/config.h src/include/nsss/grp-switch.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_getpwent.o src/libnsss/nsss_switch_getpwent.lo: src/libnsss/nsss_switch_getpwent.c src/libnsss/nsss-internal.h src/libnsss/nsss-switch-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/pwd-switch.h
src/libnsss/nsss_switch_getpwent_r.o src/libnsss/nsss_switch_getpwent_r.lo: src/libnsss/nsss_switch_getpwent_r.c src/libnsss/nsss-internal.h src/libnsss/nsss-switch-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/pwd-switch.h
src/libnsss/nsss_switch_getpwnam.o src/libnsss/nsss_switch_getpwnam.lo: src/libnsss/nsss_switch_getpwnam.c src/libnsss/nsss-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/pwd-switch.h
src/libnsss/nsss_switch_getpwnam_r.o src/libnsss/nsss_switch_getpwnam_r.lo: src/libnsss/nsss_switch_getpwnam_r.c src/libnsss/nsss-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/pwd-switch.h
src/libnsss/nsss_switch_getpwuid.o src/libnsss/nsss_switch_getpwuid.lo: src/libnsss/nsss_switch_getpwuid.c src/libnsss/nsss-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/pwd-switch.h
src/libnsss/nsss_switch_getpwuid_r.o src/libnsss/nsss_switch_getpwuid_r.lo: src/libnsss/nsss_switch_getpwuid_r.c src/libnsss/nsss-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/pwd-switch.h
src/libnsss/nsss_switch_getspent.o src/libnsss/nsss_switch_getspent.lo: src/libnsss/nsss_switch_getspent.c src/libnsss/nsss-internal.h src/libnsss/nsss-switch-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/shadow-switch.h
src/libnsss/nsss_switch_getspent_r.o src/libnsss/nsss_switch_getspent_r.lo: src/libnsss/nsss_switch_getspent_r.c src/libnsss/nsss-internal.h src/libnsss/nsss-switch-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/shadow-switch.h
src/libnsss/nsss_switch_getspnam.o src/libnsss/nsss_switch_getspnam.lo: src/libnsss/nsss_switch_getspnam.c src/libnsss/nsss-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/shadow-switch.h
src/libnsss/nsss_switch_getspnam_r.o src/libnsss/nsss_switch_getspnam_r.lo: src/libnsss/nsss_switch_getspnam_r.c src/libnsss/nsss-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/shadow-switch.h
src/libnsss/nsss_switch_grp_end.o src/libnsss/nsss_switch_grp_end.lo: src/libnsss/nsss_switch_grp_end.c src/libnsss/nsss-switch-internal.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_grp_get.o src/libnsss/nsss_switch_grp_get.lo: src/libnsss/nsss_switch_grp_get.c src/libnsss/nsss-switch-internal.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_grp_getbygid.o src/libnsss/nsss_switch_grp_getbygid.lo: src/libnsss/nsss_switch_grp_getbygid.c src/libnsss/nsss-switch-internal.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_grp_getbyname.o src/libnsss/nsss_switch_grp_getbyname.lo: src/libnsss/nsss_switch_grp_getbyname.c src/libnsss/nsss-switch-internal.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_grp_read.o src/libnsss/nsss_switch_grp_read.lo: src/libnsss/nsss_switch_grp_read.c src/libnsss/nsss-switch-internal.h src/include/nsss/grp-def.h
src/libnsss/nsss_switch_grp_rewind.o src/libnsss/nsss_switch_grp_rewind.lo: src/libnsss/nsss_switch_grp_rewind.c src/libnsss/nsss-switch-internal.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_here.o src/libnsss/nsss_switch_here.lo: src/libnsss/nsss_switch_here.c src/libnsss/nsss-switch-internal.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_op.o src/libnsss/nsss_switch_op.lo: src/libnsss/nsss_switch_op.c src/libnsss/nsss-switch-internal.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_pwd_end.o src/libnsss/nsss_switch_pwd_end.lo: src/libnsss/nsss_switch_pwd_end.c src/libnsss/nsss-switch-internal.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_pwd_get.o src/libnsss/nsss_switch_pwd_get.lo: src/libnsss/nsss_switch_pwd_get.c src/libnsss/nsss-switch-internal.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_pwd_getbyname.o src/libnsss/nsss_switch_pwd_getbyname.lo: src/libnsss/nsss_switch_pwd_getbyname.c src/libnsss/nsss-switch-internal.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_pwd_getbyuid.o src/libnsss/nsss_switch_pwd_getbyuid.lo: src/libnsss/nsss_switch_pwd_getbyuid.c src/libnsss/nsss-switch-internal.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_pwd_read.o src/libnsss/nsss_switch_pwd_read.lo: src/libnsss/nsss_switch_pwd_read.c src/libnsss/nsss-switch-internal.h src/include/nsss/pwd-def.h
src/libnsss/nsss_switch_pwd_rewind.o src/libnsss/nsss_switch_pwd_rewind.lo: src/libnsss/nsss_switch_pwd_rewind.c src/libnsss/nsss-switch-internal.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_setgrent.o src/libnsss/nsss_switch_setgrent.lo: src/libnsss/nsss_switch_setgrent.c src/libnsss/nsss-switch-internal.h src/include/nsss/config.h src/include/nsss/grp-switch.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_setpwent.o src/libnsss/nsss_switch_setpwent.lo: src/libnsss/nsss_switch_setpwent.c src/libnsss/nsss-switch-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/pwd-switch.h
src/libnsss/nsss_switch_setspent.o src/libnsss/nsss_switch_setspent.lo: src/libnsss/nsss_switch_setspent.c src/libnsss/nsss-switch-internal.h src/include/nsss/config.h src/include/nsss/nsss-switch.h src/include/nsss/shadow-switch.h
src/libnsss/nsss_switch_shadow_end.o src/libnsss/nsss_switch_shadow_end.lo: src/libnsss/nsss_switch_shadow_end.c src/libnsss/nsss-switch-internal.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_shadow_get.o src/libnsss/nsss_switch_shadow_get.lo: src/libnsss/nsss_switch_shadow_get.c src/libnsss/nsss-switch-internal.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_shadow_getbyname.o src/libnsss/nsss_switch_shadow_getbyname.lo: src/libnsss/nsss_switch_shadow_getbyname.c src/libnsss/nsss-switch-internal.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_shadow_read.o src/libnsss/nsss_switch_shadow_read.lo: src/libnsss/nsss_switch_shadow_read.c src/libnsss/nsss-switch-internal.h src/include/nsss/shadow-def.h
src/libnsss/nsss_switch_shadow_rewind.o src/libnsss/nsss_switch_shadow_rewind.lo: src/libnsss/nsss_switch_shadow_rewind.c src/libnsss/nsss-switch-internal.h src/include/nsss/nsss-switch.h
src/libnsss/nsss_switch_start.o src/libnsss/nsss_switch_start.lo: src/libnsss/nsss_switch_start.c src/include/nsss/nsss-switch.h
src/libnsss/nsss_unix_end.o src/libnsss/nsss_unix_end.lo: src/libnsss/nsss_unix_end.c src/include/nsss/nsss-unix.h
src/libnsss/nsss_unix_endgrent.o src/libnsss/nsss_unix_endgrent.lo: src/libnsss/nsss_unix_endgrent.c src/libnsss/nsss-unix-internal.h src/include/nsss/grp-unix.h
src/libnsss/nsss_unix_endpwent.o src/libnsss/nsss_unix_endpwent.lo: src/libnsss/nsss_unix_endpwent.c src/libnsss/nsss-unix-internal.h src/include/nsss/pwd-unix.h
src/libnsss/nsss_unix_endspent.o src/libnsss/nsss_unix_endspent.lo: src/libnsss/nsss_unix_endspent.c src/libnsss/nsss-unix-internal.h src/include/nsss/shadow-unix.h
src/libnsss/nsss_unix_field.o src/libnsss/nsss_unix_field.lo: src/libnsss/nsss_unix_field.c src/libnsss/nsss-unix-internal.h
src/libnsss/nsss_unix_getgrent.o src/libnsss/nsss_unix_getgrent.lo: src/libnsss/nsss_unix_getgrent.c src/libnsss/nsss-internal.h src/libnsss/nsss-unix-internal.h src/include/nsss/grp-unix.h src/include/nsss/nsss-unix.h
src/libnsss/nsss_unix_getgrent_r.o src/libnsss/nsss_unix_getgrent_r.lo: src/libnsss/nsss_unix_getgrent_r.c src/libnsss/nsss-internal.h src/libnsss/nsss-unix-internal.h src/include/nsss/grp-unix.h src/include/nsss/nsss-unix.h
src/libnsss/nsss_unix_getgrgid.o src/libnsss/nsss_unix_getgrgid.lo: src/libnsss/nsss_unix_getgrgid.c src/libnsss/nsss-internal.h src/include/nsss/grp-unix.h src/include/nsss/nsss-unix.h
src/libnsss/nsss_unix_getgrgid_r.o src/libnsss/nsss_unix_getgrgid_r.lo: src/libnsss/nsss_unix_getgrgid_r.c src/libnsss/nsss-internal.h src/include/nsss/grp-unix.h src/include/nsss/nsss-unix.h
src/libnsss/nsss_unix_getgrnam.o src/libnsss/nsss_unix_getgrnam.lo: src/libnsss/nsss_unix_getgrnam.c src/libnsss/nsss-internal.h src/include/nsss/grp-unix.h src/include/nsss/nsss-unix.h
src/libnsss/nsss_unix_getgrnam_r.o src/libnsss/nsss_unix_getgrnam_r.lo: src/libnsss/nsss_unix_getgrnam_r.c src/libnsss/nsss-internal.h src/include/nsss/grp-unix.h src/include/nsss/nsss-unix.h
src/libnsss/nsss_unix_getgrouplist.o src/libnsss/nsss_unix_getgrouplist.lo: src/libnsss/nsss_unix_getgrouplist.c src/libnsss/nsss-unix-internal.h src/include/nsss/grp-def.h src/include/nsss/grp-unix.h src/include/nsss/nsss-unix.h
src/libnsss/nsss_unix_getpwent.o src/libnsss/nsss_unix_getpwent.lo: src/libnsss/nsss_unix_getpwent.c src/libnsss/nsss-internal.h src/libnsss/nsss-unix-internal.h src/include/nsss/nsss-unix.h src/include/nsss/pwd-unix.h
src/libnsss/nsss_unix_getpwent_r.o src/libnsss/nsss_unix_getpwent_r.lo: src/libnsss/nsss_unix_getpwent_r.c src/libnsss/nsss-internal.h src/libnsss/nsss-unix-internal.h src/include/nsss/nsss-unix.h src/include/nsss/pwd-unix.h
src/libnsss/nsss_unix_getpwnam.o src/libnsss/nsss_unix_getpwnam.lo: src/libnsss/nsss_unix_getpwnam.c src/libnsss/nsss-internal.h src/include/nsss/nsss-unix.h src/include/nsss/pwd-unix.h
src/libnsss/nsss_unix_getpwnam_r.o src/libnsss/nsss_unix_getpwnam_r.lo: src/libnsss/nsss_unix_getpwnam_r.c src/libnsss/nsss-internal.h src/include/nsss/nsss-unix.h src/include/nsss/pwd-unix.h
src/libnsss/nsss_unix_getpwuid.o src/libnsss/nsss_unix_getpwuid.lo: src/libnsss/nsss_unix_getpwuid.c src/libnsss/nsss-internal.h src/include/nsss/nsss-unix.h src/include/nsss/pwd-unix.h
src/libnsss/nsss_unix_getpwuid_r.o src/libnsss/nsss_unix_getpwuid_r.lo: src/libnsss/nsss_unix_getpwuid_r.c src/libnsss/nsss-internal.h src/include/nsss/nsss-unix.h src/include/nsss/pwd-unix.h
src/libnsss/nsss_unix_getspent.o src/libnsss/nsss_unix_getspent.lo: src/libnsss/nsss_unix_getspent.c src/libnsss/nsss-internal.h src/libnsss/nsss-unix-internal.h src/include/nsss/nsss-unix.h src/include/nsss/shadow-unix.h
src/libnsss/nsss_unix_getspent_r.o src/libnsss/nsss_unix_getspent_r.lo: src/libnsss/nsss_unix_getspent_r.c src/libnsss/nsss-internal.h src/libnsss/nsss-unix-internal.h src/include/nsss/nsss-unix.h src/include/nsss/shadow-unix.h
src/libnsss/nsss_unix_getspnam.o src/libnsss/nsss_unix_getspnam.lo: src/libnsss/nsss_unix_getspnam.c src/libnsss/nsss-internal.h src/include/nsss/nsss-unix.h src/include/nsss/shadow-unix.h
src/libnsss/nsss_unix_getspnam_r.o src/libnsss/nsss_unix_getspnam_r.lo: src/libnsss/nsss_unix_getspnam_r.c src/libnsss/nsss-internal.h src/include/nsss/nsss-unix.h src/include/nsss/shadow-unix.h
src/libnsss/nsss_unix_grp_get.o src/libnsss/nsss_unix_grp_get.lo: src/libnsss/nsss_unix_grp_get.c src/libnsss/nsss-unix-internal.h src/include/nsss/grp-def.h src/include/nsss/nsss-unix.h
src/libnsss/nsss_unix_grp_getbygid.o src/libnsss/nsss_unix_grp_getbygid.lo: src/libnsss/nsss_unix_grp_getbygid.c src/include/nsss/grp-def.h src/include/nsss/nsss-unix.h
src/libnsss/nsss_unix_grp_getbyname.o src/libnsss/nsss_unix_grp_getbyname.lo: src/libnsss/nsss_unix_grp_getbyname.c src/include/nsss/grp-def.h src/include/nsss/nsss-unix.h
src/libnsss/nsss_unix_grp_here.o src/libnsss/nsss_unix_grp_here.lo: src/libnsss/nsss_unix_grp_here.c src/libnsss/nsss-unix-internal.h
src/libnsss/nsss_unix_maybe_start.o src/libnsss/nsss_unix_maybe_start.lo: src/libnsss/nsss_unix_maybe_start.c src/include/nsss/nsss-unix.h
src/libnsss/nsss_unix_pwd_get.o src/libnsss/nsss_unix_pwd_get.lo: src/libnsss/nsss_unix_pwd_get.c src/libnsss/nsss-unix-internal.h src/include/nsss/nsss-unix.h src/include/nsss/pwd-def.h
src/libnsss/nsss_unix_pwd_getbyname.o src/libnsss/nsss_unix_pwd_getbyname.lo: src/libnsss/nsss_unix_pwd_getbyname.c src/include/nsss/nsss-unix.h src/include/nsss/pwd-def.h
src/libnsss/nsss_unix_pwd_getbyuid.o src/libnsss/nsss_unix_pwd_getbyuid.lo: src/libnsss/nsss_unix_pwd_getbyuid.c src/include/nsss/nsss-unix.h src/include/nsss/pwd-def.h
src/libnsss/nsss_unix_pwd_here.o src/libnsss/nsss_unix_pwd_here.lo: src/libnsss/nsss_unix_pwd_here.c src/libnsss/nsss-unix-internal.h
src/libnsss/nsss_unix_rewind.o src/libnsss/nsss_unix_rewind.lo: src/libnsss/nsss_unix_rewind.c src/include/nsss/nsss-unix.h
src/libnsss/nsss_unix_setgrent.o src/libnsss/nsss_unix_setgrent.lo: src/libnsss/nsss_unix_setgrent.c src/libnsss/nsss-unix-internal.h src/include/nsss/grp-unix.h src/include/nsss/nsss-unix.h
src/libnsss/nsss_unix_setpwent.o src/libnsss/nsss_unix_setpwent.lo: src/libnsss/nsss_unix_setpwent.c src/libnsss/nsss-unix-internal.h src/include/nsss/nsss-unix.h src/include/nsss/pwd-unix.h
src/libnsss/nsss_unix_setspent.o src/libnsss/nsss_unix_setspent.lo: src/libnsss/nsss_unix_setspent.c src/libnsss/nsss-unix-internal.h src/include/nsss/nsss-unix.h src/include/nsss/shadow-unix.h
src/libnsss/nsss_unix_shadow_get.o src/libnsss/nsss_unix_shadow_get.lo: src/libnsss/nsss_unix_shadow_get.c src/libnsss/nsss-unix-internal.h src/include/nsss/nsss-unix.h src/include/nsss/shadow-def.h
src/libnsss/nsss_unix_shadow_getbyname.o src/libnsss/nsss_unix_shadow_getbyname.lo: src/libnsss/nsss_unix_shadow_getbyname.c src/include/nsss/nsss-unix.h src/include/nsss/shadow-def.h
src/libnsss/nsss_unix_shadow_here.o src/libnsss/nsss_unix_shadow_here.lo: src/libnsss/nsss_unix_shadow_here.c src/libnsss/nsss-unix-internal.h
src/libnsss/nsss_unix_start.o src/libnsss/nsss_unix_start.lo: src/libnsss/nsss_unix_start.c src/include/nsss/nsss-unix.h
src/nsssd/nsssd-nslcd.o src/nsssd/nsssd-nslcd.lo: src/nsssd/nsssd-nslcd.c src/include/nsss/nsssd.h src/nsssd/nsssd-nslcd.h
src/nsssd/nsssd-switch.o src/nsssd/nsssd-switch.lo: src/nsssd/nsssd-switch.c src/include/nsss/nsss-switch.h src/include/nsss/nsssd.h
src/nsssd/nsssd-unix.o src/nsssd/nsssd-unix.lo: src/nsssd/nsssd-unix.c src/include/nsss/grp-unix.h src/include/nsss/nsssd.h src/include/nsss/pwd-unix.h src/include/nsss/shadow-unix.h
src/nsssd/nsssd_convert.o src/nsssd/nsssd_convert.lo: src/nsssd/nsssd_convert.c src/include/nsss/grp-def.h src/include/nsss/nsssd.h src/include/nsss/pwd-def.h src/include/nsss/shadow-def.h
src/nsssd/nsssd_main.o src/nsssd/nsssd_main.lo: src/nsssd/nsssd_main.c src/include/nsss/grp-def.h src/include/nsss/nsss-switch.h src/include/nsss/nsssd.h src/include/nsss/pwd-def.h src/include/nsss/shadow-def.h
src/tests/test-all-fallback.o src/tests/test-all-fallback.lo: src/tests/test-all-fallback.c src/include/nsss/grp-def.h src/include/nsss/nsss-all.h src/include/nsss/pwd-def.h
src/tests/test-switch.o src/tests/test-switch.lo: src/tests/test-switch.c src/include/nsss/grp-def.h src/include/nsss/nsss-switch.h src/include/nsss/pwd-def.h
src/tests/test-unix.o src/tests/test-unix.lo: src/tests/test-unix.c src/include/nsss/grp-def.h src/include/nsss/nsss-unix.h src/include/nsss/pwd-def.h

ifeq ($(strip $(STATIC_LIBS_ARE_PIC)),)
libnsss.a.xyzzy: src/libnsss/nsss_all_endgrent.o src/libnsss/nsss_all_endpwent.o src/libnsss/nsss_all_endspent.o src/libnsss/nsss_all_errno.o src/libnsss/nsss_all_getgrent.o src/libnsss/nsss_all_getgrent_r.o src/libnsss/nsss_all_getgrgid.o src/libnsss/nsss_all_getgrgid_r.o src/libnsss/nsss_all_getgrnam.o src/libnsss/nsss_all_getgrnam_r.o src/libnsss/nsss_all_getpwent.o src/libnsss/nsss_all_getpwent_r.o src/libnsss/nsss_all_getpwnam.o src/libnsss/nsss_all_getpwnam_r.o src/libnsss/nsss_all_getpwuid.o src/libnsss/nsss_all_getpwuid_r.o src/libnsss/nsss_all_getspent.o src/libnsss/nsss_all_getspent_r.o src/libnsss/nsss_all_getspnam.o src/libnsss/nsss_all_getspnam_r.o src/libnsss/nsss_all_setgrent.o src/libnsss/nsss_all_setpwent.o src/libnsss/nsss_all_setspent.o src/libnsss/nsss_grp_copy.o src/libnsss/nsss_grp_here.o src/libnsss/nsss_pwd_copy.o src/libnsss/nsss_pwd_here.o src/libnsss/nsss_shadow_copy.o src/libnsss/nsss_shadow_here.o src/libnsss/nsss_switch_end.o src/libnsss/nsss_switch_endgrent.o src/libnsss/nsss_switch_endpwent.o src/libnsss/nsss_switch_endspent.o src/libnsss/nsss_switch_getgrent.o src/libnsss/nsss_switch_getgrent_r.o src/libnsss/nsss_switch_getgrgid.o src/libnsss/nsss_switch_getgrgid_r.o src/libnsss/nsss_switch_getgrnam.o src/libnsss/nsss_switch_getgrnam_r.o src/libnsss/nsss_switch_getpwent.o src/libnsss/nsss_switch_getpwent_r.o src/libnsss/nsss_switch_getpwnam.o src/libnsss/nsss_switch_getpwnam_r.o src/libnsss/nsss_switch_getpwuid.o src/libnsss/nsss_switch_getpwuid_r.o src/libnsss/nsss_switch_getspent.o src/libnsss/nsss_switch_getspent_r.o src/libnsss/nsss_switch_getspnam.o src/libnsss/nsss_switch_getspnam_r.o src/libnsss/nsss_switch_grp_end.o src/libnsss/nsss_switch_grp_get.o src/libnsss/nsss_switch_grp_getbygid.o src/libnsss/nsss_switch_grp_getbyname.o src/libnsss/nsss_switch_grp_read.o src/libnsss/nsss_switch_grp_rewind.o src/libnsss/nsss_switch_here.o src/libnsss/nsss_switch_op.o src/libnsss/nsss_switch_pwd_end.o src/libnsss/nsss_switch_pwd_get.o src/libnsss/nsss_switch_pwd_getbyname.o src/libnsss/nsss_switch_pwd_getbyuid.o src/libnsss/nsss_switch_pwd_read.o src/libnsss/nsss_switch_pwd_rewind.o src/libnsss/nsss_switch_setgrent.o src/libnsss/nsss_switch_setpwent.o src/libnsss/nsss_switch_setspent.o src/libnsss/nsss_switch_shadow_end.o src/libnsss/nsss_switch_shadow_get.o src/libnsss/nsss_switch_shadow_getbyname.o src/libnsss/nsss_switch_shadow_read.o src/libnsss/nsss_switch_shadow_rewind.o src/libnsss/nsss_switch_start.o src/libnsss/nsss_unix_end.o src/libnsss/nsss_unix_endgrent.o src/libnsss/nsss_unix_endpwent.o src/libnsss/nsss_unix_endspent.o src/libnsss/nsss_unix_field.o src/libnsss/nsss_unix_getgrent.o src/libnsss/nsss_unix_getgrent_r.o src/libnsss/nsss_unix_getgrgid.o src/libnsss/nsss_unix_getgrgid_r.o src/libnsss/nsss_unix_getgrnam.o src/libnsss/nsss_unix_getgrnam_r.o src/libnsss/nsss_unix_getpwent.o src/libnsss/nsss_unix_getpwent_r.o src/libnsss/nsss_unix_getpwnam.o src/libnsss/nsss_unix_getpwnam_r.o src/libnsss/nsss_unix_getpwuid.o src/libnsss/nsss_unix_getpwuid_r.o src/libnsss/nsss_unix_getspent.o src/libnsss/nsss_unix_getspent_r.o src/libnsss/nsss_unix_getspnam.o src/libnsss/nsss_unix_getspnam_r.o src/libnsss/nsss_unix_getgrouplist.o src/libnsss/nsss_unix_grp_get.o src/libnsss/nsss_unix_grp_getbygid.o src/libnsss/nsss_unix_grp_getbyname.o src/libnsss/nsss_unix_grp_here.o src/libnsss/nsss_unix_maybe_start.o src/libnsss/nsss_unix_pwd_get.o src/libnsss/nsss_unix_pwd_getbyname.o src/libnsss/nsss_unix_pwd_getbyuid.o src/libnsss/nsss_unix_pwd_here.o src/libnsss/nsss_unix_rewind.o src/libnsss/nsss_unix_setgrent.o src/libnsss/nsss_unix_setpwent.o src/libnsss/nsss_unix_setspent.o src/libnsss/nsss_unix_shadow_get.o src/libnsss/nsss_unix_shadow_getbyname.o src/libnsss/nsss_unix_shadow_here.o src/libnsss/nsss_unix_start.o
else
libnsss.a.xyzzy: src/libnsss/nsss_all_endgrent.lo src/libnsss/nsss_all_endpwent.lo src/libnsss/nsss_all_endspent.lo src/libnsss/nsss_all_errno.lo src/libnsss/nsss_all_getgrent.lo src/libnsss/nsss_all_getgrent_r.lo src/libnsss/nsss_all_getgrgid.lo src/libnsss/nsss_all_getgrgid_r.lo src/libnsss/nsss_all_getgrnam.lo src/libnsss/nsss_all_getgrnam_r.lo src/libnsss/nsss_all_getpwent.lo src/libnsss/nsss_all_getpwent_r.lo src/libnsss/nsss_all_getpwnam.lo src/libnsss/nsss_all_getpwnam_r.lo src/libnsss/nsss_all_getpwuid.lo src/libnsss/nsss_all_getpwuid_r.lo src/libnsss/nsss_all_getspent.lo src/libnsss/nsss_all_getspent_r.lo src/libnsss/nsss_all_getspnam.lo src/libnsss/nsss_all_getspnam_r.lo src/libnsss/nsss_all_setgrent.lo src/libnsss/nsss_all_setpwent.lo src/libnsss/nsss_all_setspent.lo src/libnsss/nsss_grp_copy.lo src/libnsss/nsss_grp_here.lo src/libnsss/nsss_pwd_copy.lo src/libnsss/nsss_pwd_here.lo src/libnsss/nsss_shadow_copy.lo src/libnsss/nsss_shadow_here.lo src/libnsss/nsss_switch_end.lo src/libnsss/nsss_switch_endgrent.lo src/libnsss/nsss_switch_endpwent.lo src/libnsss/nsss_switch_endspent.lo src/libnsss/nsss_switch_getgrent.lo src/libnsss/nsss_switch_getgrent_r.lo src/libnsss/nsss_switch_getgrgid.lo src/libnsss/nsss_switch_getgrgid_r.lo src/libnsss/nsss_switch_getgrnam.lo src/libnsss/nsss_switch_getgrnam_r.lo src/libnsss/nsss_switch_getpwent.lo src/libnsss/nsss_switch_getpwent_r.lo src/libnsss/nsss_switch_getpwnam.lo src/libnsss/nsss_switch_getpwnam_r.lo src/libnsss/nsss_switch_getpwuid.lo src/libnsss/nsss_switch_getpwuid_r.lo src/libnsss/nsss_switch_getspent.lo src/libnsss/nsss_switch_getspent_r.lo src/libnsss/nsss_switch_getspnam.lo src/libnsss/nsss_switch_getspnam_r.lo src/libnsss/nsss_switch_grp_end.lo src/libnsss/nsss_switch_grp_get.lo src/libnsss/nsss_switch_grp_getbygid.lo src/libnsss/nsss_switch_grp_getbyname.lo src/libnsss/nsss_switch_grp_read.lo src/libnsss/nsss_switch_grp_rewind.lo src/libnsss/nsss_switch_here.lo src/libnsss/nsss_switch_op.lo src/libnsss/nsss_switch_pwd_end.lo src/libnsss/nsss_switch_pwd_get.lo src/libnsss/nsss_switch_pwd_getbyname.lo src/libnsss/nsss_switch_pwd_getbyuid.lo src/libnsss/nsss_switch_pwd_read.lo src/libnsss/nsss_switch_pwd_rewind.lo src/libnsss/nsss_switch_setgrent.lo src/libnsss/nsss_switch_setpwent.lo src/libnsss/nsss_switch_setspent.lo src/libnsss/nsss_switch_shadow_end.lo src/libnsss/nsss_switch_shadow_get.lo src/libnsss/nsss_switch_shadow_getbyname.lo src/libnsss/nsss_switch_shadow_read.lo src/libnsss/nsss_switch_shadow_rewind.lo src/libnsss/nsss_switch_start.lo src/libnsss/nsss_unix_end.lo src/libnsss/nsss_unix_endgrent.lo src/libnsss/nsss_unix_endpwent.lo src/libnsss/nsss_unix_endspent.lo src/libnsss/nsss_unix_field.lo src/libnsss/nsss_unix_getgrent.lo src/libnsss/nsss_unix_getgrent_r.lo src/libnsss/nsss_unix_getgrgid.lo src/libnsss/nsss_unix_getgrgid_r.lo src/libnsss/nsss_unix_getgrnam.lo src/libnsss/nsss_unix_getgrnam_r.lo src/libnsss/nsss_unix_getpwent.lo src/libnsss/nsss_unix_getpwent_r.lo src/libnsss/nsss_unix_getpwnam.lo src/libnsss/nsss_unix_getpwnam_r.lo src/libnsss/nsss_unix_getpwuid.lo src/libnsss/nsss_unix_getpwuid_r.lo src/libnsss/nsss_unix_getspent.lo src/libnsss/nsss_unix_getspent_r.lo src/libnsss/nsss_unix_getspnam.lo src/libnsss/nsss_unix_getspnam_r.lo src/libnsss/nsss_unix_getgrouplist.lo src/libnsss/nsss_unix_grp_get.lo src/libnsss/nsss_unix_grp_getbygid.lo src/libnsss/nsss_unix_grp_getbyname.lo src/libnsss/nsss_unix_grp_here.lo src/libnsss/nsss_unix_maybe_start.lo src/libnsss/nsss_unix_pwd_get.lo src/libnsss/nsss_unix_pwd_getbyname.lo src/libnsss/nsss_unix_pwd_getbyuid.lo src/libnsss/nsss_unix_pwd_here.lo src/libnsss/nsss_unix_rewind.lo src/libnsss/nsss_unix_setgrent.lo src/libnsss/nsss_unix_setpwent.lo src/libnsss/nsss_unix_setspent.lo src/libnsss/nsss_unix_shadow_get.lo src/libnsss/nsss_unix_shadow_getbyname.lo src/libnsss/nsss_unix_shadow_here.lo src/libnsss/nsss_unix_start.lo
endif
libnsss.so.xyzzy: EXTRA_LIBS := -lskarnet -lpthread
libnsss.so.xyzzy: src/libnsss/nsss_all_endgrent.lo src/libnsss/nsss_all_endpwent.lo src/libnsss/nsss_all_endspent.lo src/libnsss/nsss_all_errno.lo src/libnsss/nsss_all_getgrent.lo src/libnsss/nsss_all_getgrent_r.lo src/libnsss/nsss_all_getgrgid.lo src/libnsss/nsss_all_getgrgid_r.lo src/libnsss/nsss_all_getgrnam.lo src/libnsss/nsss_all_getgrnam_r.lo src/libnsss/nsss_all_getpwent.lo src/libnsss/nsss_all_getpwent_r.lo src/libnsss/nsss_all_getpwnam.lo src/libnsss/nsss_all_getpwnam_r.lo src/libnsss/nsss_all_getpwuid.lo src/libnsss/nsss_all_getpwuid_r.lo src/libnsss/nsss_all_getspent.lo src/libnsss/nsss_all_getspent_r.lo src/libnsss/nsss_all_getspnam.lo src/libnsss/nsss_all_getspnam_r.lo src/libnsss/nsss_all_setgrent.lo src/libnsss/nsss_all_setpwent.lo src/libnsss/nsss_all_setspent.lo src/libnsss/nsss_grp_copy.lo src/libnsss/nsss_grp_here.lo src/libnsss/nsss_pwd_copy.lo src/libnsss/nsss_pwd_here.lo src/libnsss/nsss_shadow_copy.lo src/libnsss/nsss_shadow_here.lo src/libnsss/nsss_switch_end.lo src/libnsss/nsss_switch_endgrent.lo src/libnsss/nsss_switch_endpwent.lo src/libnsss/nsss_switch_endspent.lo src/libnsss/nsss_switch_getgrent.lo src/libnsss/nsss_switch_getgrent_r.lo src/libnsss/nsss_switch_getgrgid.lo src/libnsss/nsss_switch_getgrgid_r.lo src/libnsss/nsss_switch_getgrnam.lo src/libnsss/nsss_switch_getgrnam_r.lo src/libnsss/nsss_switch_getpwent.lo src/libnsss/nsss_switch_getpwent_r.lo src/libnsss/nsss_switch_getpwnam.lo src/libnsss/nsss_switch_getpwnam_r.lo src/libnsss/nsss_switch_getpwuid.lo src/libnsss/nsss_switch_getpwuid_r.lo src/libnsss/nsss_switch_getspent.lo src/libnsss/nsss_switch_getspent_r.lo src/libnsss/nsss_switch_getspnam.lo src/libnsss/nsss_switch_getspnam_r.lo src/libnsss/nsss_switch_grp_end.lo src/libnsss/nsss_switch_grp_get.lo src/libnsss/nsss_switch_grp_getbygid.lo src/libnsss/nsss_switch_grp_getbyname.lo src/libnsss/nsss_switch_grp_read.lo src/libnsss/nsss_switch_grp_rewind.lo src/libnsss/nsss_switch_here.lo src/libnsss/nsss_switch_op.lo src/libnsss/nsss_switch_pwd_end.lo src/libnsss/nsss_switch_pwd_get.lo src/libnsss/nsss_switch_pwd_getbyname.lo src/libnsss/nsss_switch_pwd_getbyuid.lo src/libnsss/nsss_switch_pwd_read.lo src/libnsss/nsss_switch_pwd_rewind.lo src/libnsss/nsss_switch_setgrent.lo src/libnsss/nsss_switch_setpwent.lo src/libnsss/nsss_switch_setspent.lo src/libnsss/nsss_switch_shadow_end.lo src/libnsss/nsss_switch_shadow_get.lo src/libnsss/nsss_switch_shadow_getbyname.lo src/libnsss/nsss_switch_shadow_read.lo src/libnsss/nsss_switch_shadow_rewind.lo src/libnsss/nsss_switch_start.lo src/libnsss/nsss_unix_end.lo src/libnsss/nsss_unix_endgrent.lo src/libnsss/nsss_unix_endpwent.lo src/libnsss/nsss_unix_endspent.lo src/libnsss/nsss_unix_field.lo src/libnsss/nsss_unix_getgrent.lo src/libnsss/nsss_unix_getgrent_r.lo src/libnsss/nsss_unix_getgrgid.lo src/libnsss/nsss_unix_getgrgid_r.lo src/libnsss/nsss_unix_getgrnam.lo src/libnsss/nsss_unix_getgrnam_r.lo src/libnsss/nsss_unix_getpwent.lo src/libnsss/nsss_unix_getpwent_r.lo src/libnsss/nsss_unix_getpwnam.lo src/libnsss/nsss_unix_getpwnam_r.lo src/libnsss/nsss_unix_getpwuid.lo src/libnsss/nsss_unix_getpwuid_r.lo src/libnsss/nsss_unix_getspent.lo src/libnsss/nsss_unix_getspent_r.lo src/libnsss/nsss_unix_getspnam.lo src/libnsss/nsss_unix_getspnam_r.lo src/libnsss/nsss_unix_getgrouplist.lo src/libnsss/nsss_unix_grp_get.lo src/libnsss/nsss_unix_grp_getbygid.lo src/libnsss/nsss_unix_grp_getbyname.lo src/libnsss/nsss_unix_grp_here.lo src/libnsss/nsss_unix_maybe_start.lo src/libnsss/nsss_unix_pwd_get.lo src/libnsss/nsss_unix_pwd_getbyname.lo src/libnsss/nsss_unix_pwd_getbyuid.lo src/libnsss/nsss_unix_pwd_here.lo src/libnsss/nsss_unix_rewind.lo src/libnsss/nsss_unix_setgrent.lo src/libnsss/nsss_unix_setpwent.lo src/libnsss/nsss_unix_setspent.lo src/libnsss/nsss_unix_shadow_get.lo src/libnsss/nsss_unix_shadow_getbyname.lo src/libnsss/nsss_unix_shadow_here.lo src/libnsss/nsss_unix_start.lo
ifeq ($(strip $(STATIC_LIBS_ARE_PIC)),)
libnsssd.a.xyzzy: src/nsssd/nsssd_main.o src/nsssd/nsssd_convert.o
else
libnsssd.a.xyzzy: src/nsssd/nsssd_main.lo src/nsssd/nsssd_convert.lo
endif
libnsssd.so.xyzzy: EXTRA_LIBS := -lskarnet
libnsssd.so.xyzzy: src/nsssd/nsssd_main.lo src/nsssd/nsssd_convert.lo
nsssd-nslcd: EXTRA_LIBS :=
nsssd-nslcd: src/nsssd/nsssd-nslcd.o ${LIBNSSSD} -lskarnet
nsssd-unix: EXTRA_LIBS :=
nsssd-unix: src/nsssd/nsssd-unix.o ${LIBNSSS} ${LIBNSSSD} -lskarnet
test-all-fallback: EXTRA_LIBS := ${SOCKET_LIB} ${TAINNOW_LIB}
test-all-fallback: src/tests/test-all-fallback.o ${LIBNSSS} -lskarnet
test-switch: EXTRA_LIBS := ${SOCKET_LIB} ${TAINNOW_LIB}
test-switch: src/tests/test-switch.o ${LIBNSSS} -lskarnet
test-unix: EXTRA_LIBS :=
test-unix: src/tests/test-unix.o ${LIBNSSS} -lskarnet
