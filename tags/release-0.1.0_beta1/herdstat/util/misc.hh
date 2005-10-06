/*
 * herdstat -- herdstat/util/misc.hh
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

#ifndef HAVE_UTIL_MISC_HH
#define HAVE_UTIL_MISC_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/util/misc.hh
 * @brief Defines miscellaneous classes/functions.
 */

#include <string>
#include <map>

enum color_name_T
{
    red,
    green,
    blue,
    yellow,
    orange,
    magenta,
    cyan,
    white,
    black,
    none
};

/* commonly-used utility functions */

namespace herdstat {
namespace util {

    void debug(const char *, ...);

    /// getcwd() wrapper.
    std::string getcwd();

    /** Determine username from email address.
     * @param e E-mail address.
     * @returns A std::string object.
     */
    std::string get_user_from_email(const std::string &e);

    /** Determine current user.
     * Uses ECHANGELOG_USER, if set.  Uses USER otherwise.
     * @returns A std::string object.
     */
    std::string current_user();

    /// Determine current terminal width.
    std::string::size_type getcols();

    /** Format date std::string.
     * @param t Reference to a time_t object.
     * @param f Format std::string as accepted by strftime(3).
     * @returns A constant std::string object.
     */
    const std::string format_date(const std::time_t &t,
        const char *f = "%a %b %d %T %Z %Y");

    /** Format date std::string.
     * @param t Reference to a std::string object that contains the time.
     * @param f Format std::string as accepted by strftime(3).
     * @returns A constant std::string object.
     */
    const std::string format_date(const std::string &t,
        const char *f = "%a %b %d %T %Z %Y");

    /** Get time_t value from date string.
     * @param str time string.
     * @param fmt format of time string.
     * @returns value as time_t.
     */
    std::time_t str2epoch(const char *str, const char *fmt);

    const std::string get_elapsed_yrs(const std::string& date);

    /**
     * Color map.
     */

    class ColorMap
    {
        public:
            /** Access color string associated with the given color type.
             * @param c Color type (color_name_T).
             * @returns The associated string object.
             */
            std::string& operator[](color_name_T c)
            { return this->_cm[c]; }

            /** Access color string associated with the given color name.
             * @param s Color name.
             * @returns The associated string object.
             */
            std::string& operator[](const std::string &s);

        private:
            /// Internal color map.
            class cmap : public std::map<color_name_T, std::string>
            {
                public:
                    /// Default constructor.  Fills map.
                    cmap()
                    {
                        (*this)[red]     = "\033[0;31m";
                        (*this)[green]   = "\033[0;32m";
                        (*this)[blue]    = "\033[1;34m";
                        (*this)[yellow]  = "\033[1;33m";
                        (*this)[orange]  = "\033[0;33m";
                        (*this)[magenta] = "\033[1;35m";
                        (*this)[cyan]    = "\033[1;36m";
                        (*this)[black]   = "\033[0;30m";
                        (*this)[white]   = "\033[0;1m";
                        (*this)[none]    = "\033[00m";
                    }
            };

            /// Internal color map.
            static cmap _cm;
    };

} // namespace util
} // namespace herdstat

#endif /* HAVE_UTIL_MISC_HH */

/* vim: set tw=80 sw=4 et : */
