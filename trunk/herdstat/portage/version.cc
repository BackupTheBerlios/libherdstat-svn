/*
 * libherdstat -- herdstat/portage/version.cc
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

#include <locale>
#include <vector>
#include <iterator>
#include <memory>
#include <cstdlib>
#include <climits>
#include <cassert>

#include <herdstat/util/misc.hh>
#include <herdstat/util/string.hh>
#include <herdstat/util/algorithm.hh>
#include <herdstat/portage/misc.hh>
#include <herdstat/portage/functional.hh>
#include <herdstat/portage/exceptions.hh>
#include <herdstat/portage/version.hh>

namespace herdstat {
namespace portage {
/*** static members *********************************************************/
std::vector<std::string> VersionString::suffix::_suffixes;
/****************************************************************************/
VersionComponents::VersionComponents()
{
}
/****************************************************************************/
VersionComponents::VersionComponents(const std::string &path)
    : _verstr(util::chop_fileext(util::basename(path)))
{
    this->parse();
}
/****************************************************************************/
void
VersionComponents::assign(const std::string& path)
{
    _verstr.assign(util::chop_fileext(util::basename(path)));
    this->clear();
    this->parse();
}
/****************************************************************************/
void
VersionComponents::parse()
{
    /* append -r0 if necessary */
    std::string::size_type pos = this->_verstr.rfind("-r0");
    if (pos == std::string::npos)
    {
        pos = this->_verstr.rfind("-r");
        if ((pos == std::string::npos) or (((pos+2) <= this->_verstr.size()) and
            not std::isdigit(this->_verstr.at(pos+2))))
            this->_verstr.append("-r0");
    }

    std::vector<std::string> parts(util::split(this->_verstr, '-'));

    /* If parts > 3, ${PN} contains a '-' */
    if (parts.size() > 3)
    {
        std::string PN;
        while (parts.size() > 2)
        {
            PN += "-" + parts.front();
            parts.erase(parts.begin());
        }

        parts.insert(parts.begin(), PN);
    }

    /* this should NEVER != 3. */
    assert(parts.size() == 3);

    /* fill our map with the components */
    std::pair<iterator, bool> pn = this->insert(value_type("PN", parts[0]));
    std::pair<iterator, bool> pv = this->insert(value_type("PV", parts[1]));
    std::pair<iterator, bool> pr = this->insert(value_type("PR", parts[2]));
    assert(pn.second and pv.second and pr.second);
    this->insert(value_type("P", pn.first->second+"-"+pv.first->second));
    std::pair<iterator, bool> pvr = this->insert(value_type("PVR",
        pv.first->second+"-"+pr.first->second));
    this->insert(value_type("PF", pn.first->second+"-"+pvr.first->second));

    /* remove $PN from _verstr */
    _verstr.erase(0, (*this)["PN"].length()+1); /* +1 for the '-' after ${PN} */
}
/*****************************************************************************
 * suffix                                                                  *
 *****************************************************************************/
VersionString::suffix::suffix()
{
}

VersionString::suffix::suffix(const std::string& pvr)
{
    this->parse(pvr);
}

void
VersionString::suffix::parse(const std::string &pvr) const
{
    /* valid suffixes (in order) */
    if (this->_suffixes.empty())
    {
        this->_suffixes.push_back("alpha");
        this->_suffixes.push_back("beta");
        this->_suffixes.push_back("pre");
        this->_suffixes.push_back("rc");
        this->_suffixes.push_back("p");
    }

    this->_suffix.assign(pvr);

    /* chop revision */
    std::string::size_type pos = this->_suffix.rfind("-r");
    if (pos != std::string::npos)
        this->_suffix.erase(pos);

    /* get suffix */
    pos = this->_suffix.rfind('_');
    if (pos != std::string::npos)
    {
        this->_suffix.erase(0, pos+1);

        /* get suffix version */
        pos = this->_suffix.find_first_of("0123456789");
        if (pos != std::string::npos)
        {
            this->_suffix_ver = this->_suffix.substr(pos);
            this->_suffix.erase(pos);
        }

        /* is suffix valid? */
        if (std::find(_suffixes.begin(), _suffixes.end(),
                    _suffix) == _suffixes.end())
            this->_suffix.clear();
    }
    else
        this->_suffix.clear();
}
/*****************************************************************************
 * Is this suffix less than that suffix?                                     *
 *****************************************************************************/
bool
VersionString::suffix::operator< (const suffix& that) const
{
    std::vector<std::string>::iterator ti, si;

    ti = std::find(this->_suffixes.begin(), this->_suffixes.end(),
        this->str());
    si = std::find(this->_suffixes.begin(), this->_suffixes.end(),
        that.str());

    /* both have a suffix */
    if ((ti != this->_suffixes.end()) and (si != this->_suffixes.end()))
    {
        /* same suffix, so compare suffix version */
        if (ti == si)
        {
            if (not this->version().empty() and not that.version().empty())
                return ( util::destringify<unsigned long>(this->version()) <
                         util::destringify<unsigned long>(that.version()) );
            else if (this->version().empty() and that.version().empty())
                return true;
            else
                return ( that.version().empty() ? false : true );
        }

        return ti < si;
    }

    /* that has no suffix */
    else if (ti != this->_suffixes.end())
        /* only the 'p' suffix is > than no suffix */
        return (*ti == "p" ? false : true);
    
    /* this has no suffix */
    else if (si != this->_suffixes.end())
        /* only the 'p' suffix is > than no suffix */
        return (*si == "p" ? true : false);

    return false;
}
/*****************************************************************************
 * Is this suffix equal to that suffix?                                      *
 *****************************************************************************/
bool
VersionString::suffix::operator== (const suffix& that) const
{
    std::vector<std::string>::iterator ti, si;

    ti = std::find(this->_suffixes.begin(), this->_suffixes.end(),
        this->str());
    si = std::find(this->_suffixes.begin(), this->_suffixes.end(),
        that.str());

    /* both have a suffix */
    if ((ti != this->_suffixes.end()) and (si != this->_suffixes.end()))
    {
        /* same suffix, so compare suffix version */
        if (ti == si)
        {
            if (not this->version().empty() and not that.version().empty())
                return ( util::destringify<unsigned long>(this->version()) ==
                         util::destringify<unsigned long>(that.version()) );
            else if (this->version().empty() and that.version().empty())
                return true;
            else
                return ( that.version().empty() ? false : true );
        }

        return ti == si;
    }
    else if ((ti != this->_suffixes.end()) or (si != this->_suffixes.end()))
        return false;

    return true;
}
/*****************************************************************************
 * nosuffix                                                                *
 *****************************************************************************/
VersionString::nosuffix::nosuffix()
{
}

VersionString::nosuffix::nosuffix(const std::string& pv)
{
    this->parse(pv);
}

void
VersionString::nosuffix::parse(const std::string& pv) const
{
    this->_version.assign(pv);

    /* strip suffix */
    std::string::size_type pos = this->_version.find('_');
    if (pos != std::string::npos)
        this->_version.erase(pos);

    /* find first non-digit */
    pos = this->_version.find_first_not_of("0123456789.");
    if (pos != std::string::npos)
    {
        this->_extra = this->_version.substr(pos);
        this->_version.erase(pos);
    }
}
/*****************************************************************************
 * Is this version (minus suffix) less that that version (minus suffix)?     *
 *****************************************************************************/
bool
VersionString::nosuffix::operator< (const nosuffix& that) const
{
    bool differ = false;
    bool result = false;

    /* std::string comparison should be sufficient for == */
    if (*this == that)
        return false;
    else if (this->_version == that._version)
        return this->_extra < that._extra;

    std::vector<std::string> thisparts = util::split(this->_version, '.');
    std::vector<std::string> thatparts = util::split(that._version, '.');
    std::vector<std::string>::size_type stoppos =
        std::min<std::vector<std::string>::size_type>(thisparts.size(),
                                                       thatparts.size());

    /* TODO: if thisparts.size() and thatpart.size() == 1, convert to long
     * and compare */

    std::vector<std::string>::iterator thisiter, thatiter;
    for (thisiter = thisparts.begin(), thatiter = thatparts.begin() ;
         stoppos != 0 ; ++thisiter, ++thatiter, --stoppos)
    {
        /* loop until the version components differ */

        /* TODO: use std::mismatch() ?? */
        unsigned long thisver =
            util::destringify<unsigned long>(*thisiter);
        unsigned long thatver =
            util::destringify<unsigned long>(*thatiter);

        bool same = false;
        if (thisver == thatver)
        {
            /* 1 == 01 ? they're the same in comparison speak but 
             * absolutely not the same in version std::string speak */
            if (*thisiter == (std::string("0") + *thatiter))
                same = true;
            else
                continue;
        }
        
        result = ( same ? true : thisver < thatver );
        differ = true;
        break;
    }

    if (not differ)
        return thisparts.size() <= thatparts.size();

    return result;
}
/*****************************************************************************
 * Is this version (minus suffix) equal to that version (minus suffix)?      *
 *****************************************************************************/
bool
VersionString::nosuffix::operator== (const nosuffix& that) const
{
    /* std::string comparison should be sufficient for == */
    return ((this->_version == that._version) and
            (this->_extra   == that._extra));
}
/*****************************************************************************
 * VersionString                                                          *
 *****************************************************************************/
VersionString::VersionString(const std::string& path)
    : _ebuild(path), _v(path), _verstr(_v.version()),
      _suffix(_v["PVR"]), _version(_v["PV"])
{
}

VersionString::VersionString(const VersionString& that)
{
    *this = that;
}

VersionString&
VersionString::operator=(const VersionString& that)
{
    const_cast<std::string&>(_ebuild) = that._ebuild;
    const_cast<VersionComponents&>(_v) = that._v;
    const_cast<std::string&>(_verstr) = that._verstr;
    const_cast<suffix&>(_suffix) = that._suffix;
    const_cast<nosuffix&>(_version) = that._version;

    return *this;
}
/*****************************************************************************
 * Display full version std::string (as portage would).                           *
 *****************************************************************************/
std::string
VersionString::str() const
{
    /* chop -r0 if necessary */
    std::string::size_type pos = _verstr.rfind("-r0");
    if (pos != std::string::npos)
        return _verstr.substr(0, pos);

    return _verstr;
}
/*****************************************************************************
 * Is this version less than that version?                                   *
 *****************************************************************************/
bool
VersionString::operator< (const VersionString& that) const
{
    if (this->_version < that._version)
        return true;
    else if (this->_version == that._version)
    {
        if (this->_suffix < that._suffix)
            return true;
        else if (this->_suffix == that._suffix)
        {
            unsigned long thisrev =
                util::destringify<unsigned long>(this->_v["PR"].substr(1).c_str());
            unsigned long thatrev =
                util::destringify<unsigned long>(that._v["PR"].substr(1).c_str());
            return thisrev <= thatrev;
        }
    }

    return false;
}
/*****************************************************************************
 * Is this version equal to that version?                                    *
 *****************************************************************************/
bool
VersionString::operator== (const VersionString& that) const
{
    return ( (this->_version == that._version) and
             (this->_suffix == that._suffix) and
             (this->_v["PR"] == that._v["PR"]) );
}
/*****************************************************************************
 * versions                                                                *
 *****************************************************************************/
Versions::Versions()
{
}

Versions::Versions(const std::string& path)
{
    this->assign(path);
}

Versions::Versions(const std::vector<std::string>& paths)
{
    std::for_each(paths.begin(), paths.end(),
        std::bind2nd(util::Appender<Versions, std::string>(), this));
}

Versions::~Versions()
{
}
/*****************************************************************************
 * Given a path to a package directory, insert a new VersionString for    *
 * each ebuild found.  clear()'s container first.                            *
 *****************************************************************************/
void
Versions::assign(const std::string& path)
{
    this->clear();

    if (not util::is_dir(path))
        return;

    const util::Directory pkgdir(path);
    util::copy_if(pkgdir.begin(), pkgdir.end(),
        std::inserter(this->container(), this->end()), IsEbuild());
}
/*****************************************************************************
 * Same as assign() but does not call clear().                               *
 *****************************************************************************/
void
Versions::append(const std::string& path)
{
    const util::Directory pkgdir(path);
    util::copy_if(pkgdir.begin(), pkgdir.end(),
        std::inserter(this->container(), this->end()), IsEbuild());
}
/*****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
