/*
 * libherdstat -- portage/ebuild.cc
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

#include <cassert>
#include <herdstat/portage/misc.hh>
#include <herdstat/portage/version.hh>
#include <herdstat/portage/ebuild.hh>

namespace herdstat {
namespace portage {
/****************************************************************************/
ebuild::ebuild()
{
}
/****************************************************************************/
ebuild::ebuild(const std::string &path) : util::vars(path)
{
    assert(is_ebuild(path));
}
/****************************************************************************/
ebuild::~ebuild()
{
}
/****************************************************************************/
void
ebuild::do_set_defaults()
{
    /* insert its variable components
     * (${P}, ${PN}, ${PV}, etc) into our map */
    version_map vmap(this->path());
    this->insert(vmap.begin(), vmap.end());
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 et : */
