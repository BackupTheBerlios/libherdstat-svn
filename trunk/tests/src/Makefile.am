include $(top_builddir)/Makefile.am.common

if BUILD_TESTS

noinst_PROGRAMS = run_lhs_test
run_lhs_test_SOURCES = run_lhs_test.cc *.hh
LDADD = $(top_builddir)/herdstat/libherdstat.la

endif

MAINTAINERCLEANFILES = Makefile.in *~ .loT
