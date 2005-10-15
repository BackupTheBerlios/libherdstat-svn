include $(top_builddir)/Makefile.am.common

noinst_PROGRAMS = string-test \
		  glob-test \
		  regex-test \
		  algo-test \
		  version-test \
		  keyword-test \
		  license-test \
		  herds.xml-test \
		  devaway.xml-test \
		  userinfo.xml-test \
		  metadata.xml-test

LDADD = $(top_builddir)/herdstat/libherdstat.la

string_test_SOURCES = string-test.cc
glob_test_SOURCES = glob-test.cc
regex_test_SOURCES = regex-test.cc
algo_test_SOURCES = algo-test.cc
version_test_SOURCES = version-test.cc
keyword_test_SOURCES = keyword-test.cc
license_test_SOURCES = license-test.cc
herds_xml_test_SOURCES = herds.xml-test.cc
devaway_xml_test_SOURCES = devaway.xml-test.cc
userinfo_xml_test_SOURCES = userinfo.xml-test.cc
metadata_xml_test_SOURCES = metadata.xml-test.cc

MAINTAINERCLEANFILES = Makefile.in *~ .loT
