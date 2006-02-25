/*
 * libherdstat -- herdstat/util/progress/percent.cc
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

#include <herdstat/util/progress/percent.hh>

namespace herdstat {
namespace util {
/****************************************************************************/
PercentMeter::PercentMeter(const std::string& color)
    : ProgressMeter(color)
{
}
/****************************************************************************/
PercentMeter::~PercentMeter() throw()
{
    this->stop();
}
/****************************************************************************/
void
PercentMeter::do_start()
{
    std::printf("  0%%");
}
/****************************************************************************/
void
PercentMeter::do_stop()
{
    append_outlen(4);

    /* sometimes the user has to use an estimate as the value
     * passed to start(), so we may not have gotten to 100 yet. */
    while (this->cur() < 100.0)
        this->operator++();
}
/****************************************************************************/
void
PercentMeter::do_increment(int cur)
{
    if (cur < 10)
	std::printf("\b\b%.1d%%", cur);
    else if (cur < 100)
	std::printf("\b\b\b%.2d%%", cur);
    else
	std::printf("\b\b\b\b%.3d%%", cur);
}
/****************************************************************************/
} // namespace util
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
