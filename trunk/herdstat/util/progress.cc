/*
 * libherdstat -- herdstat/util/progress.cc
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

#include <cstdio>
#include <herdstat/util/progress.hh>

namespace herdstat {
namespace util {
/****************************************************************************/
Progress::Progress() throw()
    : _cur(0), _step(0), _started(false)
{
}
/****************************************************************************/
Progress::~Progress() throw()
{
    if (not _started) return;
    /* sometimes the user has to use an estimate as the value
     * passed to start(), so we may not have gotten to 100 yet. */
    while (_cur < 100.0) this->operator++();
}
/****************************************************************************/
void
Progress::start(unsigned total, const std::string& title) throw()
{
    if (_started) return;
    _started = true;
    
    _step = 100.0 / total;

    if (not title.empty())
        std::printf("%s: ", title.c_str());

    std::printf("  0%%");
}
/****************************************************************************/
} // namespace util
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
