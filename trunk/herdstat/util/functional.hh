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
     * @struct Dereference functional.hh herdstat/util/functional.hh
     * @brief Function object that returns a dereferenced pointer to type T.
     */

    template <typename T>
    struct Dereference : std::unary_function<const T*, T>
    {
        const T& operator()(const T *p) const { return *p; }
    };

    /**
     * @struct First functional.hh herdstat/util/functional.hh
     * @brief Returns the 'first' member of a std::pair<K, V>.
     */

    template <typename T>
    struct First : std::unary_function<T, typename T::first_type>
    {
        const typename T::first_type&
        operator()(const T& v) const { return v.first; }
    };

    /**
     * @struct Second functional.hh herdstat/util/functional.hh
     * @brief Returns the 'second' member of a std::pair<K, V>.
     */

    template <typename T>
    struct Second : std::unary_function<T, typename T::second_type>
    {
        const typename T::second_type&
        operator()(const T& v) const { return v.second; }
    };

    /**
     * @struct EmptyFirst functional.hh herdstat/util/functional.hh
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
     * @struct DeleteAndNullify functional.hh herdstat/util/functional.hh
     * @brief Function object that deletes the given pointer and sets it to
     * NULL.
     */

    template <typename T>
    struct DeleteAndNullify : std::unary_function<T*, void>
    {
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
     * @struct New functional.hh herdstat/util/functional.hh
     * @brief Function object template that instaniates an object of type T,
     * passing an object of type U to its constructor.  U defaults to
     * std::string.
     */

    template <typename T, typename U = std::string>
    struct New : std::unary_function<T, U>
    {
        T operator()(const U& u) const
        { return T(u); }
    };

    /**
     * @struct Appender functional.hh herdstat/util/functional.hh
     * @brief Function object that calls T::append(const U&).
     * U defaults to T::value_type.
     */

    template <typename T, typename U = typename T::value_type>
    struct Appender : std::binary_function<U, T* const, void>
    {
        void operator()(const U& u, T * const v) const { v->append(u); }
    };

    /**
     * @struct FileExists functional.hh herdstat/util/functional.hh
     * @brief Function object that determines whether the given path exists.
     */

    struct FileExists : std::unary_function<std::string, bool>
    {
        bool operator()(const std::string& path) const
        { return file_exists(path); }
    };

    /**
     * @struct IsDir functional.hh herdstat/util/functional.hh
     * @brief Function object that determines whether the given path is a
     * directory.
     */

    struct IsDir : std::unary_function<std::string, bool>
    {
        bool operator()(const std::string& path) const
        { return is_dir(path); }
    };

    /**
     * @struct IsFile functional.hh herdstat/util/functional.hh
     * @brief Function object that determines whether the given path is a
     * regular file.
     */

    struct IsFile : std::unary_function<std::string, bool>
    {
        bool operator()(const std::string& path) const
        { return is_file(path); }
    };

    /**
     * @struct Basename functional.hh herdstat/util/functional.hh
     * @brief Function object that returns the basename of the given path.
     */

    struct Basename : std::unary_function<std::string, std::string>
    {
        std::string operator()(const std::string& path) const
        { return util::basename(path); }
    };

    /**
     * @struct Dirname functional.hh herdstat/util/functional.hh
     * @brief Function object that returns the dirname of the given path.
     */

    struct Dirname : std::unary_function<std::string, std::string>
    {
        std::string operator()(const std::string& path) const
        { return util::dirname(path); }
    };

    /**
     * @struct regexMatch functional.hh herdstat/util/functional.hh
     * @brief Function object for determining whether the given string matches
     * the given util::Regex object.
     */

    struct regexMatch : std::binary_function<Regex, std::string, bool>
    {
        bool operator() (const Regex &re, const std::string& s) const
        { return (re == s); }
    };

    /**
     * @struct patternMatch functional.hh herdstat/util/functional.hh
     * @brief Function object for determining whether the given glob pattern
     * matches the given path.
     */

    struct patternMatch : std::binary_function<std::string, std::string, bool>
    {
        bool operator() (const std::string& path,
                         const std::string& pattern) const
        { return (fnmatch(pattern.c_str(), path.c_str(), 0) == 0); }
    };

    ///@{
    /**
     * Composition function objects as described/implemented in Josuttis'
     * "The C++ Standard Library - A Tutorial and Reference".
     */

    /**
     * @class compose_f_gx_t functional.hh herdstat/util/functional.hh
     * @brief Function object adapter that uses the result of a unary operation
     * as input to another unary operation.
     */

    template <typename Op1, typename Op2>
    class compose_f_gx_t
        : public std::unary_function<typename Op2::argument_type,
                                     typename Op1::result_type>
    {
        public:
            /// Constructor.
            compose_f_gx_t(const Op1& o1, const Op2& o2)
                : op1(o1), op2(o2) { }

            typename Op1::result_type
            operator()(const typename Op2::argument_type& x) const
            { return op1(op2(x)); }

        private:
            Op1 op1;
            Op2 op2;
    };

    /**
     * Helper function for the compose_f_gx_t adapter.
     */

    template <typename Op1, typename Op2>
    inline compose_f_gx_t<Op1, Op2>
    compose_f_gx(const Op1& o1, const Op2& o2)
    {
        return compose_f_gx_t<Op1, Op2>(o1, o2);
    }

    /**
     * @class compose_f_gx_hx_t functional.hh herdstat/util/functional.hh
     * @brief Function object adapter that allows the combination of two
     * criteria logically to formulate a single criterion.  Use this when you
     * want to do something like "greater than 10 and less than 15".
     */

    template <typename Op1, typename Op2, typename Op3>
    class compose_f_gx_hx_t
        : public std::unary_function<typename Op2::argument_type,
                                     typename Op1::result_type>
    {
        public:
            /// Constructor.
            compose_f_gx_hx_t(const Op1& o1, const Op2& o2, const Op3& o3)
                : op1(o1), op2(o2), op3(o3) { }

            typename Op1::result_type
            operator()(const typename Op2::argument_type& x) const
            {
                return op1(op2(x), op3(x));
            }

        private:
            Op1 op1;
            Op2 op2;
            Op3 op3;
    };

    /**
     * Helper function for the compose_f_gx_hx_t adapter.
     */

    template <typename Op1, typename Op2, typename Op3>
    inline compose_f_gx_hx_t<Op1, Op2, Op3>
    compose_f_gx_hx(const Op1& o1, const Op2& o2, const Op3& o3)
    {
        return compose_f_gx_hx_t<Op1, Op2, Op3>(o1, o2, o3);
    }

    /**
     * @class compose_f_gx_hy_t functional.hh herdstat/util/functional.hh
     * @brief Function object adapter for use when you have two arguments to
     * pass to two different unary predicates (Op2 and Op3).  The results from
     * both are passed to the binary predicate Op1.
     */

    template <typename Op1, typename Op2, typename Op3>
    class compose_f_gx_hy_t
        : std::binary_function<typename Op2::argument_type,
                               typename Op3::argument_type,
                               typename Op1::result_type>
    {
        public:
            compose_f_gx_hy_t(const Op1& o1, const Op2& o2, const Op3& o3)
                : op1(o1), op2(o2), op3(o3) { }

            typename Op1::result_type
            operator()(const typename Op2::argument_type& x,
                       const typename Op3::argument_type& y) const
            {
                return op1(op2(x), op3(y));
            }

        private:
            Op1 op1;
            Op2 op2;
            Op3 op3;
    };

    /**
     * Helper function for the compose_f_gx_hy_t adapter.
     */

    template <typename Op1, typename Op2, typename Op3>
    inline compose_f_gx_hy_t<Op1, Op2, Op3>
    compose_f_gx_hy(const Op1& o1, const Op2& o2, const Op3& o3)
    {
        return compose_f_gx_hy_t<Op1, Op2, Op3>(o1, o2, o3);
    }

    ///@}

} // namespace util
} // namespace herdstat

#endif /* _HAVE_UTIL_FUNCTIONAL_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
