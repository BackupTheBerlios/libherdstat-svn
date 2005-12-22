/*
 * libherdstat -- herdstat/portage/atom.cc
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <cstdlib>
#include <cstring>
#include <herdstat/portage/util.hh>
#include <herdstat/portage/atom.hh>

namespace herdstat {
namespace portage {
/*** static members *********************************************************/
const char * const Atom::_valid_prefix_chars = "><=~!";
const char * const Atom::_valid_postfix_chars = "*";
/****************************************************************************/
Atom::Atom() throw()
    : _atom(), _pkg()
{
}
/****************************************************************************/
Atom::Atom(const std::string& atom) throw (InvalidAtom)
    : _atom(atom), _pkg()
{
    this->_parse();
}
/****************************************************************************/
Atom::~Atom() throw()
{
}
/****************************************************************************/
void
Atom::_parse() throw (InvalidAtom)
{
    std::string::size_type pos = _atom.find_first_not_of(_valid_prefix_chars);
    if (pos == std::string::npos)
        throw InvalidAtom(_atom);

    if (pos != 0)
        _prefix.assign(_atom.substr(0, pos - 1));
    _pkg.set_full(get_pkg_from_verstr(_atom.substr(pos)));
}
/****************************************************************************/
bool
Atom::operator==(const Atom& that) const
{
    return (
            (_pkg == that._pkg) and
            (_atom == that._atom) and
            (_prefix == that._prefix)
           );
}
/****************************************************************************/
bool
Atom::operator==(const std::string& verstr) const
{

    return false;
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
