/*
 * herdstat -- herdstat/util/regex.hh
 * $Id$
 * Copyright (c) 2005 Aaron Walker <ka0ttic@gentoo.org>
 *
 * This file is part of herdstat.
 *
 * herdstat is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * herdstat is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * herdstat; if not, write to the Free Software Foundation, Inc., 59 Temple
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

namespace herdstat {
namespace util {

    /**
     * POSIX Regular Expressions interface.
     */

    class Regex
    {
        public:
            /// compilation cflags
            enum cflags { };
            /// exec eflags
            enum eflags { };

            /// REG_EXTENDED
            static const cflags extended;
            /// REG_ICASE
            static const cflags icase;
            /// REG_NOSUB
            static const cflags nosub;
            /// REG_NEWLINE
            static const cflags newline;

            /// REG_NOTBOL
            static const eflags notbol;
            /// REG_NOTEOL
            static const eflags noteol;

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

            /** Get regular expression std::string.
             * @returns A std::string object.
             */
            inline const std::string& operator()() const;

            /** Is this regular expression std::string empty?
             * @returns A boolean value.
             */
            inline bool empty() const;

            /// Get CFLAGS.
            inline int get_cflags() const;
            /// Set CFLAGS.
            inline void set_cflags(int cflags);

            /// Get EFLAGS.
            inline int get_eflags() const;
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
    Regex::get_cflags() const
    {
        return _cflags;
    }

    inline void
    Regex::set_cflags(int cflags)
    {
        _cflags = cflags;
    }

    inline int
    Regex::get_eflags() const
    {
        return _eflags;
    }

    inline void
    Regex::set_eflags(int eflags)
    {
        _eflags = eflags;
    }

} // namespace util
} // namespace herdstat

#endif /* HAVE_REGEX_HH */

/* vim: set tw=80 sw=4 et : */
