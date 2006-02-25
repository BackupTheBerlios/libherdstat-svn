/*
 * libherdstat -- herdstat/util/timer.cc
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

#include <cstddef>
#include <herdstat/util/timer.hh>

namespace herdstat {
namespace util {
/****************************************************************************/
Timer::Timer()
    : _begin(), _end(), _elapsed(0), _running(false)
{
}
/****************************************************************************/
Timer::~Timer()
{
}
/****************************************************************************/
void
Timer::start()
{
    if (_running) return;
    _running = true;
    gettimeofday(&_begin, NULL);
}
/****************************************************************************/
void
Timer::stop()
{
    if (not _running) return;
    _running = false;

    gettimeofday(&_end, NULL);
    size_type tmp(_elapsed);
    _elapsed = _end.tv_sec - _begin.tv_sec;
    _elapsed *= 1000;
    _elapsed += (_end.tv_usec - _begin.tv_usec) / 1000;
    _elapsed += tmp;
}
/****************************************************************************/
} // namespace util
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
