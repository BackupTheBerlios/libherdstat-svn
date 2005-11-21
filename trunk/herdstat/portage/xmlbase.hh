/*
 * libherdstat -- herdstat/portage/xmlbase.hh
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

#ifndef _HAVE_XMLBASE_HH
#define _HAVE_XMLBASE_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/xmlbase.hh
 * @brief Defines the xmlBase abstract base class.
 */

#include <string>
#include <herdstat/parsable.hh>
#include <herdstat/noncopyable.hh>
#include <herdstat/xml/saxparser.hh>

namespace herdstat {
namespace portage {

    class Developer;

    /**
     * @class xmlBase xmlbase.hh herdstat/portage/xmlbase.hh
     * @brief Abstract base class for portage-specific XML files.
     */

    class xmlBase : public Parsable,
                    protected xml::SAXHandler,
                    private Noncopyable
    {
        public:
            /// Default constructor.
            xmlBase() throw() : Parsable() { }

            /** Constructor.
             * @param path Path to XML file.
             */
            xmlBase(const std::string& path) throw()
                : Parsable(path) { }

            /// Destructor.
            virtual ~xmlBase() throw() { }

            /** Parse file.
             * @param path Path to XML file (defaults to empty).
             * @exception FileException, xml::ParserException
             */
            virtual void parse(const std::string& path = "")
                throw (FileException, xml::ParserException) = 0;

            /** Fill Developer object with data relevant to that developer.
             * @param dev Reference to Developer object.
             * @exception Exception
             */
            virtual void fill_developer(Developer& dev) const
                throw (Exception) = 0;

        protected:
            /* SAX2 callbacks */
            virtual bool start_element(const std::string& name,
                                       const attrs_type&  attrs) = 0;
            virtual bool end_element(const std::string& name) = 0;
            virtual bool text(const std::string& text) = 0;
    };

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_XMLBASE_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
