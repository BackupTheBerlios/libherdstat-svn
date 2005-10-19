/*
 * libherdstat -- herdstat/portage/developer.cc
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/portage/developer.hh>

namespace herdstat {
namespace portage {
/****************************************************************************/
Developer::Developer()
    : _user(), _email(), _name(), _pgpkey(), _joined(), _birth(),
      _status(), _role(), _location(), _awaymsg(), _away(false), _herds()
{
}
/****************************************************************************/
Developer::Developer(const std::string &user, const std::string &email,
                     const std::string &name)
    : _user(user), _email(email.empty() ? _user : email),
      _name(name), _pgpkey(), _joined(), _birth(), _status(),
      _role(), _location(), _awaymsg(), _away(false), _herds()
{
    /* chop everything after '@' if the caller
     * gave an email addy instead of the user name.
     */
    std::string::size_type pos = _user.find('@');
    if (pos != std::string::npos)
        _user.erase(pos);
}
/****************************************************************************/
Developer::~Developer()
{
}
/****************************************************************************/
Developers::Developers()
{
}
/****************************************************************************/
Developers::Developers(const container_type& v)
{
    *this = v;
}
/****************************************************************************/
Developers::Developers(const std::vector<std::string>& devs)
{
    *this = devs;
}
/****************************************************************************/
Developers::~Developers()
{
}
/****************************************************************************/
Developers&
Developers::operator= (const std::vector<std::string>& devs)
{
    this->clear();
    std::vector<std::string>::const_iterator i;
    for (i = devs.begin() ; i != devs.end() ; ++i)
        this->insert(Developer(*i));
    return *this;
}
/****************************************************************************/
Developers&
Developers::operator= (const container_type& v)
{
    this->clear();
    this->insert(v.begin(), v.end());
    return *this;
}
/****************************************************************************/
Developers::operator
std::vector<std::string>() const
{
    std::vector<std::string> v;
    std::transform(this->begin(), this->end(), std::back_inserter(v), User());
    return v;
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 et : */
