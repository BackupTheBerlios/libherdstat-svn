/*
 * libherdstat -- herdstat/util/string.hh
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

#ifndef HAVE_STRING_HH
#define HAVE_STRING_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/util/string.hh
 * @brief Defines string-related classes/functions.
 */

#include <string>
#include <vector>
#include <sstream>
#include <cstdarg>
#include <cerrno>
#include <cctype>
#include <herdstat/exceptions.hh>

namespace herdstat {
/// General-purpose utility classes/functions.
namespace util {

    /** Tidy whitespace of the given string.
     * @param s String object
     * @returns Resulting std::string object.
     */
    std::string tidy_whitespace(const std::string &s);

    //@{
    /// sprintf() wrappers
    std::string sprintf(const char *, ...);
    std::string sprintf(const char *, va_list);
    std::string sprintf(const std::string&, ...);
    std::string sprintf(const std::string&, va_list);
    //@}

    /** Split string into a vector of strings.
     * @param s String to split.
     * @param d Delimiter.
     * @param append_empty Append "" if two contiguous delimiters are
     * encountered?
     * @returns Vector of sub-strings.
     */
    std::vector<std::string> split(const std::string& s,
                                   const char d = ' ',
                                   bool append_empty = false);

    /** Convert vector of std::strings to one std::string.
     * @param v Vector of std::strings
     * @param d Delimiter.
     * @returns Resulting string object.
     */
    std::string join(const std::vector<std::string>& v, const char d = ' ');

    /** Replace any unfriendly characters in the given std::string to their
     * HTML counterparts.
     * @param s String object.
     * @returns Resulting string object.
     */
    std::string htmlify(const std::string& s);

    /** Replace any HTML'ized characters in the given std::string to their
     * respective counterparts.
     * @param s String object.
     * @returns Resulting string object.
     */
    std::string unhtmlify(const std::string& s);

    /** Return a copy of the given string with the ASCII color sequences
     * removed.
     * @param s string object.
     * @returns Resulting string object.
     */
    std::string strip_colors(const std::string& s);

    /************************************************************************/
    /** Convert string to all lowercase.
     * @param s String object.
     * @returns Resulting string object.
     */
    inline std::string
    lowercase(const std::string& s)
    {
        std::string result;
        std::transform(s.begin(), s.end(),
            std::back_inserter(result), ::tolower);
        return result;
    }

    inline void
    lowercase_inplace(std::string& s)
    {
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    }
    /************************************************************************/
    /** Convert a type to a std::string.
     * @param v Value of type T.
     * @returns A std::string object.
     */
    template <typename T>
    std::string
    stringify(const T& v)
    {
        std::ostringstream os;
        os << v;
        return os.str();
    }

    template <>
    inline std::string
    stringify<bool>(const bool& v)
    {
        std::ostringstream os;
        os << std::boolalpha << v;
        return os.str();
    }

    template <>
    inline std::string
    stringify<std::vector<std::string> >(const std::vector<std::string>& v)
    {
        return join(v);
    }

    template <>
    inline std::string
    stringify<std::string>(const std::string& v)
    {
        return v;
    }
    /************************************************************************/
    /** Convert a std::string to a type.
     * @param s A std::string object.
     * @returns Value of type T.
     */
    template <typename T>
    T
    destringify(const std::string& s)
    {
        std::istringstream is(s.c_str());

        T v;
        is >> v;

        if (not is.eof())
            throw BadCast("Failed to cast '"+s+"'.");

        return v;
    }

    template <>
    inline std::vector<std::string>
    destringify<std::vector<std::string> >(const std::string& s)
    {
        return split(s);
    }
    /************************************************************************/
    template <>
    inline int
    destringify<int>(const std::string& s)
    {
        char *invalid;
        int result = std::strtol(s.c_str(), &invalid, 10);
        if (*invalid)
            throw BadCast("Failed to cast '"+s+"' to int.");
        return result;
    }
    /************************************************************************/
    template <>
    inline long
    destringify<long>(const std::string& s)
    {
        char *invalid;
        long result = std::strtol(s.c_str(), &invalid, 10);
        if (*invalid)
            throw BadCast("Failed to cast '"+s+"' to long.");
        return result;
    }
    /************************************************************************/
    template <>
    inline unsigned long
    destringify<unsigned long>(const std::string& s)
    {
        char *invalid;
        unsigned long result = std::strtoul(s.c_str(), &invalid, 10);
        if (*invalid or ((result == ULONG_MAX) and (errno == ERANGE)))
            throw BadCast("Failed to cast '"+s+"' to unsigned long.");
        return result;
    }
    /************************************************************************/
    template <>
    inline double
    destringify<double>(const std::string& s)
    {
        char *invalid;
        double result = std::strtod(s.c_str(), &invalid);
        if (*invalid)
            throw BadCast("Failed to cast '"+s+"' to double.");
        return result;
    }
    /************************************************************************/
    template <>
    inline float
    destringify<float>(const std::string& s)
    {
        char *invalid;
        float result = std::strtod(s.c_str(), &invalid);
        if (*invalid)
            throw BadCast("Failed to cast '"+s+"' to float.");
        return result;
    }
    /************************************************************************/
    template <>
    inline bool
    destringify<bool>(const std::string& s)
    {
        if (s == "true" or s == "yes" or s == "on")  return true;
        if (s == "false" or s == "no" or s == "off") return false;
        return destringify<int>(s);
    }
    /************************************************************************/

} // namespace util
} // namespace herdstat

#endif /* HAVE_STRING_HH */

/* vim: set tw=80 sw=4 et : */
