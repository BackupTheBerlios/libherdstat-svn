# $Id: Makefile.am 217 2005-12-26 12:29:31Z ka0ttic $

include $(top_builddir)/Makefile.am.common

cc_sources = readline.cc history.cc
hh_sources = readline.hh history.hh

if BUILD_RL_INTERFACE
noinst_LTLIBRARIES = librl.la
librl_la_SOURCES = $(cc_sources) $(hh_sources)
librl_la_LIBADD = @READLINE_LIBS@

library_includedir=$(includedir)/$(PACKAGE)-$(VERSION_MAJOR).$(VERSION_MINOR)/herdstat/readline
library_include_HEADERS = $(hh_sources)
else
EXTRA_DIST = $(cc_sources) $(hh_sources)
endif

MAINTAINERCLEANFILES = Makefile.in *~ *.loT

srchtml: $(foreach f, $(cc_sources), $(f).html) $(foreach f, $(hh_sources), $(f).html)

%.cc.html: %.cc
	@echo Generating $@
	@test -d $(top_srcdir)/html/herdstat/readline || \
		mkdir $(top_srcdir)/html/herdstat/readline
	@source-highlight -c ../../src.css -s cpp -f html -t4 -n -i $? -o \
		$(top_srcdir)/html/herdstat/readline/$@

%.hh.html: %.hh
	@echo Generating $@
	@test -d $(top_srcdir)/html/herdstat/readline || \
		mkdir $(top_srcdir)/html/herdstat/readline
	@source-highlight -c ../../src.css -s cpp -f html -t4 -n -i $? -o \
		$(top_srcdir)/html/herdstat/readline/$@
