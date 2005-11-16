# Process this file with autoconf to produce a configure script.
# $Id: configure.ac 246 2005-04-26 12:03:53Z ka0ttic $

AC_PREREQ(2.59)
AC_INIT(herdstat/util/string.cc)

# release versioning
VERSION_MAJOR=0
VERSION_MINOR=2
VERSION_MICRO=0
VERSION_SUFFIX=
VERSION_SUFFIX_VERSION=
VERSION_FULL="$VERSION_MAJOR.$VERSION_MINOR.$VERSION_MICRO"

if ! test -z "$VERSION_SUFFIX" ; then
    VERSION_FULL="$VERSION_FULL"_"$VERSION_SUFFIX""$VERSION_SUFFIX_VERSION"
fi

AC_SUBST(VERSION_MAJOR)
AC_SUBST(VERSION_MINOR)
AC_SUBST(VERSION_MICRO)
AC_SUBST(VERSION_SUFFIX)
AC_SUBST(VERSION_SUFFIX_VERSION)
AC_SUBST(VERSION_FULL)

# shared lib versioning
LIBRARY_VERSION=1:0:0
#               | | |
#        +------+ | +---+
#        |        |     |
#        current:revision:age
#        |        |     |
#        |        |     +- increment if interfaces have been added
#        |        |        set to zero if interfaces have been removed
#                          or changed
#        |        +- increment if source code has changed
#        |           set to zero if current is incremented
#        +- increment if interfaces have been added, removed or changed
AC_SUBST(LIBRARY_VERSION)

VERSION=$VERSION_FULL

AC_CONFIG_AUX_DIR(config)
AM_INIT_AUTOMAKE(libherdstat, $VERSION_FULL)

test x$localstatedir = "xNONE" && localstatedir="$ac_default_localstatedir"
test x$sysconfdir = "xNONE" && sysconfdir="$ac_default_sysconfdir"
AC_DEFINE_UNQUOTED(LOCALSTATEDIR, "$localstatedir/herdstat", [Local state directory])
AC_DEFINE_UNQUOTED(SYSCONFDIR, "$sysconfdir", [System configuration directory])

dnl --enable-tests
AC_MSG_CHECKING([whether to build tests])
AC_ARG_ENABLE(tests,
    AC_HELP_STRING([--enable-tests],[Build tests]),
    [enable_tests=$enableval],[enable_tests=yes])
AM_CONDITIONAL(BUILD_TESTS, test x$enable_tests != "xno")
AC_MSG_RESULT([$enable_tests])

dnl --with-test-data
AC_ARG_WITH(test-data,
    AC_HELP_STRING([--with-test-data],[Directory where test data is located]),
    [TEST_DATA=$withval],[TEST_DATA=foo])
if test x"$TEST_DATA" = "xfoo" ; then
    TEST_DATA="${PWD}/../test-data"
fi
AC_SUBST(TEST_DATA)

dnl --enable-debug
AC_MSG_CHECKING([whether to enable debugging code/flags])
AC_ARG_ENABLE(debug,
    AC_HELP_STRING([--enable-debug],[Enable debugging code/flags]),
    [enable_debug=$enableval],[enable_debug=no])
AM_CONDITIONAL(DEBUG, test x$enable_debug != "xno")

if test x$enable_debug != "xno" ; then
    CXXFLAGS="-ggdb3 -Winline"
    AC_MSG_RESULT([$CXXFLAGS])
    AC_DEFINE(DEBUG, 1, [Enable debugging code])
else
    AC_MSG_RESULT(no)
fi

AC_LANG_CPLUSPLUS
AC_PROG_CXX
AC_PROG_MAKE_SET
AC_PROG_INSTALL

dnl hack to disable damn f77 libtool checks (stolen from sandbox's configure.in)
m4_undefine([AC_PROG_F77])
m4_defun([AC_PROG_F77],[])
AC_PROG_LIBTOOL

LIBTOOL="${LIBTOOL} --silent"
AC_SUBST(LIBTOOL)

dnl SED is defined by the LT_AC_PROG_SED ran by AC_PROG_LIBTOOL
AC_SUBST(SED)

AC_MSG_CHECKING([gcc version])
gccver=`${CC} -dumpversion | cut -f1 -d.`
AC_MSG_RESULT([$gccver])
if test x$gccver = "x4" ; then
    AC_DEFINE_UNQUOTED(HAVE_GCC4, 1, [GCC Version 4])
fi

dnl Required headers
AC_HEADER_STDC
AC_HEADER_TIME(,
    [AC_MSG_ERROR([sys/time.h is required])])
AC_HEADER_DIRENT(,
    [AC_MSG_ERROR([dirent.h is required])])
AC_CHECK_HEADERS(regex.h,,
    [AC_MSG_ERROR([regex.h is required])])
AC_CHECK_HEADERS(glob.h,,
    [AC_MSG_ERROR([glob.h is required])])
AC_CHECK_HEADERS(fnmatch.h,,
    [AC_MSG_ERROR([fnmatch.h is required])])

dnl Optional headers
AC_CHECK_HEADERS(getopt.h)

dnl Required functions
AC_FUNC_CLOSEDIR_VOID
AC_CHECK_FUNCS(gettimeofday,,
    [AC_MSG_ERROR([gettimeofday is required])])
AC_CHECK_FUNCS(regcomp,,
    [AC_MSG_ERROR([regcomp is required])])
AC_CHECK_FUNCS(regexec,,
    [AC_MSG_ERROR([regexec is required])])
AC_CHECK_FUNCS(regfree,,
    [AC_MSG_ERROR([regfree is required])])
AC_CHECK_FUNCS(regerror,,
    [AC_MSG_ERROR([regerror is required])])
AC_CHECK_FUNCS(glob,,
    [AC_MSG_ERROR([glob is required])])
AC_CHECK_FUNCS(fnmatch,,
    [AC_MSG_ERROR([fnmatch is required])])
AC_CHECK_FUNCS(vasprintf,,
    [AC_MSG_ERROR(vasprintf is required)])

dnl Optional functions

dnl Required libs
AC_MSG_CHECKING([fetch method])
AC_ARG_WITH(curl,
    AC_HELP_STRING([--with-curl],[Use libcurl for fetching]),
    [WITH_CURL=$withval],[WITH_CURL=yes])

if test "$WITH_CURL" = "yes" ; then
    AC_MSG_RESULT([libcurl])
    AC_CHECK_LIB(curl, curl_easy_init, [CURL_LIBS="-lcurl"])
    AC_CHECK_HEADERS([curl/curl.h])

    if ! test -z "$CURL_LIBS" ; then
	AC_DEFINE(FETCH_METHOD_CURL, 1, [Use libcurl for fetching])
    fi
fi
    
if test "$WITH_CURL" != "yes" -o -z "$CURL_LIBS" ; then
    AC_MSG_RESULT([wget])
    AC_PATH_PROGS(_WGET, wget)
    if test x$_WGET = "x"; then
	AC_MSG_ERROR([wget is required])
    fi
    AC_DEFINE_UNQUOTED(WGET, "$_WGET", [wget location])
    AC_DEFINE(FETCH_METHOD_WGET, 1, [Use wget for fetching])
fi

AC_SUBST(CURL_LIBS)

PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES(xmlwrapp, xmlwrapp >= 0.5.0,
    [xmlwrapp_LIBS="-lxmlwrapp -lxslt -lxml2 -lz -lm"],
    [AC_MSG_ERROR([xmlwrapp is required])])
AC_SUBST(xmlwrapp_LIBS)

AC_CHECK_HEADERS(libebt/libebt.hh,,
    AC_MSG_ERROR([libebt/libebt.hh is required]))

AM_CONFIG_HEADER(config.h)
AC_OUTPUT(Makefile
	  doc/Makefile
          doc/Doxyfile
	  herdstat/Makefile
	  herdstat/util/Makefile
	  herdstat/fetcher/Makefile
	  herdstat/xml/Makefile
	  herdstat/portage/Makefile
	  tests/Makefile
	  tests/src/Makefile)
