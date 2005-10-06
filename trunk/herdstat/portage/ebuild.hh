/*
 * herdstat -- portage/ebuild.hh
 * $Id: ebuild.hh 614 2005-09-21 13:53:35Z ka0ttic $
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

#ifndef _HAVE_EBUILD_HH
#define _HAVE_EBUILD_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/ebuild.hh
 * @brief Defines the ebuild class.
 */

#include <herdstat/util/vars.hh>

namespace herdstat {
namespace portage {

    /**
     * Represents ebuild variables.  This is really identical to util::vars,
     * except it defines do_set_defaults() and inserts variables that should
     * be pre-existing (${PN}, ${P}, etc).
     */

    class ebuild : public util::vars
    {
        public:
            /// Default constructor.
            ebuild();

            /** Constructor.
             * @param path Path to ebuild.
             */
            ebuild(const std::string &path);

            /// Destructor.
            virtual ~ebuild();

        protected:
            /// Set default variables.
            virtual void do_set_defaults();
    };

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_EBUILD_HH */

/* vim: set tw=80 sw=4 et : */
