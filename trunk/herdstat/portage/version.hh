/*
 * libherdstat -- herdstat/portage/version.hh
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

#ifndef HAVE_PORTAGE_VERSION_HH
#define HAVE_PORTAGE_VERSION_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/version.hh
 * @brief Defines version-related classes (version sorting, version string
 * container, etc).
 */

#include <string>
#include <set>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <cassert>

#include <herdstat/util/container_base.hh>
#include <herdstat/util/functional.hh>
#include <herdstat/util/file.hh>

namespace herdstat {
namespace portage {

    /**
     * @class version_map
     * @brief Version component (${P}, ${PN}, etc) map.
     */

    class version_map : public util::MapBase<std::string, std::string>
    {
        public:
            /** Constructor.
             * @param path Path to ebuild.
             */
            version_map(const std::string &path);

            /** Get value mapped to given key.
             * @returns copy of value mapped to key.
             */
            const std::string operator[](const std::string &key) const
            {
                const_iterator i = this->find(key);
                return (i == this->end() ? "" : i->second);
            }

            /// Get version string.
            const std::string& version() const { return _verstr; }

        private:
            /// Parse version string and insert components into map.
            void parse();

            std::string _verstr;
    };

    /**
     * @class version_string.
     * @brief Represents a single version string.
     */

    class version_string
    {
        public:
            /** Constructor.
             * @param path Path to ebuild.
             */
            version_string(const std::string &path);

            /// Implicit conversion to std::string.
            operator std::string() const;

            /** Get version string (minus the suffix).
             * @returns String object.
             */
            const std::string &version() const { return this->_version(); }

            /** Get path to ebuild for this version.
             * @returns String object.
             */
            const std::string &ebuild() const { return this->_ebuild; }

            /** Get version component map for this version string.
             * @returns Reference to version_map object.
             */
            const version_map& components() const { return this->_v; }

            /** Determine whether given version_string object is less
             * than this one.
             * @param that Reference to a version_string object.
             * @returns    A boolean value.
             */
            bool operator< (const version_string& that) const;

            /** Determine whether given version_string object is greater
             * than this one.
             * @param that Reference to a version_string object.
             * @returns    A boolean value.
             */
            bool operator> (const version_string& that) const
            { return (that < *this); }

            /** Determine whether given version_string object is equal
             * to this one.
             * @param that Reference to a version_string object.
             * @returns    A boolean value.
             */
            bool operator==(const version_string& that) const;

            /** Determine whether given version_string object is not equal
             * to this one.
             * @param that Reference to a version_string object.
             * @returns    A boolean value.
             */
            bool operator!=(const version_string& that) const
            { return not (*this == that); }

        private:
            /**
             * @class suffix
             * @brief Represents a version suffix (_alpha, _beta, etc).
             */

            class suffix
            {
                public:
                    /// Default constructor.
                    suffix();

                    /** Constructor.
                     * @param pvr PVR std::string object (version+revision).
                     */
                    suffix(const std::string &pvr);

                    /** Get suffix string.
                     * @returns String object.
                     */
                    const std::string& str() const { return this->_suffix; }

                    /** Get suffix version string.
                     * @returns String object.
                     */
                    const std::string& version() const
                    { return this->_suffix_ver; }

                    /** Determine whether that suffix is less than this suffix.
                     * @param that Reference to a suffix object.
                     * @returns    A boolean value.
                     */
                    bool operator< (const suffix& that) const;

                    /** Determine whether that suffix is greater than this
                     * suffix.
                     * @param that Reference to a suffix object.
                     * @returns    A boolean value.
                     */
                    bool operator> (const suffix& that) const
                    { return (that < *this); }
                    
                    /** Determine whether that suffix is equal to this suffix.
                     * @param that Reference to a suffix object.
                     * @returns    A boolean value.
                     */
                    bool operator== (const suffix& that) const;
                    
                    /** Determine whether that suffix is not equal to this
                     * suffix.
                     * @param that Reference to a suffix object.
                     * @returns    A boolean value.
                     */
                    bool operator!= (const suffix& that) const
                    { return not (*this == that); }

                private:
                    /// Parse ${PVR}
                    void parse(const std::string &pvr) const;

                    /// Valid suffixes.
                    static std::vector<std::string> _suffixes;
                    /// Suffix std::string.
                    mutable std::string _suffix;
                    /// Suffix version std::string.
                    mutable std::string _suffix_ver;
            };

            /**
             * @class nosuffix
             * @brief Represents package version minus the suffix.
             */

            class nosuffix
            {
                public:
                    nosuffix();

                    /** Constructor.
                     * @param pv PV std::string object.
                     */
                    nosuffix(const std::string &pv);

                    /** Get version string minus suffix.
                     * @returns String object.
                     */
                    const std::string& operator() () const
                    { return this->_version; }

                    /** Determine whether that nosuffix is less than this
                     * nosuffix.
                     * @param that Reference to a nosuffix object.
                     * @returns    A boolean value.
                     */
                    bool operator< (const nosuffix& that) const;

                    /** Determine whether that nosuffix is greater than this
                     * nosuffix.
                     * @param that Reference to a nosuffix object.
                     * @returns    A boolean value.
                     */
                    bool operator> (const nosuffix& that) const
                    { return (that < *this); }

                    /** Determine whether that nosuffix is equal to this
                     * nosuffix.
                     * @param that Reference to a nosuffix object.
                     * @returns    A boolean value.
                     */
                    bool operator== (const nosuffix& that) const;

                    /** Determine whether that nosuffix is not equal to this
                     * nosuffix.
                     * @param that Reference to a nosuffix object.
                     * @returns    A boolean value.
                     */
                    bool operator!= (const nosuffix& that) const
                    { return not (*this == that); }

                private:
                    /// Parse ${PV}.
                    void parse(const std::string& pv) const;

                    /// Version string (minus suffix).
                    mutable std::string _version;
                    /// Any extra non-digit characters.
                    mutable std::string _extra;
            };

            /// Absolute path to ebuild.
            const std::string _ebuild;
            /// Version components map.
            const version_map  _v;
            /// Reference to actual version string
            const std::string &_verstr;
            /// Our version suffix.
            const suffix _suffix;
            /// Our version minus suffix.
            const nosuffix _version;
    };

    /** 
     * @class versions
     * @brief version_string container.
     * Generally used for all versions of a single package.
     */

    class versions : public util::SetBase<version_string>
    {
        public:
            /// Default constructor.
            versions();

            /** Constructor.  Instantiate version_string objects for each
             * ebuild existing in the specified package directory.
             * @param path Path to package directory.
             */
            versions(const std::string &path);

            /** Constructor.  Instantiate version_string objects for each
             * ebuild existing in each element (package directories).
             * @param v Vector of package directory paths.
             */
            versions(const std::vector<std::string> &v);

            /// Get first version_string.
            inline const version_string& front() const;
            /// Get last version_string.
            inline const version_string& back() const;

            //@{
            /** Find version string using ebuild matching path.
             * @param path Ebuild path.
             * @returns iterator to first match or end() if no match.
             */
            inline iterator find(const std::string& path);
            inline const_iterator find(const std::string& path) const;
            //@}

            /** Insert given version_string.
             * @param v const reference to version_string.
             * @returns True if insertion was successful.
             */
            inline bool insert(const version_string& v);

            /** Instantiate and insert a version_string object with the
             * specified path.
             * @param p Path.
             * @returns True if insertion was successful.
             */
            inline bool insert(const std::string &p);

            /** Assign a new package directory clearing any previously
             * contained version_string instances.
             * @param p Path to package directory.
             */
            void assign(const std::string &p);

            /** Append a new package directory.
             * @param p Path to package directory.
             */
            void append(const std::string &p);
    };

    inline versions::iterator
    versions::find(const std::string& p)
    {
        return this->find(version_string(p));
    }

    inline versions::const_iterator
    versions::find(const std::string& p) const
    {
        return this->find(version_string(p));
    }

    inline bool
    versions::insert(const std::string& path)
    {
        return util::SetBase<version_string>::insert(version_string(path)).second;
    }

    inline bool
    versions::insert(const version_string& v)
    {
        return util::SetBase<version_string>::insert(v).second;
    }

    inline const version_string&
    versions::front() const
    {
        assert(not this->empty());
        return *(this->begin());
    }

    inline const version_string&
    versions::back() const
    {
        assert(not this->empty());
        const_iterator i = this->end();
        return *(--i);
    }

} // namespace portage
} // namespace herdstat

#endif

/* vim: set tw=80 sw=4 et : */
