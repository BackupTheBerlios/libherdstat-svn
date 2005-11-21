/*
 * libherdstat -- herdstat/util/regex.hh
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

#ifndef HAVE_REGEX_HH
#define HAVE_REGEX_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/util/regex.hh
 * @brief Defines the Regex class.
 */

#include <string>
#include <functional>
#include <cstddef>
#include <cassert>
#include <sys/types.h>
#include <regex.h>

#include <herdstat/util/container_base.hh>

namespace herdstat {
namespace util {

    /**
     * @class Regex regex.hh herdstat/util/regex.hh
     * @brief POSIX Regular Expressions interface.
     */

    class Regex
    {
        public:
            /// compilation cflags
            enum Cflags { };
            /// exec eflags
            enum Eflags { };

            /// REG_EXTENDED
            static const Cflags extended;
            /// REG_ICASE
            static const Cflags icase;
            /// REG_NOSUB
            static const Cflags nosub;
            /// REG_NEWLINE
            static const Cflags newline;

            /// REG_NOTBOL
            static const Eflags notbol;
            /// REG_NOTEOL
            static const Eflags noteol;

            /// Default constructor.
            Regex();

            /// Copy constructor.
            Regex(const Regex& that);

            /** Constructor.
             * @param c CFLAGS.
             * @param e EFLAGS.
             */
            Regex(int c, int e = 0);

            /** Constructor.
             * @param r regular expression string.
             * @param c CFLAGS.
             * @param e EFLAGS.
             */
            Regex(const std::string& r, int c = 0, int e = 0);

            /// Destructor.
            ~Regex();

            /** Assign a new regular expression.
             * @param r regular expression string.
             */
            void assign(const std::string& r);

            /** Assign a new regular expression.
             * @param r regular expression string.
             * @param c CFLAGS.
             * @param e EFLAGS.
             */
            void assign(const std::string& r , int c, int e = 0);

            /** Assign a new regular expression (no CFLAGS/EFLAGS).
             * @param s regular expression string.
             * @returns a Regex object.
             */
            inline Regex& operator= (const std::string& s);

            /// Copy assignment operator.
            Regex& operator= (const Regex& that);

            /** Determine if this regex matches the specified std::string.
             * @param cmp Comparison string.
             * @returns   A boolean value.
             */
            inline bool operator== (const std::string& cmp) const;

            /** Determine if this regex does not match the specified std::string.
             * @param cmp Comparison string.
             * @returns   A boolean value.
             */
            inline bool operator!= (const std::string& cmp) const;

            /** Determine if this regex is equal to that regex.  Only compares
             * uncompiled regex strings.
             * @param that const reference to Regex object.
             * @returns A boolean value.
             */
            inline bool operator== (const Regex& that) const;

            /** Determine if this regex is not equal to that regex.  Only
             * compares uncompiled regex strings.
             * @param that const reference to Regex object.
             * @returns A boolean value.
             */
            inline bool operator!= (const Regex& that) const;

            /** Determine if this regex is less than that regex.  Only
             * compares uncompiled regex strings.
             * @param that const reference to Regex object.
             * @returns A boolean value.
             */
            inline bool operator< (const Regex& that) const;

            /** Determine if this regex is greater than that regex.  Only
             * compares uncompiled regex strings.
             * @param that const reference to Regex object.
             * @returns A boolean value.
             */
            inline bool operator> (const Regex& that) const;

            /** Get regular expression std::string.
             * @returns A std::string object.
             */
            inline const std::string& operator()() const;

            /** Is this regular expression std::string empty?
             * @returns A boolean value.
             */
            inline bool empty() const;

            /// Get CFLAGS.
            inline int cflags() const;
            /// Set CFLAGS.
            inline void set_cflags(int cflags);

            /// Get EFLAGS.
            inline int eflags() const;
            /// Set EFLAGS.
            inline void set_eflags(int eflags);

        private:
            /// Clean up compiled regex_t
            void cleanup();
            /// Compile regex.
            void compile();

            std::string _str;
            bool        _compiled;
            int         _cflags;
            int         _eflags;
            regex_t     _regex;
    };

    inline Regex&
    Regex::operator= (const std::string& re)
    {
        this->assign(re);
        return *this;
    }

    inline bool
    Regex::operator== (const std::string& cmp) const
    {
        return (regexec(&_regex, cmp.c_str(), 0, NULL, _eflags) == 0);
    }

    inline bool
    Regex::operator!= (const std::string& cmp) const
    {
        return not (*this == cmp);
    }

    inline bool
    Regex::operator== (const Regex& that) const
    {
        return (_str == that._str);
    }

    inline bool
    Regex::operator!= (const Regex& that) const
    {
        return (_str != that._str);
    }

    inline bool
    Regex::operator< (const Regex& that) const
    {
        return (_str < that._str);
    }

    inline bool
    Regex::operator> (const Regex& that) const
    {
        return (_str > that._str);
    }

    inline const std::string&
    Regex::operator()() const
    {
        return _str;
    }

    inline bool
    Regex::empty() const
    {
        return _str.empty();
    }

    inline int
    Regex::cflags() const
    {
        return _cflags;
    }

    inline void
    Regex::set_cflags(int cflags)
    {
        _cflags = cflags;
    }

    inline int
    Regex::eflags() const
    {
        return _eflags;
    }

    inline void
    Regex::set_eflags(int eflags)
    {
        _eflags = eflags;
    }

    ///@{
    /// Compare a Regex with a std::string on the left-hand side.
    inline bool
    operator==(const std::string& lhs, const Regex& rhs)
    {
        return (rhs == lhs);
    }

    inline bool
    operator!=(const std::string& lhs, const Regex& rhs)
    {
        return (rhs != lhs);
    }
    ///@}

    /**
     * @class RegexMap regex.hh herdstat/util/regex.hh
     * @brief Acts like an unsorted map (vector of unique pairs) with Regex
     * objects mapped to objects of type T.  Provides a few map-compatible
     * member functions such as insert(), operator[](), and find().
     */

    template <typename T>
    class RegexMap
        : public herdstat::util::VectorBase<std::pair<Regex, T> >
    {
        public:
            typedef herdstat::util::VectorBase<std::pair<Regex, T> > base_type;
            typedef typename base_type::container_type container_type;
            typedef typename container_type::size_type size_type;
            typedef typename container_type::difference_type difference_type;
            typedef typename container_type::value_type value_type;
            typedef typename container_type::iterator iterator;
            typedef typename container_type::const_iterator const_iterator;
            typedef Regex key_type;
            typedef T mapped_type;

            mapped_type& operator[](const key_type& k);
            std::pair<iterator, bool> insert(const value_type& v);

            inline iterator find(const std::string& str);
            inline const_iterator find(const std::string& str) const;
    };

    template <typename T>
    inline typename RegexMap<T>::iterator
    RegexMap<T>::find(const std::string& str)
    {
        for (iterator i = this->begin() ; i != this->end() ; ++i)
            if (i->first == str) return i;
        return this->end();
    }

    template <typename T>
    inline typename RegexMap<T>::const_iterator
    RegexMap<T>::find(const std::string& str) const
    {
        for (const_iterator i = this->begin() ; i != this->end() ; ++i)
            if (i->first == str) return i;
        return this->end();
    }

    template <typename T>
    typename RegexMap<T>::mapped_type&
    RegexMap<T>::operator[](const key_type& k)
    {
        for (iterator i = this->begin() ; i != this->end() ; ++i)
            if (i->first == k) return i->second;
        return this->insert(this->end(), value_type(k, "")).second;
    }

    template <typename T>
    std::pair<typename RegexMap<T>::iterator, bool>
    RegexMap<T>::insert(const value_type& v)
    {
        for (iterator i = this->begin() ; i != this->end() ; ++i)
            if (i->first == v.first)
                return std::pair<iterator, bool>(this->end(), false);
        return std::pair<iterator, bool>(
                base_type::insert(this->end(), v), true);
    }

} // namespace util
} // namespace herdstat

#endif /* HAVE_REGEX_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
