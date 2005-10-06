/*
 * herdstat -- herdstat/util/glob.hh
 * $Id: glob.hh 629 2005-09-26 11:54:23Z ka0ttic $
 * Copyright (c) 2005 Aaron Walker <ka0ttic@gentoo.org>
 *
 * This file is part of herdstat.
 *
 * herdstat is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * herdstat is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * herdstat; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 325, Boston, MA  02111-1257  USA
 */

#ifndef HAVE_GLOB_HH
#define HAVE_GLOB_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file glob.hh
 * @brief Defines the Glob class.
 */

#include <string>
#include <vector>
#include <glob.h>

namespace herdstat {
namespace util {

    /**
     * POSIX glob() interface.  Fills container with all files
     * matching a glob pattern.
     */

    class Glob
    {
        public:
            typedef std::vector<std::string> container_type;
            typedef container_type::const_iterator const_iterator;
            typedef container_type::size_type size_type;

            Glob(const char *pattern);
            ~Glob();

            const_iterator begin() const { return _results.begin(); }
            const_iterator end()   const { return _results.end(); }
            size_type size() const { return _results.size(); }
            bool empty() const { return _results.empty(); }

        private:
            glob_t _glob;
            container_type _results;
    };

} // namespace util
} // namespace herdstat

#endif

/* vim: set tw=80 sw=4 et : */
