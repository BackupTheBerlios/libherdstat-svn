/*
 * libherdstat -- herdstat/portage/config.hh
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

#ifndef HAVE_PORTAGE_CONFIG_HH
#define HAVE_PORTAGE_CONFIG_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/config.hh
 * @brief Defines the config class, the interface to Portage configuration.
 */

#include <vector>
#include <string>

#include <herdstat/noncopyable.hh>
#include <herdstat/exceptions.hh>
#include <herdstat/util/vars.hh>
#include <herdstat/portage/archs.hh>
#include <herdstat/portage/categories.hh>

namespace herdstat {
/**
 * @namespace herdstat::portage
 * @brief portage-related classes/functions.
 */
namespace portage {

    /**
     * @class config
     * @brief Represents the current portage configuration.
     */

    class config : private noncopyable
    {
        public:
            /// Get PORTDIR.
            inline const std::string& portdir() const;
            /// Get PORTDIR_OVERLAY
            inline const std::vector<std::string>& overlays() const;

            /** Get value of a portage configuration variable (anything in
             * make.conf/make.globals is valid).
             * @returns a copy of the value mapped to the specified variable
             * or an empty string if the value doesn't exist.
             */
            inline std::string operator[] (const std::string& var) const;

            /// Get categories.
            inline const Categories& categories() const;
            /// Get arch keywords.
            inline const Archs& archs() const;

        private:
            /// Only GlobalConfig() can instantiate this class.
            friend const config& GlobalConfig();

            /// Constructor.
            config();
            /// Destructor.
            ~config();

            util::vars _vars;
            std::string _portdir;
            std::vector<std::string> _overlays;
            mutable Categories *_cats;
            mutable Archs *_archs;
    };

    inline const std::string& config::portdir() const { return _portdir; }
    inline const std::vector<std::string>& config::overlays() const
    { return _overlays; }

    inline const Categories&
    config::categories() const
    {
        if (not _cats) _cats = new Categories(_portdir);
        return *_cats;
    }

    inline const Archs&
    config::archs() const
    {
        if (not _archs) _archs = new Archs(_portdir);
        return *_archs;
    }

    inline std::string
    config::operator[] (const std::string& var) const
    {
        util::vars::const_iterator i = _vars.find(var);
        return (i == _vars.end() ? std::string() : i->second);
    }

    /** Create a local static instance of the config class.
     * @returns const reference to the static instance.
     */
    inline const config&
    GlobalConfig()
    {
        static config c;
        return c;
    }

} // namespace portage
} // namespace herdstat

#endif

/* vim: set tw=80 sw=4 fdm=marker et : */
