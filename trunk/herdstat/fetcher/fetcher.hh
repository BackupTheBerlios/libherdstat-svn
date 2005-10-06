/*
 * herdstat -- herdstat/fetcher/fetcher.hh
 * $Id: fetcher.hh 636 2005-09-28 13:52:44Z ka0ttic $
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

#ifndef _HAVE_FETCHER_HH
#define _HAVE_FETCHER_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file fetcher.hh
 * @brief Defines the Fetcher interface.
 */

#include <herdstat/noncopyable.hh>
#include <herdstat/fetcher/fetcherimp.hh>

namespace herdstat {

    /**
     * File fetcher.  This is the interface meant to be used by clients.
     */

    class Fetcher : private noncopyable
    {
        public:
            /// Default constructor.
            Fetcher();

            /** Constructor.
             * @param opts Reference to FetcherOptions object.
             */
            Fetcher(const FetcherOptions& opts);

            /** Constructor.  Fetch url and save to path.
             * @param url URL string.
             * @param path Path to save to.
             */
            Fetcher(const std::string& url, const std::string& path);

            /// Destructor.
            ~Fetcher();

            /// Get const reference to options object.
            inline const FetcherOptions& options() const;
            /// Set options object.
            inline void set_options(const FetcherOptions& opts);

            /** Fetch url and save to path.
             * @param url URL string.
             * @param path Path to save to.
             */
            void operator()(const std::string& url, const std::string& path) const;

        private:
            void newFetcherImp();
            FetcherImp *_imp;
    };

    inline const FetcherOptions&
    Fetcher::options() const
    {
        return _imp->options();
    }

    inline void
    Fetcher::set_options(const FetcherOptions& opts)
    {
        _imp->set_options(opts);
    }

} // namespace herdstat

#endif /* _HAVE_FETCHER_HH */

/* vim: set tw=80 sw=4 et : */
