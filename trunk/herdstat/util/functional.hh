/*
 * libherdstat -- herdstat/util/functional.hh
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

#ifndef _HAVE_UTIL_FUNCTIONAL_HH
#define _HAVE_UTIL_FUNCTIONAL_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/util/functional.hh
 * @brief General purpose utility functors.
 */

#include <functional>
#include <fnmatch.h>
#include <herdstat/util/file.hh>
#include <herdstat/util/regex.hh>

namespace herdstat {
namespace util {

    /**
     * @struct Dereference
     * @brief Function object that returns a dereferenced pointer to type T.
     */
    struct Dereference
    {
        template <typename T>
        const T& operator()(const T *p) const { return *p; }
    };

    /**
     * @struct DereferenceLess
     * @brief Function object that dereferences the given pointers and then
     * compares their values via operator<.
     */
    template <typename T>
    struct DereferenceLess
        : std::binary_function<const T*, const T*, bool>
    {
        bool operator() (const T *p1, const T *p2) const { return (*p1 < *p2); }
    };

    /**
     * @struct DereferenceGreater
     * @brief Function object that dereferences the given pointers and then
     * compares their values via operator<.
     */
    template <typename T>
    struct DereferenceGreater
        : std::binary_function<const T*, const T*, bool>
    {
        bool operator() (const T *p1, const T *p2) const { return (*p2 < *p1); }
    };

    /**
     * @struct DereferenceEqual
     * @brief Function object that dereferences the given pointers and then
     * compares their values via operator==.
     */
    template <typename T>
    struct DereferenceEqual
        : std::binary_function<const T*, const T*, bool>
    {
        bool operator() (const T *p1, const T *p2) const { return (*p1 == *p2); }
    };

    /**
     * @struct DereferenceStrLess
     * @brief Function object that dereferences the given pointer and calls
     * operator< against the given string.  Assumes the pointer type defines
     * operator<(std::string).
     */
    template <typename T>
    struct DereferenceStrLess
        : std::binary_function<const T*, std::string, bool>
    {
        bool operator()(const T *p, std::string s) const { return (*p < s); }
    };

    /**
     * @struct DereferenceStrGreater
     * @brief Function object that dereferences the given pointer and calls
     * operator> against the given string.  Assumes the pointer type defines
     * operator>(std::string).
     */
    template <typename T>
    struct DereferenceStrGreater
        : std::binary_function<const T*, std::string, bool>
    {
        bool operator()(const T *p, std::string s) const { return (*p > s); }
    };

    /**
     * @struct DereferenceStrEqual
     * @brief Function object that dereferences the given pointer and calls
     * operator== against the given string.  Assumes the pointer type defines
     * operator==(std::string).
     */
    template <typename T>
    struct DereferenceStrEqual
        : std::binary_function<const T*, std::string, bool>
    {
        bool operator()(const T *p, std::string s) const { return (*p == s); }
    };

    /**
     * @struct LengthLess
     * @brief Function object that determines if length of v1 is less than
     * length of v2.  Implicit interface assumes T offers a length() member.
     */
    struct LengthLess
    {
        template <typename T>
        bool operator()(const T& v1, const T& v2) const
        {
            return (v1.length() < v2.length());
        }
    };

    /**
     * @struct LengthGreater
     * @brief Function object that determines if length of v1 is greater than
     * length of v2.  Implicit interface assumes T offers a length() member.
     */
    struct LengthGreater
    {
        template <typename T>
        bool operator()(const T& v1, const T& v2) const
        {
            return (v1.length() > v2.length());
        }
    };

    /**
     * @struct FirstLess
     * @brief Function object for comparing 'first' members of a pair<T, U>
     * with operator<.
     */
    struct FirstLess
    {
        template <typename T, typename U>
        bool operator()(const std::pair<T, U>& p1,
                        const std::pair<T, U>& p2) const
        {
            return (p1.first < p2.first);
        }
    };

    /**
     * @struct FirstGreater
     * @brief Function object for comparing 'first' members of a pair<T, U>
     * with operator>.
     */
    struct FirstGreater
    {
        template <typename T, typename U>
        bool operator()(const std::pair<T, U>& p1,
                        const std::pair<T, U>& p2) const
        {
            return (p1.first > p2.first);
        }
    };

    /**
     * @struct SecondLess
     * @brief Function object for comparing 'second' members of a pair<T, U>
     * with operator<.
     */
    struct SecondLess
    {
        template <typename T, typename U>
        bool operator()(const std::pair<T, U>& p1,
                        const std::pair<T, U>& p2) const
        {
            return (p1.second < p2.second);
        }
    };

    /**
     * @struct SecondGreater
     * @brief Function object for comparing 'second' members of a pair<T, U>
     * with operator>.
     */
    struct SecondGreater
    {
        template <typename T, typename U>
        bool operator()(const std::pair<T, U>& p1,
                        const std::pair<T, U>& p2) const
        {
            return (p1.second > p2.second);
        }
    };

    /**
     * @struct SecondEqual
     * @brief Function object for comparing a string with the 'second' member of
     * a pair<string, string>.
     */
    struct SecondEqual : std::binary_function<std::string,
                         std::pair<std::string, std::string> , bool>
    {
        bool operator()(const std::string& str,
                        const std::pair<std::string, std::string>& p) const
        {
            return (str == p.second);
        }
    };

    /**
     * @struct EmptyFirst
     * @brief Function object for instantiating a new std::pair<string, T> with
     * the 'first' member as an empty string.
     */
    struct EmptyFirst
    {
        template <typename T>
        std::pair<std::string, T> operator()(const T& v) const
        { return std::pair<std::string, T>("", v); }

        template <typename T>
        std::pair<std::string, T>
        operator()(const std::pair<std::string, T>& v) const
        { return std::pair<std::string, T>("", v.second); }
    };

    /**
     * @struct DeleteAndNullify
     * @brief Function object that deletes the given pointer and sets it to
     * NULL.
     */
    struct DeleteAndNullify
    {
        template <typename T>
        void operator()(T *p) const
        {
            if (p)
            {
                delete p;
                p = NULL;
            }
        }
    };

    /**
     * @struct Appender
     * @brief Function object that calls T::append(const U&).
     * U defaults to T::value_type.
     */
    template <typename T, typename U = typename T::value_type>
    struct Appender : std::binary_function<U, T* const, void>
    {
        void operator()(const U& u, T * const v) const { v->append(u); }
    };

    /**
     * @struct FileExists
     * @brief Function object that returns util::file_exists().
     */
    struct FileExists
    {
        bool operator()(const std::string& path) const
        { return file_exists(path); }
    };

    /**
     * @struct IsDir
     * @brief Function object that returns util::is_dir().
     */
    struct IsDir
    {
        bool operator()(const std::string& path) const
        { return is_dir(path); }
    };

    /**
     * @struct IsFile
     * @brief Function object that returns util::is_file().
     */
    struct IsFile
    {
        bool operator()(const std::string& path) const
        { return is_file(path); }
    };

    /**
     * @struct regexMatch
     * @brief Function object for using Regex class with std algorithms.
     */
    struct regexMatch : std::binary_function<Regex, std::string, bool>
    {
        bool operator() (const Regex &re, const std::string& s) const
        { return (re == s); }
    };

    /**
     * @struct patternMatch
     * @brief Function object for using globs (pattern matching) with std
     * algorithms.
     */
    struct patternMatch : std::binary_function<std::string, std::string, bool>
    {
        bool operator() (const std::string& path,
                         const std::string& pattern) const
        { return (fnmatch(pattern.c_str(), path.c_str(), 0) == 0); }
    };

} // namespace util
} // namespace herdstat

#endif /* _HAVE_UTIL_FUNCTIONAL_HH */

/* vim: set tw=80 sw=4 et : */
