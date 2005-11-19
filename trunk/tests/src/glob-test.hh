/*
 * libherdstat -- tests/src/glob-test.hh
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

#ifndef _HAVE__GLOB_TEST_HH
#define _HAVE__GLOB_TEST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/util/glob.hh>
#include "test_handler.hh"

DECLARE_TEST_HANDLER(GlobTest)

void
GlobTest::operator()(const opts_type& null) const
{
    /* test Glob */
    char *test_data = std::getenv("TEST_DATA");
    assert(test_data);
    chdir(test_data);

    const herdstat::util::Glob results("portdir/*/*/*.ebuild");
    herdstat::util::Glob::const_iterator i;
    for (i = results.begin() ; i != results.end() ; ++i)
        std::cout << *i << std::endl;

    /* test patternMatch functor */
    herdstat::util::Glob::size_type n =
        std::count_if(results.begin(), results.end(),
            std::bind2nd(herdstat::util::patternMatch(), "*foo-1.10*"));
    if (n == 0)
        throw herdstat::Exception("*foo-1.10* not found in results vector.");

    std::cout << std::endl
        << "The pattern '*foo-1.10*' appears " << n
        << " times in the output above." << std::endl;
}

#endif /* _HAVE__GLOB_TEST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
