CLEANFILES = $(VERSION)/*
MAINTAINERCLEANFILES = Makefile.in Doxyfile *~
EXTRA_DIST = Doxyfile.in

docs: Doxyfile
	@rm -fr $(VERSION)
	@doxygen
	@rm -f $(VERSION)/man/man3/_*
