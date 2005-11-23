CLEANFILES = $(VERSION)/html/* $(VERSION)/man/*/*
MAINTAINERCLEANFILES = Makefile.in Doxyfile *~
EXTRA_DIST = Doxyfile.in header.html footer.html doxygen.css

doxygen: Doxyfile
	@rm -fr $(VERSION)
	@doxygen
	@rm -f $(VERSION)/man/man3/_*
