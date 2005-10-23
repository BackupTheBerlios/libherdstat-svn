/*
 * libherdstat -- herdstat/portage/license.hh
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

#ifndef _HAVE_LICENSE_HH
#define _HAVE_LICENSE_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/license.hh
 * @brief Defines the License class.
 */

#include <string>

namespace herdstat {
namespace portage {

    /**
     * @class License
     * @brief Represents a LICENSE string.
     */

    class License
    {
        public:
            /** Default constructor.
             * @param validate Bail if an invalid license is found?
             */
            License(bool validate = false);

            /** Constructor.
             * @param str License string as found in an ebuild.
             * @param validate Bail if an invalid license is found?
             */
            License(const std::string& str, bool validate = false);

            /** Assign new license string.
             * @param str License string as found in an ebuild.
             * @param validate Bail if an invalid license is found?
             */
            inline void assign(const std::string& str, bool validate = false);

            /// Get license string.
            inline const std::string& str() const;

            /// Implicit conversion to std::string.
            inline operator const std::string&() const;

        private:
            void parse();

            bool _validate;
            std::string _license;
    };

    inline void
    License::assign(const std::string& str, bool validate)
    {
        _validate = validate;
        _license = str;
        this->parse();
    }

    inline const std::string&
    License::str() const
    {
        return _license;
    }

    inline License::operator
    const std::string&() const
    {
        return _license;
    }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_LICENSE_HH */

/* vim: set tw=80 sw=4 et : */
