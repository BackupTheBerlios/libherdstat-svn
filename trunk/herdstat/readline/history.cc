/*
 * libherdstat -- herdstat/readline/history.cc
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

#include <cstdlib>
#include <herdstat/util/file.hh>
#include <herdstat/readline/history.hh>

namespace herdstat {
namespace readline {
/****************************************************************************/
History::History() throw()
    : _path()
{
    _init();
}
/****************************************************************************/
History::History(const std::string& path) throw()
    : _path(path)
{
    _init();
}
/****************************************************************************/
History::~History() throw()
{
}
/****************************************************************************/
void
History::_init() throw()
{
    using_history();

    if (_path.empty())
    {
        const char * const homedir = std::getenv("HOME");
        if (homedir)
            _path.assign(std::string(homedir) + "/.history");
        else
            _path.assign(".history");
    }
}
/****************************************************************************/
void
History::read() throw (FileException)
{
    if (util::is_file(_path) and (read_history(_path.c_str()) != 0))
        throw FileException(_path);
}
/****************************************************************************/
void
History::read(int from, int to) throw (FileException)
{
    if (util::is_file(_path) and
        (read_history_range(_path.c_str(), from, to) != 0))
        throw FileException(_path);
}
/****************************************************************************/
void
History::write() throw (FileException)
{
    if (write_history(_path.c_str()) != 0)
        throw FileException(_path);
}
/****************************************************************************/
} // namespace readline
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
