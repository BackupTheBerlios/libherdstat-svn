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
#include <herdstat/portage/find.hh>
#include <herdstat/portage/exceptions.hh>

using namespace herdstat;

int
main(int argc, char **argv)
{
    try
    {
        const std::string& portdir(portage::GlobalConfig().portdir());
        std::cout << "Testing ebuild_which()" << std::endl;
        const std::string path = portage::ebuild_which("foo", false);
        assert(not path.empty());

        std::cout << "  " << path.substr(portdir.length()+1) << std::endl;

        try
        {
            std::cout << std::endl
                << "Testing find_package() with ambiguous package name" << std::endl;
            std::pair<std::string, std::string> search_results =
                portage::find_package("libfoo", false);
            assert(not search_results.first.empty() and
                   not search_results.second.empty());
            std::cout << "  " << search_results.second << std::endl;
        }
        catch (const portage::AmbiguousPkg& e)
        {
            std::cerr << "  libfoo is ambigious, matches are:" << std::endl;
            std::vector<std::string>::const_iterator i;
            for (i = e.packages.begin() ; i != e.packages.end() ; ++i)
                std::cerr << "    " << *i << std::endl;
        }

        std::cout << std::endl
            << "Testing find_package()" << std::endl;
        std::pair<std::string, std::string> search_results =
            portage::find_package("pfft", false);
        assert(not search_results.first.empty() and
               not search_results.second.empty());
        std::cout << "  " << search_results.second << std::endl;

        std::cout << std::endl << "Testing find_package_regex()" << std::endl;
        std::multimap<std::string, std::string> results_map =
            portage::find_package_regex(util::Regex("^foo"), false);
        std::multimap<std::string, std::string>::iterator i;
        for (i = results_map.begin() ; i != results_map.end() ; ++i)
            std::cout << "  Found " << i->second << std::endl;
    }
    catch (const BaseException& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/* vim: set tw=80 sw=4 et : */
