/*
 * libherdstat -- herdstat/util/progress/bar.cc
 * $Id$
 * Copyright (c) 2005 Aaron Walker <ka0ttic@gentoo.org>
 *
 * This file is part of libherdstat.
 *
 * libherdstat is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * libherdstat is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * libherdstat; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 325, Boston, MA  02111-1257  USA
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/util/getcols.hh>
#include <herdstat/util/progress/bar.hh>

namespace herdstat {
namespace util {

ProgressBar::ProgressBar(const std::string& color) throw()
    : ProgressMeter(color), _cols(0), _total(0), _cur(0), _step(0)
{
}

ProgressBar::~ProgressBar() throw()
{
}

void
ProgressBar::do_start() throw()
{
    _cols = util::getcols();
    _total = (_cols - 2);
    _step = (100.0 / _total);

    std::printf("\n[");
    for (std::size_t i = 0 ; i < _total ; ++i)
        std::printf(" ");
    std::printf("]");
}

void
ProgressBar::do_stop() throw()
{
    append_outlen(_cols);
}

void
ProgressBar::do_increment(int cur) throw()
{
    std::size_t inc = static_cast<std::size_t>(_cur += _step);
    if (inc >= 100)
        return;

    for (std::size_t i = 0 ; i < _cols ; ++i)
        std::printf("\b \b");

    std::printf("[");
    for (std::size_t i = 0 ; i < ( inc - 1 ) ; ++i)
        std::printf("=");
    std::printf(">");
    for (std::size_t i = 0 ; i < (_total - inc) ; ++i)
        std::printf(" ");
    std::printf("]");
}

} // namespace util
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
