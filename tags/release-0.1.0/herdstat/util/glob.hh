/*
 * libherdstat -- herdstat/util/glob.hh
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

#ifndef HAVE_GLOB_HH
#define HAVE_GLOB_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/util/glob.hh
 * @brief Defines the Glob class.
 */

#include <string>
#include <glob.h>

#include <herdstat/util/container_base.hh>

namespace herdstat {
namespace util {

    /**
     * POSIX glob() interface.  Fills container with all files
     * matching a glob pattern.
     */

    class Glob : public util::VectorBase<std::string>
    {
        public:
            /** Constructor.
             * @param pattern Glob pattern string.
             */
            Glob(const char *pattern);

            /// Destructor.
            ~Glob();

        private:
            glob_t _glob;
    };

} // namespace util
} // namespace herdstat

#endif

/* vim: set tw=80 sw=4 et : */
