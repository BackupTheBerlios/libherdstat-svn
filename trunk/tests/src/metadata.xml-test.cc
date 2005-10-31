/*
 * libherdstat -- herdstat/metadata_xml.cc
 * $Id$
 * Copyright (c) 2005 Aaron Walker <ka0ttic@gentoo.org>
 *
 * This file is part of libherdstat.
 *
 * libherdstat is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * libherdstat is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * libherdstat; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 325, Boston, MA  02111-1257  USA
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <cstdlib>
#include <iostream>
#include <herdstat/exceptions.hh>
#include <herdstat/util/string.hh>
#include <herdstat/xml/init.hh>
#include <herdstat/portage/metadata_xml.hh>

using namespace herdstat;
using namespace herdstat::portage;

int
main(int argc, char **argv)
{
    try
    {
        if (argc != 2)
            throw Exception("usage: metadata_xml <path>");

        herdstat::xml::GlobalInit();

        std::string path(argv[1]);
        metadata_xml meta(path);
        const Herds& herds = meta.herds();
        const Developers& devs  = meta.devs();

        std::cout << "herds: ";
        for (Herds::const_iterator i = herds.begin() ; i != herds.end() ; ++i)
            std::cout << i->name() << " ";
        std::cout << std::endl;

        std::cout << "devs: ";
        for (Developers::const_iterator i = devs.begin() ; i != devs.end() ; ++i)
            std::cout << i->user() << " ";
        std::cout << std::endl;

        if (not meta.longdesc().empty())
        {
            std::cout << "longdesc: " << meta.longdesc() << std::endl;
            std::cout << "tidy longdesc: "
                << util::tidy_whitespace(meta.longdesc()) << std::endl;
        }
    }
    catch (const BaseException &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/* vim: set tw=80 sw=4 et : */
