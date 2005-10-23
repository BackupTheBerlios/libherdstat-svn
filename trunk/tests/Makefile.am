# $Id$

SUBDIRS = src

export tests = string \
	container_base \
	glob \
	regex \
	algo \
	version \
	keyword \
	license \
	ebuild \
	find \
	package_list \
	herds.xml \
	devaway.xml \
	userinfo.xml \
	metadata.xml

TESTS = $(foreach f, $(tests), $(f)-test.sh)
TESTS_ENVIRONMENT = TEST_DATA=$(TEST_DATA) PORTDIR=$(TEST_DATA)/portdir PORTDIR_OVERLAY=''

CLEANFILES = actual/*
MAINTAINERCLEANFILES = Makefile.in *~
EXTRA_DIST = $(TESTS) common.sh expected
