/*
 * libherdstat -- herdstat/portage/package_list.hh
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

#ifndef _HAVE_PORTAGE_PACKAGE_LIST_HH
#define _HAVE_PORTAGE_PACKAGE_LIST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/package_list.hh
 * @brief Defines the PackageList class.
 */

#include <herdstat/util/container_base.hh>
#include <herdstat/portage/package.hh>
#include <herdstat/portage/functional.hh>

namespace herdstat {
namespace portage {

    /**
     * @class PackageList package_list.hh herdstat/portage/package_list.hh
     * @brief Represents a sorted package list of all directories inside valid
     * categories.  Note that for speed reasons, no validation is done (other
     * than checking that it's a directory and it exists), so you should use
     * the portage::is_pkg_dir() function or the portage::IsPkgDir() function
     * object to validate an element before using it.
     */

    class PackageList : public util::VectorBase<Package>
    {
        public:
            /** Default constructor.
             * @param fill Fill with all packages in the tree?
             */
            PackageList(bool fill = true);

            /** Constructor.
             * @param portdir PORTDIR to search.
             * @param overlays const reference to a vector of strings denoting
             * overlays (defaults to empty).
             * @param fill Fill with all packages in the tree?
             */
            PackageList(const std::string& portdir, const std::vector<std::string>&
                overlays = std::vector<std::string>(), bool fill = true);

            /// Destructor.
            ~PackageList() throw();

            /// Fill container.
            void fill();
            /// Has our container been fill()'d?
            bool filled() const { return _filled; }

            ///@{
            /// Is the specified package present in our container?
            inline bool has_package(const std::string& pkg) const;
            inline bool has_package(const Package& pkg) const;
            ///@}

            /// Implicit conversion to const vector<Package>&
            operator const container_type&() const { return this->container(); }

        private:
            const std::string& _portdir;
            const std::vector<std::string>& _overlays;
            bool _filled;
    };

    inline bool
    PackageList::has_package(const std::string& pkg) const
    {
        return std::binary_search(this->begin(), this->end(), pkg);
    }

    inline bool
    PackageList::has_package(const Package& pkg) const
    {
        return has_package(pkg.full());
    }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_PORTAGE_PACKAGE_LIST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
