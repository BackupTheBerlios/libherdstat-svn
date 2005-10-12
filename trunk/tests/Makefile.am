# $Id$

SUBDIRS = src

tests = string \
	glob \
	regex \
	algo \
	version \
	keyword \
	herds.xml \
	devaway.xml \
	userinfo.xml \
	metadata.xml

TESTS = $(foreach f, $(tests), $(f)-test.sh)
TESTS_ENVIRONMENT = PORTDIR=portdir PORTDIR_OVERLAY=''

CLEANFILES = actual/* localstatedir/*cache*
MAINTAINERCLEANFILES = Makefile.in *~
EXTRA_DIST = $(TESTS) \
	     common.sh \
	     portdir \
	     expected \
	     localstatedir
