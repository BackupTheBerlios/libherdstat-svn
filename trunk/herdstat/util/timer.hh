/*
 * herdstat -- herdstat/util/timer.hh
 * $Id: timer.hh 605 2005-09-19 14:59:34Z ka0ttic $
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

#ifndef HAVE_TIMER_HH
#define HAVE_TIMER_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file timer.hh
 * @brief Defines the Timer class.
 */

#include <sys/time.h>

namespace herdstat {
namespace util {

    /**
     * Represents a timer.
     */

    class Timer
    {
        public:
            typedef long size_type;

            /// Default constructor.
            Timer();

            /// Start timer.
            void start();

            /// Stop timer.
	    void stop();

            /** Is the timer running?
             * @returns A boolean value.
             */
            inline bool is_running() const;

            /** How long has the timer been running?
             * @returns An long integer value.
             */
            inline size_type elapsed() const;

            /// Reset elapsed value.
            inline void reset();

        private:
	    timeval _begin, _end;
	    size_type _elapsed;
            bool _running;
    };

    inline bool
    Timer::is_running() const
    {
        return this->_running;
    }

    inline Timer::size_type
    Timer::elapsed() const
    {
        return this->_elapsed;
    }

    inline void
    Timer::reset()
    {
        this->_elapsed = 0;
    }

} // namespace util
} // namespace herdstat

#endif

/* vim: set tw=80 sw=4 et : */
