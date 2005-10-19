/*
 * libherdstat -- herdstat/portage/keywords.cc
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

#include <herdstat/util/misc.hh>
#include <herdstat/util/string.hh>
#include <herdstat/portage/exceptions.hh>
#include <herdstat/portage/config.hh>
#include <herdstat/portage/keywords.hh>

namespace herdstat {
namespace portage {
/*** static members *********************************************************/
const std::string Keyword::_valid_masks("-~");
/****************************************************************************/
Keyword::maskc::maskc() : _c('\0')
{
}
/****************************************************************************/
Keyword::maskc::maskc(const char c) : _c('\0')
{
    if (_valid_masks.find(c) == std::string::npos)
        throw InvalidKeywordMask(c);

    _c = c;
}
/****************************************************************************/
bool
Keyword::maskc::operator< (const maskc& that) const
{
    if (_c == that._c)
        return false;

    /* '-' is less than everything */
    if (_c == '-')
        return true;

    if (not this->empty() and that.empty())
        return true;

    return false;
}
/****************************************************************************/
Keyword::Keyword(const std::string& kw)
    : _valid_archs(GlobalConfig().archs())
{
    this->parse(kw);

    if (not _valid_archs.count(_arch))
        throw InvalidArch(_arch);
}
/****************************************************************************/
void
Keyword::parse(const std::string& kw)
{
    if (_valid_masks.find(kw[0]) != std::string::npos)
        _mask = kw[0];

    _arch = (_mask.empty() ? kw : kw.substr(1));
}
/****************************************************************************/
Keywords::Keywords(bool use_colors)
    : _color(use_colors), _ebuild(), _str()
{
}
/****************************************************************************/
Keywords::Keywords(const std::string& path, bool use_colors)
    : _color(use_colors), _ebuild(path), _str()
{
    this->fill();
    this->format();
}
/****************************************************************************/
Keywords::Keywords(const ebuild& e, bool use_colors)
    : _color(use_colors), _ebuild(e), _str()
{
    this->fill();
    this->format();
}
/****************************************************************************/
Keywords::Keywords(const std::vector<std::string>& keywords, bool use_colors)
    : _color(), _ebuild(), _str()
{
    this->assign(keywords, use_colors);
}
/****************************************************************************/
void
Keywords::assign(const std::string& path, bool use_colors)
{
    _color = use_colors;
    _ebuild.read(path);
    this->fill();
    this->format();
}
/****************************************************************************/
void
Keywords::assign(const ebuild& e, bool use_colors)
{
    _color = use_colors;
    _ebuild = e;
    this->fill();
    this->format();
}
/****************************************************************************/
void
Keywords::assign(const std::vector<std::string>& v, bool use_colors)
{
    _color = use_colors;

    this->clear();
    
    std::vector<std::string>::const_iterator i;
    for (i = v.begin() ; i != v.end() ; ++i)
        this->insert(Keyword(*i));
}
/****************************************************************************/
void
Keywords::fill()
{
    if (_ebuild["KEYWORDS"].empty())
        throw Exception(_ebuild.path()+": no KEYWORDS variable defined");

    const std::vector<std::string> v(util::split(_ebuild["KEYWORDS"]));
    this->assign(v, _color);
}
/****************************************************************************/
void
Keywords::format()
{
    size_type n = 0;
    util::ColorMap cmap;

    for (iterator i = this->begin() ; i != this->end() ; ++i, ++n)
    {
        if (_color)
        {
            switch (i->mask())
            {
                case '-':
                    _str += cmap[red];
                    break;
                case '~':
                    _str += cmap[yellow];
                    break;
                default:
                    _str += cmap[blue];
            }

            _str += i->str() + cmap[none];
        }
        else
            _str += i->str();

        if ((n+1) != this->size())
            _str += " ";
    }
}
/****************************************************************************/
struct IsMaskChar : std::binary_function<Keyword, char, bool>
{
    bool operator()(const Keyword& kw, char maskc) const
    { return (kw.mask() == maskc); }
};

bool
Keywords::all_masked() const
{
    difference_type size(this->size());
    return (std::count_if(this->begin(), this->end(),
                std::bind2nd(IsMaskChar(), '-')) == size);
}

bool
Keywords::all_unstable() const
{
    difference_type size(this->size());
    return (std::count_if(this->begin(), this->end(),
                std::bind2nd(IsMaskChar(), '~')) == size);
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 et : */
