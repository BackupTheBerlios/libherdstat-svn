# $Id: Makefile.am 633 2005-09-28 12:11:58Z ka0ttic $

include $(top_builddir)/Makefile.am.common

SUBDIRS = util fetcher xml portage

cc_sources = exceptions.cc \
	     email_address.cc
hh_sources = exceptions.hh \
	     noncopyable.hh \
	     cachable.hh \
	     fetchable.hh \
	     parsable.hh \
	     email_address.hh

lib_LTLIBRARIES = libherdstat.la
libherdstat_la_LDFLAGS = -release $(VERSION_MAJOR).$(VERSION_MINOR) -version-info $(LIBRARY_VERSION)
libherdstat_la_LIBADD = util/libutil.la \
			fetcher/libfetcher.la \
			xml/libxml.la \
			portage/libportage.la
libherdstat_la_SOURCES = $(hh_sources) $(cc_sources)

library_includedir=$(includedir)/$(PACKAGE)-$(VERSION_MAJOR).$(VERSION_MINOR)/herdstat
library_include_HEADERS = $(hh_sources)

MAINTAINERCLEANFILES = Makefile.in *~ .loT

srchtml: $(foreach f, $(libherdstat_la_SOURCES), $(f).html)
	@for x in $(SUBDIRS) ; do \
		cd ${PWD}/$${x} && $(MAKE) $@ ; \
	done

%.cc.html: %.cc
	@echo Generating $@
	@test -d $(top_srcdir)/html/herdstat || mkdir $(top_srcdir)/html/herdstat
	@source-highlight -c ../src.css -s cpp -f html -t4 -n -i $? -o ../html/herdstat/$@

%.hh.html: %.hh
	@echo Generating $@
	@test -d $(top_srcdir)/html/herdstat || mkdir $(top_srcdir)/html/herdstat
	@source-highlight -c ../src.css -s cpp -f html -t4 -n -i $? -o ../html/herdstat/$@
