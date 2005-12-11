/*
 * libherdstat -- herdstat/util/progress/ellipse.hh
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

#ifndef _HAVE_PROGRESS_ELLIPSE_HH
#define _HAVE_PROGRESS_ELLIPSE_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/util/progress/ellipse.hh
 * @brief Provides the EllipseMeter class definition.
 */

#include <herdstat/util/progress/meter.hh>

namespace herdstat {
namespace util {

    /**
     * @class EllipseMeter ellipse.hh herdstat/util/progress/ellipse.hh
     * @brief Concrete ProgressMeter implementation that shows an animated
     * ellipse ("...") repeatedly.
     */

    class EllipseMeter : public ProgressMeter
    {
        public:
            virtual ~EllipseMeter() throw();
            virtual void start() throw();
            virtual void increment(int cur) throw();

        private:
            friend class Progress;
            EllipseMeter() throw();

            unsigned short _cur;
    };

} // namespace util
} // namespace herdstat

#endif /* _HAVE_PROGRESS_ELLIPSE_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
