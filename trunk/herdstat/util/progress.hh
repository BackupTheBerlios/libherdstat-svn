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

#include <string>

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
@code
const herdstat::portage::PackageList pkgs;
herdstat::util::Progress progress;
progress.start(pkgs.size(), "Searching for all packages matching the criteria");
herdstat::portage::PackageList::const_iterator i;
for (i = pkgs.begin() ; i != pkgs.end() ; ++i)
{
    ++progress;
    ...
}
std::cout << std::endl;
@endcode
     *
     */

    class Progress
    {
	public:
            /// Default constructor.
	    Progress() throw();

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
    };

    inline bool
    Progress::operator++() throw()
    {
        if (not _started)
            return false;

        int incr = static_cast<int>(_cur += _step);
        if (incr < 10)
            std::printf("\b\b%.1d%%", incr);
        else if (incr < 100)
            std::printf("\b\b\b%.2d%%", incr);
        else
            std::printf("\b\b\b\b%.3d%%", incr);

        std::fflush(stdout);
        return true;
    }

} // namespace util
} // namespace herdstat

#endif

/* vim: set tw=80 sw=4 fdm=marker et : */
