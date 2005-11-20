/*
 * libherdstat -- tests/src/main.cc
 * $Id$
 * Copyright (c) 2005 Aaron Walker <ka0ttic@gentoo.org>
 *
 * This file is part of libherdstat.
 *
 * libherdstat is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * libherdstat is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * libherdstat; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 325, Boston, MA  02111-1257  USA
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <map>
#include <string>
#include <iostream>
#include <cstdlib>

#include <herdstat/exceptions.hh>

#include "algo-test.hh"
#include "container_base-test.hh"
#include "devaway.xml-test.hh"
#include "ebuild-test.hh"
#include "glob-test.hh"
#include "herds.xml-test.hh"
#include "license-test.hh"
#include "keyword-test.hh"
#include "metadata.xml-test.hh"
#include "package_finder-test.hh"
#include "package_list-test.hh"
#include "package_which-test.hh"
#include "regex-test.hh"
#include "string-test.hh"
#include "userinfo.xml-test.hh"
#include "version-test.hh"

int
main(int argc, char **argv)
{
    try
    {
        typedef std::map<std::string, TestHandler *> TestsMap;

        if (argc < 2)
            throw herdstat::Exception("usage: run_lhs_test <test> <test opts>");

        std::string test_id(argv[1]);

        opts_type opts;
        if (argc > 2)
            std::copy(argv+2, argv+argc, std::back_inserter(opts));

        TestsMap tests;
        tests["algo"]           = new AlgoTest();
        tests["container_base"] = new ContainerBaseTest();
        tests["devaway.xml"]    = new DevawayXMLTest();
        tests["ebuild"]         = new EbuildTest();
        tests["glob"]           = new GlobTest();
        tests["herds.xml"]      = new HerdsXMLTest();
        tests["keyword"]        = new KeywordTest();
        tests["license"]        = new LicenseTest();
        tests["metadata.xml"]   = new MetadataXMLTest();
        tests["package_finder"] = new PackageFinderTest();
        tests["package_list"]   = new PackageListTest();
        tests["package_which"]  = new PackageWhichTest();
        tests["regex"]          = new RegexTest();
        tests["string"]         = new StringTest();
        tests["userinfo.xml"]   = new UserinfoXMLTest();
        tests["version"]        = new VersionTest();

        TestHandler *test = tests[test_id];
        if (not test)
            throw herdstat::Exception("Unknown test '"+test_id+"'.");

        (*test)(opts);

        /* delete the TestHandler pointer for each element in the tests map */
        std::for_each(tests.begin(), tests.end(),
            herdstat::util::compose_f_gx(
                    herdstat::util::DeleteAndNullify<TestHandler>(),
                    herdstat::util::Second<TestsMap::value_type>()
                ));
    }
    catch (const herdstat::BaseException& e)
    {
        std::cerr << e.backtrace(":\n  * ") << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/* vim: set tw=80 sw=4 fdm=marker et : */
