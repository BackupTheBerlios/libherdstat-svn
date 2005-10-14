/*
 * libherdstat -- herdstat/util/vars.cc
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

#include <ostream>
#include <utility>
#include <cassert>

#include <herdstat/exceptions.hh>
#include <herdstat/util/misc.hh>
#include <herdstat/util/vars.hh>

namespace herdstat {
namespace util {
/****************************************************************************/
vars::vars() : _depth(0)
{
}
/****************************************************************************/
vars::vars(const std::string& path)
    : BaseFile(path), _depth(0)
{
    this->read();
}
/****************************************************************************/
vars::~vars()
{
}
/****************************************************************************/
void
vars::dump(std::ostream& stream) const
{
    for (const_iterator i = this->begin() ; i != this->end() ; ++i)
        stream << i->first << "=" << i->second << std::endl;
}
/****************************************************************************/
void
vars::set_defaults()
{
    char *result = std::getenv("HOME");
    if (result)
        this->insert(std::make_pair("HOME", result));
    else
    {
        std::string home("/home/");
        home += current_user();
        if (is_dir(home))
            this->insert(std::make_pair("HOME", home));
    }

    /* for derivatives to define their own defaults */
    this->do_set_defaults();
}

void
vars::strip_ws(std::string& str)
{
    std::string::size_type pos;
    if ((pos = str.find_first_not_of(" \t")) != std::string::npos)
        str.erase(0, pos);
    if ((pos = str.find_last_not_of(" \t")) != std::string::npos)
        str.erase(++pos);
}

void
vars::perform_action_on(const std::string& str)
{
    if (str.empty())
        return;

    /* it's a variable assignment, so insert the key/value */
    if (str.find('=') != std::string::npos)
    {
        std::string line(str);
        std::string::size_type pos = line.find_first_not_of(" \t");
        if (pos != std::string::npos)
            line.erase(0, pos);

        if (line.length() > 0 and line[0] != '#')
        {
            pos = line.find('=');
            std::string key(line.substr(0, pos));
            std::string val(line.substr(++pos));

            /* handle leading/trailing whitespace */
            strip_ws(key);
            strip_ws(val);
 
            /* handle quotes */
            if ((pos = val.find_first_of("'\"")) != std::string::npos)
            {
                val.erase(pos, pos + 1);
                if ((pos = val.find_last_of("'\"")) != std::string::npos)
                    val.erase(pos, pos + 1);
            }
 
            this->erase(key);
            this->insert(std::make_pair(key, val));
        }
    }

    this->do_perform_action_on(str);
}
/****************************************************************************
 * Read from our stream, saving any VARIABLE=["']value['"]
 * statements in our map.  Lines beginning with a '#'
 * are considered to be comments.  Should work with shell
 * scripts or VARIABLE=value-type configuration files.
 ****************************************************************************/
void
vars::do_read()
{
    this->set_defaults();

    std::string line;
    while (std::getline(this->stream(), line))
        this->perform_action_on(line);

    /* loop through our map performing variable substitutions */
    iterator i, e;
    for (i = this->begin(), e = this->end() ; i != e ; ++i)
        this->subst(i->second);
}
/****************************************************************************
 * Search the given variable value for any variable occurrences,
 * recursively calling ourselves each time we find another occurrence.
 ****************************************************************************/
void
vars::subst(std::string& value)
{
    std::vector<std::string> vars;
    std::vector<std::string>::iterator v;
    std::string::size_type lpos = 0;

    /* find variables that need substituting */
    while (true)
    {
        std::string::size_type begin = value.find("${", lpos);
        if (begin == std::string::npos)
            break;

        std::string::size_type end = value.find("}", begin);
        if (end == std::string::npos)
            break;

        /* save it */
        if (this->_depth < 20)
            vars.push_back(value.substr(begin + 2, end - (begin + 2)));
        
        lpos = ++end;
    }

    /* for each variable we found */
    for (v = vars.begin() ; v != vars.end() ; ++v)
    {
        std::string subst;
        std::string var("${"+(*v)+"}");

        std::string::size_type pos = value.find(var);
        if (pos == std::string::npos)
            continue;

        /* is that variable defined? */
        iterator x = this->find(*v);
        if (x != this->end())
            subst = x->second;

        /* don't bother trying to perform substitution if they're equal */
        if (subst == value)
            continue;

        if (subst.find("${") != std::string::npos)
        {
            ++(this->_depth);
            this->subst(subst);
            --(this->_depth);
        }

        if (not subst.empty())
            value.replace(pos, var.length(), subst, 0, subst.length());
    }
}
/****************************************************************************/
} // namespace util
} // namespace herdstat

/* vim: set tw=80 sw=4 et : */
