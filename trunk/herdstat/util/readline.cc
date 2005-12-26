/*
 * libherdstat -- herdstat/util/readline.cc
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
#include <herdstat/util/readline.hh>

static const std::string * _rl_buf = NULL;

static int
default_readline_startup_hook()
{
    rl_insert_text(_rl_buf->c_str());
    return 0;
}

namespace herdstat {
namespace util {
/****************************************************************************/
ReadLine::ReadLine(const std::string& name,
                   const std::string& prompt) throw()
    : _name(name), _prompt(prompt),
      _inithook(default_readline_startup_hook)
{
    _init();
}
/****************************************************************************/
ReadLine::ReadLine(rl_hook_func_t *startup_hook) throw()
    : _name(), _prompt(), _inithook(startup_hook)
{
    _init();
}
/****************************************************************************/
ReadLine::ReadLine(const std::string& name,
                   const std::string& prompt,
                   rl_hook_func_t *startup_hook)
    throw()
    : _name(name), _prompt(prompt), _inithook(startup_hook)
{
    _init();
}
/****************************************************************************/
ReadLine::~ReadLine() throw()
{
}
/****************************************************************************/
void
ReadLine::_init() throw()
{
    if (not _name.empty())
        rl_readline_name = _name.c_str();

    rl_startup_hook = _inithook;
}
/****************************************************************************/
std::string
ReadLine::operator()(const std::string& text) const throw (ReadLineEOF)
{
    _rl_buf = &text;

    char *input = readline(_prompt.c_str());
    if (not input)
        throw ReadLineEOF();

    std::string result;

    if (*input)
    {
        add_history(input);
        result.assign(input);
    }

    std::free(input);
    return result;
}
/****************************************************************************/
} // namespace util
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
