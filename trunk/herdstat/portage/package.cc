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
    : _name(), _cat(), _dir(), _path(), _kwmap(NULL)
{
}
/****************************************************************************/
Package::Package(const Package& that)
    : _name(), _cat(), _dir(), _path(), _kwmap(NULL)
{
    *this = that;
}
/****************************************************************************/
Package::Package(const std::string& name, const std::string& portdir)
    : _name(), _cat(), _dir(portdir), _path(), _kwmap(NULL)
{
    set_name(name);
}
/****************************************************************************/
Package::~Package()
{
    if (_kwmap) delete _kwmap;
}
/****************************************************************************/
Package&
Package::operator=(const Package& that)
{
    _name.assign(that._name);
    _cat.assign(that._cat);
    _dir.assign(that._dir);
    _full.assign(that._full);
    _path.assign(that._path);

    if (that._kwmap)
        _kwmap = new KeywordsMap(*that._kwmap);

    return *this;
}
/****************************************************************************/
void
Package::set_name(const std::string& name)
{
    BacktraceContext c("herdstat::portage::Package::set_name("+name+")");

    if (name.find('/') != std::string::npos)
        set_full(name);
    else
        _name.assign(name);
}
/****************************************************************************/
void
Package::set_full(const std::string& full)
{
    BacktraceContext c("herdstat::portage::Package::set_full("+full+")");

    std::string::size_type pos = full.find('/');
    if (pos == std::string::npos)
        throw Exception("Invalid full category/package specification '"+full+"'.");

    set_category(full.substr(0, pos));
    set_name(full.substr(++pos));
    _full.assign(full);
    set_path(_dir+"/"+_full);
}
/****************************************************************************/
PackageList::PackageList(bool fill)
    : _portdir(GlobalConfig().portdir()),
      _overlays(GlobalConfig().overlays()),
      _filled(false)
{
    if (fill)
        this->fill();
}
/****************************************************************************/
PackageList::PackageList(const std::string& portdir,
                         const std::vector<std::string>& overlays,
                         bool fill)
    : _portdir(portdir), _overlays(overlays), _filled(false)
{
    if (fill)
        this->fill();
}
/****************************************************************************/
PackageList::~PackageList()
{
}
/****************************************************************************/
void
PackageList::fill()
{
    BacktraceContext c("herdstat::portage::PackageList::fill()");

    if (_filled)
        return;

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

    _filled = true;
}
/****************************************************************************/
PackageFinder::PackageFinder(const PackageList& pkglist)
    : _pkglist(pkglist), _results()
{
}
/****************************************************************************/
PackageFinder::~PackageFinder()
{
}
/****************************************************************************/
PackageWhich::PackageWhich()
{
}
/****************************************************************************/
PackageWhich::~PackageWhich()
{
}
/****************************************************************************/
const std::vector<std::string>&
PackageWhich::operator()(const std::vector<Package>& finder_results)
    throw (NonExistentPkg)
{
    BacktraceContext c("herdstat::portage::PackageWhich::operator()(std::vector<Package>)");

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

            const VersionString& v1(p1.keywords().back().first);
            const VersionString& v2(p2.keywords().back().first);

            /* if the pkg that already exists is older than the current one, or
             * they're equal and the one not already in 'pkgs' is in an overlay,
             * replace it */
            if (((v2 < v1) or (v2 == v1)) and p1.in_overlay())
                p2 = p1;
        }
    }

    std::transform(pkgs.begin(), pkgs.end(),
        std::back_inserter(_results), GetWhichFromPackage());

    return _results;
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
