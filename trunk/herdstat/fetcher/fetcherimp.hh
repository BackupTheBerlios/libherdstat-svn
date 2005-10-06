/*
 * herdstat -- herdstat/fetcher/fetcherimp.hh
 * $Id: fetcherimp.hh 636 2005-09-28 13:52:44Z ka0ttic $
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

#ifndef _HAVE_FETCHERIMP_HH
#define _HAVE_FETCHERIMP_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/fetcher/fetcherimp.hh
 * @brief Defines the FetcherImp abstract base class.
 */

#include <string>
#include <herdstat/fetcher/options.hh>

namespace herdstat {

    /**
     * Base class for different fetcher implementations.
     */

    class FetcherImp
    {
        public:
            /// Default constructor.
            FetcherImp() { }

            /// Destructor.
            virtual ~FetcherImp() { }

            /// Get const reference to options.
            inline const FetcherOptions& options() const;
            /// Set options.
            inline void set_options(const FetcherOptions& o);

            /** Fetch url and save to path.
             * @param url URL string.
             * @param path Path to file.
             */
            virtual bool fetch(const std::string& url,
                               const std::string& path) const = 0;

        private:
            FetcherOptions _opts;
    };

    inline const FetcherOptions& FetcherImp::options() const { return _opts; }
    inline void FetcherImp::set_options(const FetcherOptions& o) { _opts = o; }

} // namespace herdstat

#endif /* _HAVE_FETCHERIMP_HH */

/* vim: set tw=80 sw=4 et : */
