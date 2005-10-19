/*
 * libherdstat -- src/version-test.cc
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

#include <herdstat/exceptions.hh>
#include <herdstat/portage/misc.hh>
#include <herdstat/portage/version.hh>

using namespace herdstat;

int main(int argc, char **argv)
{
    assert(argc == 2);

    try
    {
        std::cout << "Testing version_string:" << std::endl;

        {
            const util::Directory dir(argv[1]);
            util::Directory::const_iterator d;
            for (d = dir.begin() ; d != dir.end() ; ++d)
            {
                if (portage::is_ebuild(*d))
                {
                    portage::version_string ver(*d);
                    std::cout << "  found version '" << ver.str() << "'." << std::endl;
                }
            }
        }

        std::cout << std::endl
            << "Testing sorted version_string container:" << std::endl;

        std::string ebuild;

        const portage::versions versions(argv[1]);
        portage::versions::const_iterator i;
        for (i = versions.begin() ; i != versions.end() ; ++i)
        {
            std::cout << "  " << i->str() << std::endl;    
            ebuild.assign(i->ebuild());
        }

        std::cout << std::endl
            << "Testing version_map for " << ebuild << ": " << std::endl;
    
        const portage::version_map vmap(ebuild);
        portage::version_map::const_iterator v;
        for (v = vmap.begin() ; v != vmap.end() ; ++v)
            std::cout << "  " << v->first << " = " << v->second << std::endl;
    }
    catch (const BaseException& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/* vim: set tw=80 sw=4 et : */
