/*
 * herdstat -- src/xmlparser.cc
 * $Id: saxparser.cc 558 2005-09-12 11:54:23Z ka0ttic $
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/xml/saxparser.hh>

namespace herdstat {
namespace xml {
/****************************************************************************/
saxhandler::~saxhandler()
{
}
/****************************************************************************/
saxparser::saxparser(saxhandler *handler)
    : _handler(handler)
{
}
/****************************************************************************/
saxparser::~saxparser()
{
}
/****************************************************************************/
void
saxparser::parse(const std::string &path) throw (ParserException)
{
    if (not this->_handler->parse_file(path.c_str()))
        throw ParserException(path, this->_handler->get_error_message());
}
/****************************************************************************/
} // namespace xml
} // namespace herdstat

/* vim: set tw=80 sw=4 et : */
