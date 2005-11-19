/*
 * libherdstat -- herdstat/portage/package_finder.hh
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

#ifndef _HAVE_PORTAGE_PACKAGE_FINDER_HH
#define _HAVE_PORTAGE_PACKAGE_FINDER_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/util/timer.hh>
#include <herdstat/util/algorithm.hh>
#include <herdstat/portage/package_list.hh>

namespace herdstat {
namespace portage {

    /**
     * @class PackageFinder
     * @brief Interface for portage package searching.
     */

    class PackageFinder
    {
        public:
            /** Constructor.
             * @param pkglist const reference to a PackageList object.
             */
            PackageFinder(const PackageList& pkglist);

            /// Destructor.
            ~PackageFinder();

            /// Clear search results.
            void clear_results() { _results.clear(); }
            /// Get search results.
            const std::vector<Package>& results() const { return _results; }

            /** Perform search on the given criteria.
             * @param v const reference to either a std::string or a
             * util::Regex.
             * @param timer pointer to a util::Timer instance (defaults to
             * NULL).
             * @returns const reference to search results.
             */
            template <typename T>
            const std::vector<Package>&
            operator()(const T& v, util::Timer *timer = NULL)
                throw (NonExistentPkg);

            const std::vector<Package>&
            operator()(const char * const v, util::Timer *timer = NULL)
                throw (NonExistentPkg)
            { return operator()(std::string(v), timer); }

        private:
            const PackageList& _pkglist;
            std::vector<Package> _results;
    };

    PackageFinder::PackageFinder(const PackageList& pkglist)
        : _pkglist(pkglist), _results()
    {
    }

    PackageFinder::~PackageFinder()
    {
    }

    template <typename T>
    const std::vector<Package>&
    PackageFinder::operator()(const T& v, util::Timer *timer) throw (NonExistentPkg)
    {
        BacktraceContext c("herdstat::portage::PackageFinder::operator()");

        if (timer and not timer->is_running())
            timer->start();

        /* copy those packages in _pkglist that
         *      a) match the given criteria (v), and
         *      b) have a valid package directory
         * to our _results vector.
         */
        util::copy_if(_pkglist.begin(), _pkglist.end(),
            std::back_inserter(_results),
            util::compose_f_gx_hx(std::logical_and<bool>(),
                    std::bind2nd(PackageMatches<T>(), v),
                    PackageIsValid()));

        if (timer)
            timer->stop();

        if (_results.empty())
            throw NonExistentPkg(v);

        return _results;
    }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_PORTAGE_PACKAGE_FINDER_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
