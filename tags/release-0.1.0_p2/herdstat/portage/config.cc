/*
 * libherdstat -- herdstat/portage/config.cc
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

#include <herdstat/util/string.hh>
#include <herdstat/portage/config.hh>

namespace herdstat {
namespace portage {
/****************************************************************************/
config::config()
    : _vars(), _portdir(), _overlays(), _cats(), _archs()
{
    /* read default config */
    _vars.read("/etc/make.globals");
    _vars.close();
    /* read make.conf overriding any defined settings */
    _vars.read("/etc/make.conf");
    _vars.close();

    util::vars::iterator x;
    char *result = NULL;

    /* PORTDIR */
    if ((result = std::getenv("PORTDIR")))
        _portdir.assign(result);
    else if ((x = _vars.find("PORTDIR")) != _vars.end())
        _portdir.assign(x->second);
    
    /* default to /usr/portage */
    if (_portdir.empty())
        _portdir.assign("/usr/portage");

    /* PORTDIR_OVERLAY */
    if ((result = std::getenv("PORTDIR_OVERLAY")))
    {
        if (std::strlen(result) > 0)
            _overlays = util::split(result);
    }
    else if ((x = _vars.find("PORTDIR_OVERLAY")) != _vars.end())
    {
        if (not x->second.empty())
            _overlays = util::split(x->second);
    }

    /* initialize categories and archs now that we know PORTDIR */
    _cats.init(_portdir);
    _archs.init(_portdir);
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 et : */
