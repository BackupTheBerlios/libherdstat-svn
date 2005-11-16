/*
 * libherdstat -- src/find-test.cc
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

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <herdstat/exceptions.hh>
#include <herdstat/portage/config.hh>
#include <herdstat/portage/package.hh>

using namespace herdstat;
using namespace herdstat::portage;

int
main(int argc, char **argv)
{
    try
    {
        PackageList pkgs;
        PackageFinder find(pkgs);
        const std::vector<Package>& results(find.results());
        const std::string& portdir(portage::GlobalConfig().portdir());

        {
            std::cout << "Testing PackageWhich" << std::endl;

            PackageWhich which;
            const std::vector<std::string>& results(which("foo", pkgs));
            assert(results.size() == 1);
            const std::string& result(results.front());

            std::cout << "  " << result.substr(portdir.length()+1) << std::endl;
        }

        try
        {
            std::cout << std::endl
                << "Testing PackageFinder with ambiguous package name" << std::endl;
            find.clear_results();
            find("libfoo");
            assert(results.size() > 1);
            throw AmbiguousPkg(results.begin(), results.end());
        }
        catch (const portage::AmbiguousPkg& e)
        {
            std::cerr << "  libfoo is ambiguous, matches are:" << std::endl;
            std::vector<std::string>::const_iterator i;
            for (i = e.packages.begin() ; i != e.packages.end() ; ++i)
                std::cerr << "    " << *i << std::endl;
        }

        {
            std::cout << std::endl
                << "Testing PackageFinder" << std::endl;
            find.clear_results();
            find("pfft");
            assert(results.size() == 1);
            const Package& result(results.front());
            std::cout << "  " << result.category() << "/" << result.name()
                << std::endl;
        }

        {
            std::cout << std::endl << "Testing PackageFinder w/regex:" << std::endl;
            find.clear_results();
            find(util::Regex("^foo"));
            assert(results.size() > 1);
            std::vector<Package>::const_iterator i;
            for (i = results.begin() ; i != results.end() ; ++i)
                std::cout << "  Found " << i->category() << "/" << i->name()
                    << std::endl;
             
        }
    }
    catch (const BaseException& e)
    {
        std::cerr << e.backtrace(":\n  * ") << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/* vim: set tw=80 sw=4 fdm=marker et : */
