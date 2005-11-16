/*
 * libherdstat -- src/parsable.hh
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

#ifndef HAVE_PARSABLE_HH
#define HAVE_PARSABLE_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/parsable.hh
 * @brief Defines the parsable abstract interface.
 */

#include <string>
#include <herdstat/util/timer.hh>

namespace herdstat {

    /*
     * Defines an abstract base class for parsable things.
     */

    class parsable
    {
        public:
            typedef util::Timer timer_type;

            /// Default constructor.
            parsable() : _path(), _timer() { }

            /** Constructor.
             * @param path Path of parsable file.
             */
            parsable(const std::string& path) : _path(path), _timer() { }
            
            /// Destructor.
            virtual ~parsable() { }

            /** Parse specified file.
             * @param path Path of parsable file (defaults to empty).
             */
            virtual void parse(const std::string& path = "") = 0;

            /// Get path of parsable file.
            const std::string &path() const { return _path; }
            /// Get elapsed time it took to parse.
            timer_type::size_type elapsed() const { return _timer.elapsed(); }

        protected:
            /** Set path of parsable file.
             * @param path Path of parsable file.
             */
            void set_path(const std::string &path) const { _path.assign(path); }

            /// Get reference to timer object.
            timer_type& timer() { return _timer; }

        private:
            mutable std::string _path;
            timer_type  _timer;
    };

} // namespace herdstat

#endif /* HAVE_PARSABLE_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
