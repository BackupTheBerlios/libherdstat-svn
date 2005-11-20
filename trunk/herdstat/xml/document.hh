/*
 * libherdstat -- herdstat/xml/document.hh
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

#ifndef HAVE_XML_HH
#define HAVE_XML_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/xml/document.hh
 * @brief Defines the Document class template.
 */

#include <memory>
#include <herdstat/parsable.hh>
#include <herdstat/util/file.hh>
#include <herdstat/xml/exceptions.hh>
#include <herdstat/xml/saxparser.hh>

namespace herdstat {
/**
 * @namespace herdstat::xml
 * @brief XML-related classes.
 */
namespace xml {

    /**
     * @class Document document.hh herdstat/xml/document.hh
     * @brief Represents an XML document.
     */

    template <typename H>
    class Document : public parsable
    {
        public:
            typedef H handler_type;

            /// Default constructor.
            Document();

            /** Constructor.
             * @param path Path to XML document.
             */
            Document(const std::string& path);

            /// Destructor.
            virtual ~Document();

            /// Get pointer to underlying handler.
            H *handler() const { return this->_handler.get(); }

            /** Parse file.
             * @param path Path to XML file (defaults to empty).
             */
            virtual void parse(const std::string& path = "");

        private:
            const std::auto_ptr<H> _handler;    /* content handler */
    };

    template <typename H>
    Document<H>::Document() : parsable(), _handler(new H()) { }

    template <typename H>
    Document<H>::Document(const std::string &path)
        : parsable(path), _handler(new H())
    {
        BacktraceContext c("xml::Document::Document("+path+")");

        if (not util::is_file(path))
            throw FileException(path);

        this->parse();
    }

    template <typename H>
    Document<H>::~Document()
    {
    }

    template <typename H>
    void
    Document<H>::parse(const std::string &path)
    {
        const std::string file(path.empty() ? this->path() : path);
        saxparser p(this->_handler.get());
        this->timer().start();
        p.parse(file);
        this->timer().stop();
    }

} // namespace xml
} // namespace herdstat

#endif

/* vim: set tw=80 sw=4 fdm=marker et : */
