/*
 * libherdstat -- portage/devaway_xml.hh
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

#ifndef _HAVE_DEVAWAY_XML_HH
#define _HAVE_DEVAWAY_XML_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/devaway_xml.hh
 * @brief Defines the interface for Gentoo's devaway.xml.
 */

#include <herdstat/portage/xmlbase.hh>
#include <herdstat/portage/developer.hh>

namespace herdstat {
namespace portage {

    /**
     * @class devaway_xml devaway_xml.hh herdstat/portage/devaway_xml.hh
     * @brief Represents Gentoo's devaway.xml.
     */

    class devaway_xml : public xmlBase
    {
        public:
            /// Default constructor.
            devaway_xml();

            /** Constructor.
             * @param path Path to devaway.xml.
             */
            devaway_xml(const std::string& path);
            
            /// Destructor.
            virtual ~devaway_xml();

            /** Parse devaway.xml.
             * @param path Path to devaway.xml (defaults to empty).
             */
            virtual void parse(const std::string& path = "");
            
            /** Fill a Developer object with data we contain relevant to the
             * developer.  At the very least, the Developer's user name must
             * have been set prior to calling this function.
             * @param dev Reference to a Developer object.
             */
            virtual void fill_developer(Developer& dev) const;

            /// Get developers.
            inline const Developers& devs() const;
            /// Get developers.
            inline Developers& devs();

            /// Get vector of all usernames as well as all email addy's.
            const std::vector<std::string> keys() const;

        protected:
            virtual bool start_element(const std::string& name,
                                       const attrs_type& attrs);
            virtual bool end_element(const std::string& name);
            virtual bool text(const std::string& text);

        private:
            Developers _devs;
            static const char * const _local_default;
            bool in_devaway, in_dev, in_reason;
            Developers::iterator _cur_dev;
    };

    inline Developers& devaway_xml::devs() { return _devs; }
    inline const Developers& devaway_xml::devs() const { return _devs; }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_DEVAWAY_XML_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
