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
#include <herdstat/portage/version.hh>

namespace herdstat {
namespace portage {

    /**
     * @class Keyword keywords.hh herdstat/portage/keywords.hh
     * @brief Represents a single architecture keyword.
     */
    class Keyword
    {
        public:
            /** Constructor.
             * @param kw keyword string.
             */
            Keyword(const std::string& kw);

            /// Get mask character (or nul byte if empty).
            char mask() const { return _mask; }
            /// Get architecture.
            const std::string& arch() const { return _arch; }
            /// Get keyword string.
            const std::string str() const
            { return (std::string(1, _mask)+_arch); }

            /** Is this Keyword less that that Keyword?
             * @param that const reference to Keyword
             * @returns Boolean value.
             */
            inline bool operator< (const Keyword& that) const;

            /** Is this Keyword greater than that Keyword?
             * @param that const reference to Keyword
             * @returns Boolean value
             */
            bool operator> (const Keyword& that) const
            { return (that < *this); }

            /** Is this Keyword equal to that Keyword?
             * @param that const reference to Keyword
             * @returns Boolean value
             */
            bool operator==(const Keyword& that) const
            { return ((_mask == that._mask) and (_arch == that._arch)); }

            /** Is this Keyword not equal to that Keyword?
             * @param that const reference to Keyword
             * @returns Boolean value
             */
            bool operator!=(const Keyword& that) const
            { return (*this != that); }

            /// Is this a masked keyword?
            bool is_masked() const { return _mask == '-'; }
            /// Is this a testing keyword?
            bool is_testing() const { return _mask == '~'; }
            /// Is this a stable keyword?
            bool is_stable() const { return _mask.empty(); }

        private:
            /**
             * @class maskc
             * @brief Keyword mask character ('~' for example).
             */
            class maskc
            {
                public:
                    /// Default constructor.
                    maskc();

                    /** Constructor.
                     * @param c mask character
                     */
                    maskc(const char c);

                    /** Assignment operator.
                     * @param c mask character.
                     */
                    maskc& operator= (const char c)
                    { _c = c; return *this; }
                    
                    /// Implicit conversion to char
                    operator char() const { return _c; }

                    /// Do we not hold a mask character?
                    bool empty() const { return (_c == '\0'); }

                    /** Is this maskc less than that maskc?
                     * @param that const reference to maskc
                     * @returns Boolean value
                     */
                    bool operator< (const maskc& that) const;

                    /** Is this maskc greater than that maskc?
                     * @param that const reference to maskc
                     * @returns Boolean value
                     */
                    bool operator> (const maskc& that) const
                    { return (that < *this); }

                    /** Is this maskc equal to that maskc?
                     * @param const reference to maskc
                     * @returns Boolean value
                     */
                    bool operator==(const maskc& that) const
                    { return (_c == that._c); }
                    
                    /** Is this maskc not equal to that maskc?
                     * @param const reference to maskc
                     * @returns Boolean value
                     */
                    bool operator!=(const maskc& that) const
                    { return (*this != that); }

                    ///@{
                    /// Compare this with a character.
                    bool operator< (const char c) const
                    { return (_c < c); }
                    bool operator> (const char c) const
                    { return (_c > c); }
                    bool operator==(const char c) const
                    { return (_c == c); }
                    bool operator!=(const char c) const
                    { return (_c != c); }
                    ///@}
                
                private:
                    char _c;
            };


            /// parse keyword.
            void parse(const std::string& kw);

            std::string _arch;
            maskc _mask;
            const Archs& _valid_archs;
            static const char * const _valid_masks;
    };

    inline bool
    Keyword::operator< (const Keyword& that) const
    {
        return ((_mask == that._mask) ?
                (_arch < that._arch) : (_mask < that._mask));
    }

    /**
     * @class Keywords keywords.hh herdstat/portage/keywords.hh
     * @brief Keyword container.
     * Usually used for all keywords for a certain ebuild.
     * Also able to provide a pretty-printed keywords string.
     */

    class Keywords : public util::SetBase<Keyword>
    {
        public:
            /// Default constructor.
            Keywords();

            /** Constructor.
             * @param path Path to ebuild.
             */
            Keywords(const std::string& path);

            /** Constructor.
             * @param e Pre-existing ebuild instance
             */
            Keywords(const Ebuild& e);

            /// Destructor.
            virtual ~Keywords();

            /** Assign new ebuild path.
             * @param path Path to ebuild
             */
            void assign(const std::string& path);

            /** Assign new ebuild.
             * @param e Pre-existing ebuild instance
             */
            void assign(const Ebuild& e);

            /// Get formatted keywords string.
            inline const std::string& str() const;

            /// Get path to ebuild associated with these keywords.
            inline const std::string& path() const;

            /// Are all keywords masked?
            inline bool all_masked() const;
            /// Are all keywords testing?
            inline bool all_testing() const;
            /// Are all keywords stable?
            inline bool all_stable() const;

        private:
            void fill();
            /// prepare keywords string
            void format();

            Ebuild _ebuild;
            std::string _str;
    };

    inline const std::string& Keywords::str() const { return _str; }
    inline const std::string& Keywords::path() const { return _ebuild.path(); }

    inline bool
    Keywords::all_masked() const
    {
        const difference_type size(this->size());
        return (std::count_if(this->begin(), this->end(),
                    std::mem_fun_ref(&Keyword::is_masked)) == size);
    }

    inline bool
    Keywords::all_testing() const
    {
        const difference_type size(this->size());
        return (std::count_if(this->begin(), this->end(),
                    std::mem_fun_ref(&Keyword::is_testing)) == size);
    }

    inline bool
    Keywords::all_stable() const
    {
        const difference_type size(this->size());
        return (std::count_if(this->begin(), this->end(),
                    std::mem_fun_ref(&Keyword::is_stable)) == size);
    }

    /**
     * @class KeywordsMap keywords.hh herdstat/portage/keywords.hh
     * @brief Maps VersionString objects to Keywords objects.
     */

    class KeywordsMap : public VersionsMap<Keywords>
    {
        public:
            /** Constructor.  Instantiate/insert a new VersionString/Keywords
             * object for each ebuild in the given package directory.
             * @param pkgdir Package directory.
             */
            KeywordsMap(const std::string& pkgdir);

            /// Destructor.
            virtual ~KeywordsMap();

            inline const value_type& front() const;
            inline const value_type& back() const;
    };

    inline const KeywordsMap::value_type&
    KeywordsMap::front() const
    {
        assert(not this->empty());
        return *(this->begin());
    }

    inline const KeywordsMap::value_type&
    KeywordsMap::back() const
    {
        assert(not this->empty());
        const_iterator i = this->end();
        return *(--i);
    }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_KEYWORDS_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
