/*
 * libherdstat -- tests/src/glob-test.cc
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
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <cassert>
#include <unistd.h>

#include <herdstat/exceptions.hh>
#include <herdstat/util/glob.hh>
#include <herdstat/util/functional.hh>

using namespace herdstat;

int main()
{
    try
    {
        /* test Glob */
        char *test_data = std::getenv("TEST_DATA");
        assert(test_data);
        chdir(test_data);

        const util::Glob results("portdir/*/*/*.ebuild");
        util::Glob::const_iterator i;
        for (i = results.begin() ; i != results.end() ; ++i)
            std::cout << *i << std::endl;

        /* test patternMatch functor */
        util::Glob::size_type n = std::count_if(results.begin(), results.end(),
                std::bind2nd(util::patternMatch(), "*foo-1.10*"));
        if (n == 0)
            throw Exception("*foo-1.10* not found in results vector.");

        std::cout << std::endl
            << "The pattern '*foo-1.10*' appears " << n
            << " times in the output above." << std::endl;
    }
    catch (const BaseException& e)
    {
        std::cerr << e.backtrace(":\n  * ") << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/* vim: set tw=80 sw=4 fdm=marker et : */
