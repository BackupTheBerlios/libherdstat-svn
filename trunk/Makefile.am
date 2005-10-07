# $Id$

AUTOMAKE_OPTIONS = 1.8 dist-bzip2 no-dist-gzip

SUBDIRS = herdstat doc

MAINTAINERCLEANFILES = aclocal.m4 \
		       configure \
		       Makefile.in \
		       config/* \
		       config.h.in \
		       stamp-h.in \
		       html/*/*.html \
		       *~

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = $(PACKAGE)-$(VERSION_MAJOR).$(VERSION_MINOR).pc

DISTCLEANFILES = ChangeLog TODO $(pkgconfig_DATA)
EXTRA_DIST = ChangeLog Makefile.am.common autogen.sh .todo tests \
	$(pkgconfig_DATA).in

docs:
	cd doc && $(MAKE) $@

check:
	cd tests && $(MAKE) $@

srchtml:
	@test -d ${PWD}/html || mkdir ${PWD}/html ; \
	for x in herdstat ; do \
		if test -d ${PWD}/html/$${x} ; then \
			rm -fr ${PWD}/html/$${x}/* ; \
		else \
			mkdir ${PWD}/html/$${x} ; \
		fi ; \
		cd ${PWD}/$${x} && $(MAKE) $@ ; \
	done

TODO: .todo
	@test -x $(prefix)/bin/devtodo && devtodo all --TODO

clitimestamp:
	@touch clitimestamp

ChangeLog: clitimestamp
	@if test -d $(top_srcdir)/.svn -a -x $(prefix)/bin/svn2cl ; then \
                svn up $(top_srcdir) ; \
                svn2cl --group-by-day --include-rev --stdout | \
                        @SED@ -e 's|\(ka0ttic\)|Aaron Walker <\1@gentoo.org>|' \
                        > $@; \
        else \
                touch ChangeLog; \
        fi
	@rm clitimestamp

pkgconfig:
	cp $(PACKAGE).pc $(pkgconfig_DATA)

distcheck-hook:
	@cp Makefile.am.common "$(PACKAGE)-$(VERSION)/_build/"

dist-hook: ChangeLog TODO pkgconfig

dist-sign: dist
	gpg --armour --detach-sign "$(PACKAGE)-$(VERSION).tar.bz2"

dist-upload: dist-sign
	echo -ne "user anonymous $(PACKAGE)\ncd incoming\nput $(PACKAGE)-$(VERSION).tar.bz2\nput $(PACKAGE)-$(VERSION).tar.bz2.asc\nbye" | \
		ftp -n ftp.berlios.de
