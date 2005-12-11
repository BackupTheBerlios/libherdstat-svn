/*
 * libherdstat -- herdstat/util/progress/meter.hh
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

#ifndef _HAVE_PROGRESS_METER_HH
#define _HAVE_PROGRESS_METER_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/util/progress/meter.hh
 * @brief Provides the ProgressMeter abstract class definition.
 */

#include <cstdio>
#include <herdstat/defs.hh>

namespace herdstat {
namespace util {

    /**
     * @class ProgressMeter meter.hh herdstat/util/progress/meter.hh
     * @brief Defines the abstract interface for progress meter implementations.
     */

    class ProgressMeter
    {
        public:
            virtual ~ProgressMeter() throw() { }
            /// start meter
            virtual void start() throw() = 0;
            /// increment progress
            virtual void increment(int cur) throw() = 0;

        protected:
            ProgressMeter() throw() { }
    };

} // namespace util
} // namespace herdstat

#endif /* _HAVE_PROGRESS_METER_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
