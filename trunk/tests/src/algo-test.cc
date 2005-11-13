/*
 * libherdstat -- tests/src/algo-test.cc
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

#include <iostream>
#include <cstdlib>
#include <vector>
#include <iterator>

#include <herdstat/exceptions.hh>
#include <herdstat/util/algorithm.hh>

using namespace herdstat;

int main()
{
    try
    {
        std::vector<int> v1, v2;
        v1.push_back(1);
        v1.push_back(10);
        v1.push_back(20);
        v1.push_back(199);
        v1.push_back(-5);

        std::cout << "original v1 = ";
        std::copy(v1.begin(), v1.end(),
            std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;

        /* for each element > 10, add 5 to it and insert it into v2 */
        std::cout << "testing transform_if()" << std::endl;
        util::transform_if(v1.begin(), v1.end(), std::back_inserter(v2),
            std::bind2nd(std::greater<int>(), 10),
            std::bind2nd(std::plus<int>(), 5));

        std::cout << "  resulting v2 = ";
        std::copy(v2.begin(), v2.end(),
            std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        v2.clear();

        /* copy elements > 11 */
        std::cout << "testing copy_if()" << std::endl;
        util::copy_if(v1.begin(), v1.end(), std::back_inserter(v2),
            std::bind2nd(std::greater<int>(), 11));

        std::cout << "  resulting v2 = ";
        std::copy(v2.begin(), v2.end(),
            std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        v2.clear();

        std::cout << "testing all_equal()" << std::endl;
        std::cout << "  v1 = ";
        std::copy(v1.begin(), v1.end(),
            std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl << "  all_equal(v1.begin(), v1.end()) ? "
            << std::boolalpha << util::all_equal(v1.begin(), v1.end())
            << std::endl;
        std::cout << "  all_equal(v1.begin(), v1.end(), std::plus<int>(5)) ? "
            << util::all_equal(v1.begin(), v1.end(),
                std::bind2nd(std::plus<int>(), 5)) << std::endl;

        v2.push_back(1);
        v2.push_back(1);
        std::cout << "  v2 = ";
        std::copy(v2.begin(), v2.end(),
            std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl << "  all_equal(v2.begin(), v2.end()) ? "
            << std::boolalpha << util::all_equal(v2.begin(), v2.end())
            << std::endl;
        std::cout << "  all_equal(v2.begin(), v2.end(), std::plus<int>(5)) ? "
            << util::all_equal(v2.begin(), v2.end(),
                std::bind2nd(std::plus<int>(), 5)) << std::endl;
    }
    catch (const Exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/* vim: set tw=80 sw=4 et : */
