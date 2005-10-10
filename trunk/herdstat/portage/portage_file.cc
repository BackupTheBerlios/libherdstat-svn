/*
 * libherdstat -- herdstat/portage/portage_file.cc
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

#include <herdstat/exceptions.hh>
#include <herdstat/portage/portage_file.hh>

namespace herdstat {
namespace portage {
/****************************************************************************/
PortageFileBase::PortageFileBase(const std::string& path)
    : _path(path)
{
}
/****************************************************************************/
void
PortageFileBase::read()
{
    if (_path.empty())
        throw Exception("PortageFileBase::read() called with empty path.\nUse set_path() member.");

    std::ifstream stream(_path.c_str());
    if (not stream)
        throw FileException(_path);

    this->insert(std::istream_iterator<std::string>(stream),
                 std::istream_iterator<std::string>());
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 et : */
