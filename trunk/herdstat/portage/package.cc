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
    if (name.find('/') != std::string::npos)
        set_full(name);
    else
        _name.assign(name);
}
/****************************************************************************/
void
Package::set_full(const std::string& full)
{
    std::string::size_type pos = full.find('/');
    if (pos != std::string::npos)
    {
        set_category(full.substr(0, pos));
        set_name(full.substr(++pos));
        _full.assign(full);
    }
}
/****************************************************************************/
bool
Package::operator< (const Package& that) const
{
    if (_full == that._full)
    {
        /* if package names are equal, this is only less than that if this
         * portdir is the real portdir and that portdir isn't */
        const std::string& portdir(GlobalConfig().portdir());
        return (not ((_dir == portdir and that._dir == portdir) or
                     (that._dir == portdir)));
    }

    return (_full < that._full);
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
PackageFinder::PackageFinder(const PackageList& pkglist)
    : _pkglist(pkglist), _results()
{
}
/****************************************************************************/
const std::vector<std::string>&
PackageWhich::operator()(const std::vector<Package>& finder_results)
    throw (NonExistentPkg)
{
    const std::string& portdir(GlobalConfig().portdir());

    /* Loop through the results only keeping the newest of packages */
    std::vector<Package> pkgs;
    std::vector<Package>::const_iterator i;
    for (i = finder_results.begin() ; i != finder_results.end() ; ++i)
    {
        std::vector<Package>::iterator p =
            std::find_if(pkgs.begin(), pkgs.end(),
            std::bind2nd(FullPkgNameEqual(), *i));

        /* package doesn't exist, so add it */
        if (p == pkgs.end())
            pkgs.push_back(*i);
        /* package of the same name exists */
        else
        {
            const Package& p1(*i);
            Package& p2(*p);

            const versions& v1(p1.versions());
            const versions& v2(p2.versions());

            /* if the package that already exists is older than the current one,
             * replace it */
            if (v2.back() < v1.back())
                p2 = p1;
            else if (v2.back() == v1.back())
            {
                /* if they're equal and the one not already in pkgs is in an
                 * overlay, replace it */
                if (p1.portdir() != portdir)
                    p2 = p1;
            }
        }
    }

    std::transform(pkgs.begin(), pkgs.end(),
        std::back_inserter(_results), GetWhichFromPkg());

    return _results;
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
