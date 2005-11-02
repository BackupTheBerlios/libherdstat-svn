/*
 * libherdstat -- herdstat/portage/package_list.hh
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

#ifndef _HAVE_PACKAGE_LIST_HH
#define _HAVE_PACKAGE_LIST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/package_list.hh
 * @brief Defines the PackageList class.
 */

#include <string>
#include <herdstat/util/container_base.hh>

#define PKGLIST_RESERVE            10130

namespace herdstat {
namespace portage {

    /**
     * @class PackageList
     * @brief Represents a sorted package list of the portage tree.
     */

    class PackageList : public util::VectorBase<std::string>
    {
        public:
            /// Default constructor.
            PackageList();

            /** Constructor.
             * @param portdir PORTDIR to search.
             * @param overlays const reference to a vector of strings denoting
             * overlays (defaults to empty).
             */
            PackageList(const std::string& portdir, const std::vector<std::string>&
                overlays = std::vector<std::string>());

            /// Fill container.
            void fill();

            /// Implicit conversion to const container_type&
            inline operator const container_type&() const;

        private:
            const std::string& _portdir;
            const std::vector<std::string>& _overlays;
    };

    inline PackageList::operator const PackageList::container_type&() const
    { return this->container(); }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_PACKAGE_LIST_HH */

/* vim: set tw=80 sw=4 et : */
