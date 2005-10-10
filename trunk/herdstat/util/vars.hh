/*
 * libherdstat -- herdstat/util/vars.hh
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

#ifndef HAVE_VARS_HH
#define HAVE_VARS_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/util/vars.hh
 * @brief Defines the vars class.
 */

#include <map>
#include <utility>
#include <herdstat/util/file.hh>

namespace herdstat {
namespace util {

    /**
     * Represents a file with variables in the form of VARIABLE=VALUE,
     * stored in key,value pairs.
     */

    class vars : public BaseFile,
                 public MapBase<std::string, std::string>
    {
        public:
            /// Default constructor.
            vars();

            /** Constructor.
             * @param path Path.
             */
            vars(const std::string &path);

            virtual ~vars();

            /** Overloaded operator[] since std::map doesn't provide
             * a const version.
             * @param k Key to look up.
             * @returns A std::string object (Value mapped to Key).
             */
            inline mapped_type operator[] (const key_type& k) const;

            /** Dump keys/values to specified stream.
             * @param s Output stream.
             */
            virtual void dump(std::ostream &s) const;

            /// Read file.
            virtual void read();

            /** Read specified file.
             * @param p Path.
             */
            virtual void read(const std::string &p);

            /// Set default variables to be present before substitution.
            void set_defaults();

        protected:
            virtual void do_set_defaults() { }

        private:
            /** Perform elementary variable substitution.
             * @param v Variable.
             */
            void subst(std::string &v);

            /// subst() recursion depth (safeguard).
            unsigned short _depth;
    };

    inline vars::mapped_type vars::operator[] (const key_type& k) const
    {
        const_iterator i = this->find(k);
        return (i == this->end() ? "" : i->second);
    }

} // namespace util
} // namespace herdstat

#endif

/* vim: set tw=80 sw=4 et : */
