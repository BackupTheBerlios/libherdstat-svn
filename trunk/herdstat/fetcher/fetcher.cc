/*
 * libherdstat -- herdstat/fetcher/fetcher.cc
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
#include <unistd.h>

#include <herdstat/util/string.hh>
#include <herdstat/fetcher/fetcherimp.hh>
#include <herdstat/fetcher/fetcher.hh>

namespace herdstat {
/****************************************************************************/
Fetcher::Fetcher() throw()
    : _opts(), _impmap(_opts)
{
}
/****************************************************************************/
Fetcher::Fetcher(const FetcherImpMap& impmap, const FetcherOptions& opts)
    throw()
    : _opts(opts), _impmap(impmap)
{
}
/****************************************************************************/
Fetcher::Fetcher(const FetcherOptions& opts) throw()
    : _opts(opts), _impmap(opts)
{
}
/****************************************************************************/
Fetcher::Fetcher(const std::string& url,
                 const std::string& path,
                 const FetcherOptions& opts)
    throw (FileException, FetchException, UnimplementedFetchMethod)
    : _opts(opts), _impmap(opts)
{
    this->operator()(url, path);
}
/****************************************************************************/
Fetcher::~Fetcher() throw()
{
}
/****************************************************************************/
void
Fetcher::operator()(const std::string& url, const std::string& path) const
    throw (FileException, FetchException, UnimplementedFetchMethod)
{
    BacktraceContext c("Fetcher::operator()("+url+", "+path+")");
    assert(not _opts.implementation().empty());

    std::cerr << "_opts.implementation() == '" << _opts.implementation()
        << "'." << std::endl;
    std::cerr << "FetcherImpMap contents: " << std::endl;
    FetcherImpMap::const_iterator i;
    for (i = _impmap.begin() ; i != _impmap.end() ; ++i)
        std::cerr << "imp: " << i->first << std::endl;

    const FetcherImp * const imp = _impmap[_opts.implementation()];
    if (not imp)
        throw UnimplementedFetchMethod(_opts.implementation());

    /* make sure we have write access to the directory */
    const char * const dir = util::dirname(path).c_str();
    if (access(dir, W_OK) != 0)
        throw FileException(dir);

    if (_opts.verbose())
        std::cerr << "Fetching " << url << std::endl;

    if (not imp->fetch(url, path))
        throw FetchException();
}
/****************************************************************************/
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
