/*
 * libherdstat -- src/ebuild-test.cc
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
#include <herdstat/portage/ebuild.hh>

using namespace herdstat;

int
main(int argc, char **argv)
{
    assert(argc == 2);

    try
    {
        const portage::ebuild ebuild(argv[1]);
        for (portage::ebuild::const_iterator i = ebuild.begin() ;
                i != ebuild.end() ; ++i)
        {
            if (i->first != "HOME")
                std::cout << i->first << " = " << i->second << std::endl;
        }
    }
    catch (const BaseException& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/* vim: set tw=80 sw=4 et : */
