/*
 * libherdstat -- herdstat/fetcher/curlfetcher.hh
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

#ifndef _HAVE_CURLFETCHER_HH
#define _HAVE_CURLFETCHER_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/fetcher/curlfetcher.hh
 * @brief Defines the CurlFetcher concrete class.
 */

#include <herdstat/fetcher/fetcherimp.hh>

namespace herdstat {

    /**
     * Implement file fetching using libcurl.
     */

    class CurlFetcher : public FetcherImp
    {
        public:
            /// Default constructor.
            CurlFetcher();

            /// Destructor.
            virtual ~CurlFetcher();

            /** Fetch URL and save to path.
             * @param url URL string.
             * @param path Path.
             * @returns False if fetching failed.
             */
            virtual bool fetch(const std::string& url,
                               const std::string& path) const;
    };

} // namespace herdstat

#endif /* _HAVE_CURLFETCHER_HH */

/* vim: set tw=80 sw=4 et : */
