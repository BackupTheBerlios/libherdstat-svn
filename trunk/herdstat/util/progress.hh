/*
 * libherdstat -- herdstat/util/progress.hh
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

#ifndef HAVE_PROGRESS_HH
#define HAVE_PROGRESS_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/util/progress.hh
 * @brief Defines the Progress class.
 */

#include <cstdio>
#include <string>
#include <herdstat/util/progress/meter.hh>

namespace herdstat {
namespace util {

    /**
     * @class Progress progress.hh herdstat/util/progress.hh
     * @brief Represents the amount of progress on an operation.
     *
     * @section usage Usage
     *
     * To use the Progress class, you simply pass the total number of items to
     * process to the start() member.  When processing each item, you call
     * opertor++() to increment the progress.
     *
     * @section example Example
     *
     * Below is an example of using the Progress class to display the progress
     * of an operation:
     *
     * @include progress/main.cc
     *
     */

    class Progress
    {
	public:
            /** Constructor.
             * @param type Meter type.
             * @param color ASCII color sequence to show meter as (defaults to
             * "").
             */
	    Progress(const std::string& type = "percent",
                     const std::string& color = "") throw();

            /// Destructor.
            ~Progress() throw();

            /** Start progress.
             * @param total Number of total items to process.
             * @param title Title string to display before the progress meter.
             */
	    void start(unsigned total, const std::string& title = "") throw();

            /** Increment progress.
             * @returns false if not start()'d yet.
             */
	    inline bool operator++() throw();

	private:
            /// Current progress.
	    float _cur;
            /// Increment amount.
            float _step;
            /// Whether we've started yet.
            bool  _started;
            /// ASCII color sequence.
            const std::string _color;
            /// Pointer to meter implementation.
            ProgressMeter *_meter;
    };

    inline bool
    Progress::operator++() throw()
    {
        if (not _started)
            return false;

        _cur += _step;

        std::printf("%s", _color.c_str());
        _meter->increment(static_cast<int>(_cur));
        std::printf("\033[00m");

        std::fflush(stdout);
        return true;
    }

} // namespace util
} // namespace herdstat

#endif

/* vim: set tw=80 sw=4 fdm=marker et : */
