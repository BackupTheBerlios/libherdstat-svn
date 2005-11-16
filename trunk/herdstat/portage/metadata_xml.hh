/*
 * libherdstat -- herdstat/portage/metadata_xml.hh
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

#ifndef _HAVE_METADATA_XML_HH
#define _HAVE_METADATA_XML_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/metadata_xml.hh
 * @brief Defines the interface for metadata.xml files.
 */

#include <herdstat/parsable.hh>
#include <herdstat/xml/saxparser.hh>
#include <herdstat/portage/metadata.hh>

namespace herdstat {
namespace portage {

    /**
     * @class metadata_xml
     * @brief Interface to Gentoo's metadata.xml files.
     */

    class metadata_xml : public parsable,
                         protected xml::saxhandler
    {
        public:
            /// Default constructor.
            metadata_xml();

            /** Constructor.
             * @param path Path to metadata.xml.
             * @param pkg Package name for this metadata.xml (defaults to
             * empty).
             */
            metadata_xml(const std::string& path,
                         const std::string& pkg = "");

            /// Destructor.
            virtual ~metadata_xml();

            /** Parse metadata.xml.
             * @param path Path to metadata.xml (defaults to empty).
             */
            virtual void parse(const std::string& path = "");

            /// Get data associated with this metadata.xml.
            inline const metadata& data() const;

            /* for convenience */
            /// Get long description.
            inline const std::string& longdesc() const;
            /// Get herds.
            inline const Herds& herds() const;
            /// Get developers.
            inline const Developers&  devs()  const;

        protected:
            virtual bool start_element(const std::string& name,
                                       const attrs_type& attrs);
            virtual bool end_element(const std::string& name);
            virtual bool text(const std::string& text);

        private:
            metadata _data;

            bool in_herd,
                 in_maintainer,
                 in_email,
                 in_name,
                 in_desc,
                 in_longdesc,
                 in_en_longdesc;

            Developers::iterator _cur_dev;
            std::string _longdesc;
    };

    inline const metadata& metadata_xml::data() const { return _data; }
    inline const Herds& metadata_xml::herds() const { return _data.herds(); }
    inline const Developers&  metadata_xml::devs()  const { return _data.devs(); }
    inline const std::string& metadata_xml::longdesc() const
    { return _data.longdesc(); }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_METADATA_XML_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
