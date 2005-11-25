/*
 * libherdstat -- herdstat/util/string.cc
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

#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include <cstdarg>
#include <cstring>
#include <cctype>
#include <locale>
#include <functional>

#include <herdstat/exceptions.hh>
#include <herdstat/util/string.hh>

namespace herdstat {
namespace util {
/*****************************************************************************/
std::string
basename(const std::string& path) throw()
{
    std::string result(path);
    std::string::size_type pos;

    /* chop all trailing /'s */
    while (result[result.length() - 1] == '/' and result.length() > 1)
	result.erase(result.length() - 1);

    if ((pos = result.rfind('/')) != std::string::npos)
	result = result.substr(pos + 1);

    return ( result.empty() ? std::string("/") : result );
}
/*****************************************************************************/
std::string
dirname(const std::string& path) throw()
{
    std::string result(path);
    std::string::size_type pos;

    /* chop all trailing /'s */
    while (result[result.length() - 1] == '/' and result.length() > 1)
	result.erase(result.length() - 1);

    if ((pos = result.rfind('/')) != std::string::npos)
        result.erase(pos);
    else
        result.assign(".");

    return ( result.empty() ? std::string("/") : result );
}
/*****************************************************************************/
const char *
chop_fileext(const std::string& path, unsigned short depth) throw()
{
    BacktraceContext c("herdstat::util::chop_fileext("+path+")");

    std::string result(path);

    for (; depth > 0 ; --depth)
    {
        std::string::size_type pos = result.rfind('.');
        if (pos != std::string::npos)
            result = result.substr(0, pos);
    }

    return result.c_str();
}
/*****************************************************************************
 * Clean up the whitespace of the given string.                              *
 *****************************************************************************/
struct BothSpaces
{
    bool operator()(char c1, char c2) const
    { return (std::isspace(c1) and std::isspace(c2)); }
};

std::string
tidy_whitespace(const std::string &s) throw()
{
    if (s.empty())
	return s;

    std::string result;
    std::string::size_type pos;

    /* collapse whitespace */
    std::unique_copy(s.begin(), s.end(),
        std::back_inserter(result), BothSpaces());

    /* replace all newlines with a space */
    std::replace(result.begin(), result.end(), '\n', ' ');

    /* remove any leading whitespace */
    if ((pos = result.find_first_not_of(" \t")) != std::string::npos)
	result.erase(0, pos);

    /* remove any trailing whitespace */
    if ((pos = result.find_last_not_of(" \t")) != std::string::npos)
	result.erase(++pos);

    if (result == " ")
        return std::string();
	
    return result;
}
/*****************************************************************************/
std::string
sprintf(const char *fmt, ...) throw()
{
    va_list v;
    va_start(v, fmt);
    std::string s(util::sprintf(fmt, v));
    va_end(v);
    return s;
}
/*****************************************************************************/
std::string
sprintf(const char *fmt, va_list v) throw()
{
    char *buf;
    vasprintf(&buf, fmt, v);
    std::string s(buf);
    std::free(buf);
    return s;
}
/*****************************************************************************/
std::string
sprintf(const std::string& fmt, ...) throw()
{
    va_list v;
#ifdef HAVE_GCC4
    va_start(v, fmt);
#else
    va_start(v, fmt.c_str());
#endif

    std::string s(util::sprintf(fmt, v));
    va_end(v);
    return s;
}
/*****************************************************************************/
std::string
sprintf(const std::string& fmt, va_list v) throw()
{
    return util::sprintf(fmt.c_str(), v);
}
/*****************************************************************************
 * HTMLify the given std::string (replace any occurrences of &,>,<)               *
 *****************************************************************************/
std::string
htmlify(const std::string &str) throw()
{
    std::string result(str);
    std::map<std::string, std::string> sr;
    std::map<std::string, std::string>::iterator i, e;
    sr["&"] = "&amp;";
    sr[">"] = "&gt;";
    sr["<"] = "&lt;";

    i = sr.begin(), e = sr.end();
    for (; i != e ; ++i)
    {
	std::string::size_type pos, lpos = 0;
	while (true)
	{
	    pos = result.find(i->first, lpos);
	    if (pos == std::string::npos)
		break;

	    if (result.substr(pos, pos + i->second.length()) == i->second)
		result.replace(pos, i->first.length(), i->second, 0,
		    i->second.length());

	    lpos = ++pos;
	}
    }

    return result;
}
/*****************************************************************************
 * unHTMLify the given std::string (replace occurrences of &amp;,&gt;,&;lt;       *
 *****************************************************************************/
std::string
unhtmlify(const std::string &str) throw()
{
    std::string result(str);
    std::map<std::string, std::string> sr;
    std::map<std::string, std::string>::iterator i, e;
    sr["&amp;"] = "&";
    sr["&gt;"] = ">";
    sr["&lt;"] = "<";

    i = sr.begin(), e = sr.end();
    for (; i != e ; ++i)
    {
	std::string::size_type pos, lpos = 0;
	while (true)
	{
	    pos = result.find(i->first, lpos);
	    if (pos == std::string::npos)
		break;

	    result.replace(pos, i->first.length(), i->second,
		0, i->second.length());

	    lpos = ++pos;
	}
    }

    return result;
}
/*****************************************************************************
 * Convert a vector of std::string to one std::string.                                 *
 *****************************************************************************/
std::string
join(const std::vector<std::string> &v,
           const std::string::value_type delim) throw()
{
    std::string result;

    std::vector<std::string>::const_iterator i, end;
    for (i = v.begin(), end = v.end(); i != end ; ++i)
    {
        result += *i;
        if ((i+1) != end)
            result += delim;
    }

    return result;
}
/*****************************************************************************/
std::vector<std::string>
split(const std::string& str, const char delim, bool append_empty) throw()
{
    std::vector<std::string> v;
    std::string::size_type pos, lpos = 0;
    
    while (true)
    {
	if ((pos = str.find(delim, lpos)) == std::string::npos)
	{
	    v.push_back(str.substr(lpos));
	    break;
	}

	/* don't append empty strings (two
	 * delimiters in a row were encountered) */
        const std::string sub(str.substr(lpos, pos - lpos));
	if (not sub.empty() or append_empty)
	    v.push_back(sub);

	lpos = ++pos;
    }
    return v;
}
/*****************************************************************************/
std::string
strip_colors(const std::string& str) throw()
{
    std::string result(str);
    std::string::size_type pos, lpos = 0;

    while ((pos = result.find("\033", lpos)) != std::string::npos)
    {
	std::string::size_type mpos = result.find('m', pos);
	if (mpos == std::string::npos)
	    result.erase(pos);

	result.erase(pos, (mpos-pos)+1);
	lpos = ++pos;
    }

    return result;
}
/*****************************************************************************/
} // namespace util
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
