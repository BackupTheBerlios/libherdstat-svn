/*
 * libherdstat -- herdstat/portage/package.cc
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

#include <herdstat/portage/misc.hh>
#include <herdstat/portage/config.hh>
#include <herdstat/portage/package.hh>

namespace herdstat {
namespace portage {
/****************************************************************************/
Package::Package()
    : _name(), _cat(), _dir(), _versions(NULL)
{
}
/****************************************************************************/
Package::Package(const Package& that)
    : _name(), _cat(), _dir(), _versions(NULL)
{
    *this = that;
}
/****************************************************************************/
Package::Package(const std::string& name, const std::string& portdir)
    : _name(), _cat(), _dir(portdir), _versions(NULL)
{
    set_name(name);
}
/****************************************************************************/
Package::~Package()
{
    if (_versions) delete _versions;
}
/****************************************************************************/
Package&
Package::operator=(const Package& that)
{
    _name.assign(that._name);
    _cat.assign(that._cat);
    _dir.assign(that._dir);
    _full.assign(that._full);

    if (that._versions)
        _versions = new portage::versions(*that._versions);

    return *this;
}
/****************************************************************************/
void
Package::set_name(const std::string& name)
{
    std::string::size_type pos = name.find('/');
    if (pos != std::string::npos)
    {
        set_category(name.substr(0, pos));
        _name.assign(name.substr(++pos));
        _full.assign(_cat+"/"+_name);
    }
    else
        _name.assign(name);
}
/****************************************************************************/
PackageList::PackageList()
    : _portdir(GlobalConfig().portdir()),
      _overlays(GlobalConfig().overlays())
{
}
/****************************************************************************/
PackageList::PackageList(const std::string& portdir,
                         const std::vector<std::string>& overlays)
    : _portdir(portdir), _overlays(overlays)
{
}
/****************************************************************************/
struct NewPackage
    : std::binary_function<std::string, std::string, Package>
{
    Package
    operator()(const std::string& path, const std::string& portdir) const
    {
        return Package(get_pkg_from_path(path), portdir);
    }
};
/****************************************************************************/
void
PackageList::fill()
{
    std::string path;
    const Categories& categories(GlobalConfig().categories());
    Categories::const_iterator ci, cend;

    /* we can only use the estimate here */
    this->reserve(PKGLIST_RESERVE);

    /* search portdir */
    for (ci = categories.begin(), cend = categories.end() ; ci != cend ; ++ci)
    {
        path.assign(_portdir+"/"+(*ci));
        if (not util::is_dir(path))
            continue;

        /* for each pkg in category, insert "cat/pkg" into container */
        const util::Directory cat(path);
        std::transform(cat.begin(), cat.end(),
            std::back_inserter(this->container()),
            std::bind2nd(NewPackage(), _portdir));
    }

    /* search overlays, if any */
    if (not _overlays.empty())
    {
        std::vector<std::string>::const_iterator oi, oend = _overlays.end();
        for (ci = categories.begin() ; ci != cend ; ++ci)
        {
            for (oi = _overlays.begin() ; oi != oend ; ++oi)
            {
                path.assign(*oi+"/"+(*ci));
                if (not util::is_dir(path))
                    continue;

                /* for each pkg in category, insert "cat/pkg" */
                const util::Directory cat(path);
                std::transform(cat.begin(), cat.end(),
                    std::back_inserter(this->container()),
                    std::bind2nd(NewPackage(), *oi));
            }
        }
    }

    std::sort(this->begin(), this->end());

    /* container may contain duplicates if overlays were searched */
    if (not _overlays.empty())
        this->erase(std::unique(this->begin(), this->end()), this->end());
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
