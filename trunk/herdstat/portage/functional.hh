/*
 * libherdstat -- herdstat/portage/functional.hh
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

#ifndef _HAVE_PORTAGE_FUNCTIONAL_HH
#define _HAVE_PORTAGE_FUNCTIONAL_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/functional.hh
 * @brief portage-related function object definitions.
 */

#include <functional>
#include <herdstat/util/regex.hh>
#include <herdstat/portage/misc.hh>
#include <herdstat/portage/config.hh>

namespace herdstat {
namespace portage {

    /**
     * @struct Name
     * @brief Returns T::name().
     */
    struct Name
    {
        template <typename T>
        const std::string& operator()(const T& v) const { return v.name(); }
    };

    /**
     * @struct User
     * Returns T::user().
     */
    struct User
    {
        template <typename T>
        const std::string& operator()(const T& v) const { return v.user(); }
    };

    /**
     * @struct Email
     * Returns T::email().
     */

    struct Email
    {
        template <typename T>
        const std::string& operator()(const T& v) const { return v.email(); }
    };

    /**
     * @struct UserRegexMatch
     * @brief Compares regex against T::user().
     */
    template <typename T>
    struct UserRegexMatch : std::binary_function<util::Regex, T, bool>
    {
        bool operator()(const util::Regex &re, const T& v) const
        { return (re == v.user()); }
    };

    /**
     * @struct NameRegexMatch
     * @brief Compares regex against T::name().
     */
    template <typename T>
    struct NameRegexMatch : std::binary_function<util::Regex, T, bool>
    {
        bool operator()(const util::Regex &re, const T& v) const
        { return (re == v.name()); }
    };

    /**
     * @struct IsCategory
     * @brief Function object that determines whether the given string is a
     * category name.
     */
    struct IsCategory
    {
        bool operator()(const std::string& cat) const
        {
            return is_category(cat);
        }
    };

    /**
     * @struct IsEbuild
     * @brief Function object that returns is_ebuild(path).
     */

    struct IsEbuild
    {
        bool operator()(const std::string& path) const
        {
            return is_ebuild(path);
        }
    };

    /**
     * @struct IsPkgDir
     * @brief Function object that returns is_pkg_dir(path).
     */

    struct IsPkgDir
    {
        bool operator()(const std::string& path) const
        {
            return is_pkg_dir(path);
        }
    };

    /**
     * @struct GetPkgFromPath
     * @brief Function object that returns a "cat/pkg" string given a full
     * path to a package directory.
     */

    struct GetPkgFromPath
    {
        std::string operator()(const std::string& path) const
        {
            return get_pkg_from_path(path);
        }
    };

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_PORTAGE_FUNCTIONAL_HH */

/* vim: set tw=80 sw=4 et : */
