# $Id$

if BUILD_TESTS

SUBDIRS = src

tests = string \
	container_base \
	glob \
	regex \
	algo \
	version \
	keyword \
	license \
	ebuild \
	package_list \
	package_finder \
	package_which \
	herds.xml \
	devaway.xml \
	userinfo.xml \
	metadata.xml

TESTS = $(foreach f, $(tests), $(f)-test.sh)
TESTS_ENVIRONMENT = TEST_DATA=$(TEST_DATA) PORTDIR=$(TEST_DATA)/portdir PORTDIR_OVERLAY=''

CLEANFILES = actual/*

endif

MAINTAINERCLEANFILES = Makefile.in *~
EXTRA_DIST = $(TESTS) common.sh expected
