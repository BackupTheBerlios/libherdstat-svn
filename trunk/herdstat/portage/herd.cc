/*
 * libherdstat -- herdstat/portage/herd.cc
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

#include <herdstat/portage/herd.hh>

namespace herdstat {
namespace portage {
/****************************************************************************/
Herd::Herd()
    : Developers(), _name(), _email(), _desc()
{
}
/****************************************************************************/
Herd::Herd(const std::string &name,
           const std::string &email, const std::string &desc)
    : Developers(), _name(name), _email(email.empty() ? name : email),
      _desc(desc)
{
    /* chop everything after '@' if the caller
     * gave the email addy instead of the herd name.
     */
    std::string::size_type pos = _name.find('@');
    if (pos != std::string::npos)
        _name.erase(pos);
}
/****************************************************************************/
Herd::Herd(const container_type& v)
    : Developers(v), _name(), _email(), _desc()
{
}
/****************************************************************************/
Herd::Herd(const std::vector<std::string>& devs)
    : Developers(devs), _name(), _email(), _desc()
{
}
/****************************************************************************/
Herd::~Herd()
{
}
/****************************************************************************/
Herds::Herds()
{
}
/****************************************************************************/
Herds::Herds(const container_type& v)
{
    *this = v;
}
/****************************************************************************/
Herds::~Herds()
{
}
/****************************************************************************/
Herds&
Herds::operator= (const std::vector<std::string>& herds)
{
    this->clear();
    
    std::vector<std::string>::const_iterator i;
    for (i = herds.begin() ; i != herds.end() ; ++i)
        this->insert(Herd(*i));
    
    return *this;
}
/****************************************************************************/
Herds&
Herds::operator= (const container_type& v)
{
    this->clear();
    this->insert(v.begin(), v.end());
    return *this;
}
/****************************************************************************/
Herds::operator
std::vector<std::string>() const
{
    std::vector<std::string> v;
    std::transform(this->begin(), this->end(),
        std::back_inserter(v), std::mem_fun_ref(&Herd::name));
    return v;
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
