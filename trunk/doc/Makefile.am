CLEANFILES = $(VERSION)/*
MAINTAINERCLEANFILES = Makefile.in Doxyfile *~
EXTRA_DIST = Doxyfile.in

docs: Doxyfile
	@rm -fr $(VERSION)
	@doxygen
