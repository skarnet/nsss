BIN_TARGETS := \
nsssd-unix \
nsssd-nslcd \
nsssd-switch

LIBEXEC_TARGETS :=

TEST_BINS := \
test-switch \
test-unix \
test-nsssd-switch \
test-all-fallback

LIB_DEFS := NSSS=nsss NSSSD=nsssd
NSSS_DESCRIPTION := The nsss library (user-facing part of nsss, applications link against it)
NSSSD_DESCRIPTION := The nsssd library (non-user-facing part of nsss, only nsss modules link against it)

ifneq ($(DO_LIBC_INCLUDES),)
EXTRA_INCLUDES := src/include/pwd.h src/include/grp.h src/include/shadow.h
endif
