/*
 * libherdstat -- herdstat/portage/keywords.hh
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

#ifndef _HAVE_KEYWORDS_HH
#define _HAVE_KEYWORDS_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file keywords.hh
 * @brief Defines the Keyword/Keywords classes.
 */

#include <string>
#include <herdstat/util/container_base.hh>
#include <herdstat/portage/ebuild.hh>
#include <herdstat/portage/archs.hh>

namespace herdstat {
namespace portage {

    /**
     * @class Keyword
     * @brief Represents a single architecture keyword.
     */
    class Keyword
    {
        public:
            Keyword(const std::string& kw);

            const char mask() const { return _mask; }
            const std::string& arch() const { return _arch; }
            const std::string str() const
            { std::string s(1, _mask); s+=_arch; return s; }

            bool operator< (const Keyword& that) const;
            bool operator> (const Keyword& that) const
            { return (that < *this); }
            bool operator==(const Keyword& that) const
            { return ((_mask == that._mask) and (_arch == that._arch)); }
            bool operator!=(const Keyword& that) const
            { return (*this != that); }

        private:
            /**
             * @class maskc
             * @brief Keyword mask character ('~' for example).
             */
            class maskc
            {
                public:
                    maskc();
                    maskc(const char c);
                    maskc& operator= (const char c)
                    { _c = c; return *this; }
                    
                    /// implicit conversion to char
                    operator char() const { return _c; }

                    bool empty() const { return (_c == 0); }

                    bool operator< (const maskc& that) const;
                    bool operator> (const maskc& that) const
                    { return (that < *this); }
                    bool operator==(const maskc& that) const
                    { return (_c == that._c); }
                    bool operator!=(const maskc& that) const
                    { return (*this != that); }

                private:
                    char _c;
            };


            /// parse keyword.
            void parse(const std::string& kw);

            std::string _arch;
            maskc _mask;
            const Archs& _valid_archs;
            static const std::string _valid_masks;
    };

    /**
     * @class Keywords
     * @brief Keyword container.
     * Usually used for all keywords for a certain ebuild.
     * Also able to provide a pretty-printed keywords string.
     */

    class Keywords : public util::SetBase<Keyword>
    {
        public:
            /** Default constructor.
             * @param use_colors Use colors when formatting keywords string.
             */
            Keywords(bool use_colors = false);

            /** Constructor.
             * @param path Path to ebuild.
             * @param use_colors Use colors when formatting keywords string.
             */
            Keywords(const std::string& path, bool use_colors = false);

            /** Constructor.
             * @param e Pre-existing ebuild instance.
             * @param use_colors Use colors when formatting keywords string.
             */
            Keywords(const ebuild& e, bool use_colors = false);

            /** Assign new ebuild path.
             * @param path Path to ebuild.
             * @param use_colors Use colors when formatting keywords string.
             */
            void assign(const std::string& path, bool use_colors = false);

            /** Assign new ebuild.
             * @param e Pre-existing ebuild instance.
             * @param use_colors Use colors when formatting keywords string.
             */
            void assign(const ebuild& e, bool use_colors = false);

            /// Get formatted keywords string.
            inline const std::string& str() const;

            /// Get path to ebuild associated with these keywords.
            inline const std::string& path() const;

            /// Are all keywords masked?
//            bool all_masked() const;
            /// Are all ebuilds unstable?
//            bool all_unstable() const;

        private:
            void fill();
            /// prepare keywords string
            void format();

            bool _color;
            ebuild _ebuild;
            std::string _str;
    };

    inline const std::string& Keywords::str() const { return _str; }
    inline const std::string& Keywords::path() const { return _ebuild.path(); }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_KEYWORDS_HH */

/* vim: set tw=80 sw=4 et : */
