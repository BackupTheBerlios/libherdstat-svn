/*
 * libherdstat -- herdstat/portage/categories.cc
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

#include <fstream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <herdstat/portage/exceptions.hh>
#include <herdstat/portage/config.hh>
#include <herdstat/portage/categories.hh>

#define CATEGORIES      "/profiles/categories"
#define CATEGORIES_USER "/etc/portage/categories"

namespace herdstat {
namespace portage {
/****************************************************************************/
Categories::Categories(bool validate)
    : PortageFileBase(config::portdir()+CATEGORIES),
      _portdir(config::portdir()), _validate(validate)
{
    this->read();
}
/****************************************************************************/
Categories::Categories(const std::string& portdir, bool validate)
    : PortageFileBase(portdir+CATEGORIES), _portdir(portdir),
      _validate(validate)
{
    this->read();
}
/****************************************************************************/
// for QA - bails if given category does not exist
struct BailIfInvalid : std::binary_function<std::string, std::string, void>
{
    void operator()(const std::string& cat, const std::string& portdir) const
    {
        if (not util::is_dir(portdir+"/"+cat))
            throw QAException("invalid category '"+cat+"'.");
    }
};

void
Categories::validate() const
{
    std::for_each(this->begin(), this->end(),
        std::bind2nd(BailIfInvalid(), _portdir));
}

void
Categories::read()
{
    PortageFileBase::read();

    /* virtual isn't really a category */
    this->erase("virtual");

    /* validate if requested */
    if (_validate)
        this->validate();

    /* read user categories file */
    if (util::is_file(CATEGORIES_USER))
    {
        this->set_path(CATEGORIES_USER);
        PortageFileBase::read();
    }
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 et : */
