/*
 * libherdstat -- herdstat/cachable.hh
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

#ifndef _HAVE_CACHABLE_HH
#define _HAVE_CACHABLE_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/cachable.hh
 * @brief Defines the cachable abstract class.
 */

#include <herdstat/noncopyable.hh>

namespace herdstat {

    /**
     * Abstract interface for cachable things.
     */

    class cachable : private noncopyable
    {
        public:
            /// Destructor.
            virtual ~cachable() { }

            /** Determine if cache is valid.
             * @returns True if valid.
             */
            virtual bool valid() const = 0;

            /// Fill cache.
            virtual void fill() = 0;

            /// Load cache.
            virtual void load() = 0;

            /// Dump cache.
            virtual void dump() = 0;

        protected:
            /** Constructor.
             * @param path Path of cache.
             */
            cachable(const std::string &path) : _path(path) { }

            /// Initialize cache.  Default cache logic.
            virtual void logic()
            {
                if (this->valid())
                    this->load();
                else
                {
                    this->fill();
                    this->dump();
                }
            }

            /** Get path of cache.
             * @returns const reference to std::string.
             */
            const std::string& path() const { return _path; }

        private:
            const std::string _path;
    };

} // namespace herdstat

#endif /* _HAVE_CACHABLE_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
