/*
 * herdstat -- src/xmlparser.hh
 * $Id$
 * Copyright (c) 2005 Aaron Walker <ka0ttic at gentoo.org>
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

#ifndef HAVE_PARSER_HH
#define HAVE_PARSER_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/xml/saxparser.hh
 * @brief Defines the saxparser/saxhandler classes.
 */

#include <xmlwrapp/event_parser.h>
#include <herdstat/noncopyable.hh>
#include <herdstat/xml/exceptions.hh>

namespace herdstat {
namespace xml {

    /**
     * Abstract SAX2 Content Handler.
     */

    class saxhandler : public ::xml::event_parser
    {
        public:
            /// Destructor.
            virtual ~saxhandler();

        protected:
            /// Callback called upon entering an element.
            virtual bool start_element(const std::string &,
                                       const attrs_type &) = 0;

            /// Callback called upon exiting an element.
            virtual bool end_element(const std::string &) = 0;

            /// Callback called upon encountering the text of an element.
            virtual bool text(const std::string &) = 0;
    };

    /**
     * SAX2 Parser.
     */

    class saxparser : private noncopyable
    {
        public:
            /** Constructor.
             * @param h pointer to a saxhandler object.
             */
            explicit saxparser(saxhandler *h);

            /// Destructor.
            virtual ~saxparser();

            /** Parse file.
             * @param path Path.
             * @exception ParserException.
             */
            virtual void parse(const std::string &path) throw (ParserException);

        protected:
            /// Get pointer to underlying saxhandler object.
            saxhandler *handler() const { return _handler; }

        private:
            saxhandler *_handler;
    };

} // namespace xml
} // namespace herdstat

#endif

/* vim: set tw=80 sw=4 et : */
