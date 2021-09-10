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

ifneq ($(DO_LIBC_INCLUDES),)
EXTRA_INCLUDES := src/include/pwd.h src/include/grp.h src/include/shadow.h
endif
