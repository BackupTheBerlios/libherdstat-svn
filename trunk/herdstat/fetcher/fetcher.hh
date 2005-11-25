/*
 * libherdstat -- herdstat/fetcher/fetcher.hh
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

#ifndef _HAVE_FETCHER_HH
#define _HAVE_FETCHER_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/fetcher/fetcher.hh
 * @brief Defines the Fetcher interface.
 */

#include <map>
#include <herdstat/noncopyable.hh>
#include <herdstat/fetcher/exceptions.hh>
#include <herdstat/fetcher/options.hh>

namespace herdstat {

    class FetcherImp;

    /**
     * @class Fetcher fetcher.hh herdstat/fetcher/fetcher.hh
     * @brief File fetcher.
     * @see Fetchable
     */

    /**
     * @section example Example
     *
     * Below is an example on using the Fetcher class.  It simply uses the
     * specified implementation to save the specified URL to the specified path.
     *
     * @include fetcher/main.cc
     */

    class Fetcher : private Noncopyable
    {
        public:
            /// Default constructor.
            Fetcher() throw();

            /** Constructor.
             * @param opts const reference to FetcherOptions object.
             */
            Fetcher(const FetcherOptions& opts) throw();

            /** Constructor.  Fetch url and save to path.
             * @param url URL string.
             * @param path Path to save to.
             * @exception FileException, FetchException, UnimplementedFetchMethod
             */
            Fetcher(const std::string& url, const std::string& path)
                throw (FileException, FetchException, UnimplementedFetchMethod);

            /// Destructor.
            ~Fetcher() throw();

            /// Get const reference to options object.
            const FetcherOptions& options() const { return _opts; }
            /// Set options object.
            void set_options(const FetcherOptions& opts) { _opts = opts; }

            /** Fetch url and save to path.
             * @param url URL string.
             * @param path Path to save to.
             * @exception FileException, FetchException, UnimplementedFetchMethod
             */
            void operator()(const std::string& url,
                            const std::string& path) const
                throw (FileException, FetchException, UnimplementedFetchMethod);

        private:
            /// initialize _impmap.
            void _init_imps();

            FetcherOptions _opts;
            // mutable so we can use operator[] in a const function
            mutable std::map<std::string, FetcherImp *> _impmap;
    };

} // namespace herdstat

#endif /* _HAVE_FETCHER_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
