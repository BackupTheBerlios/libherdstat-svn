/*
 * libherdstat -- herdstat/portage/atom.hh
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

#ifndef _HAVE_PORTAGE_ATOM_HH
#define _HAVE_PORTAGE_ATOM_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/atom.hh
 * @brief Provides the Atom class definition.
 */

#include <string>
#include <herdstat/util/container_base.hh>
#include <herdstat/portage/package.hh>

namespace herdstat {
namespace portage {

    /**
     * @class Atom atom.hh herdstat/portage/atom.hh
     * @brief Represents a DEPEND atom as described in the ebuild(5) manual
     * page.
     */

    class Atom
    {
        public:
            Atom();
            Atom(const std::string& atom);
            ~Atom() throw();

            void assign(const std::string& atom);

            ///@{
            /// Determine equivelance of this Atom compared to that Atom.
            bool operator==(const Atom& that) const;
            inline bool operator!=(const Atom& that) const
            { return not (*this == that); }
            ///@}

            ///@{
            /** Determine if the given version string matches this Atom.
             * @param verstr version string
             */
            bool operator==(const std::string& verstr) const;
            inline bool operator!=(const std::string& verstr) const
            { return not (*this == verstr); }
            ///@}

            /// Get const reference to Package object for this atom.
            const Package& package() const { return _pkg; }
            /// Get atom string.
            const std::string& str() const { return _atom; }
            /// Get prefix string.
            const std::string& prefix() const { return _prefix; }

        private:
            /// Parse atom string.
            void _parse();

            std::string _atom, _prefix;
            Package _pkg;
            static const char * const _valid_prefix_chars;
            static const char * const _valid_postfix_chars;
    };

    inline void
    Atom::assign(const std::string& atom)
    {
        _atom.assign(atom);
        this->_parse();
    }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_PORTAGE_ATOM_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
