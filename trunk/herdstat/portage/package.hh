/*
 * libherdstat -- herdstat/portage/package.hh
 * $Id$
 * Copyright (c) 2005 Aaron Walker <ka0ttic@gentoo.org>
 *
 * This file is part of libherdstat.
 *
 * libherdstat is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * libherdstat is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * libherdstat; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 325, Boston, MA  02111-1257  USA
 */

#ifndef _HAVE__PACKAGE_HH
#define _HAVE__PACKAGE_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <string>
#include <algorithm>
#include <iterator>

#include <herdstat/util/regex.hh>
#include <herdstat/util/algorithm.hh>
#include <herdstat/portage/misc.hh>
#include <herdstat/portage/exceptions.hh>
#include <herdstat/portage/version.hh>

/** Rough estimate of number of packages updated from time to time.
 * Used for reserve()'ing to prevent a sleu of allocations. */
#define PKGLIST_RESERVE            10250

namespace herdstat {
namespace portage {

    /**
     * @class Package
     * @brief Represents a "package" that exists in either PORTDIR or an
     * overlay.
     */

    class Package
    {
        public:
            /// Default constructor.
            Package();

            /// Copy constructor.
            Package(const Package& that);

            /** Constructor.
             * @param name Package name.
             * @param portdir Directory package lives in.
             */
            Package(const std::string& name,
                    const std::string& portdir = "");

            /// Destructor.
            ~Package();

            /// Copy assignment operator.
            Package& operator= (const Package& that);

            /// Implicit conversion to category/package string.
            inline operator const std::string&() const;

            /// Get package name.
            inline const std::string& name() const;
            /// Set package name.
            void set_name(const std::string& name);

            /// Get category this package is in.
            inline const std::string& category() const;
            /// Set category this package is in.
            inline void set_category(const std::string& cat);

            /// Get portdir this package is in (may be an overlay).
            inline const std::string& portdir() const;
            /// Set portdir this package is in.
            inline void set_portdir(const std::string& dir);

            /// Get a versions object for this package.
            inline const portage::versions& versions() const;

            ///@{
            /** Compare that Package to this Package.
             * Only compares the full category/package string for container
             * sorting criterion.
             */
            inline bool operator< (const Package& that) const;
            inline bool operator<=(const Package& that) const;
            inline bool operator> (const Package& that) const;
            inline bool operator>=(const Package& that) const;
            inline bool operator==(const Package& that) const;
            inline bool operator!=(const Package& that) const;
            ///@}

            //@{
            /** Does the given regular expression match or not match our
             * category/package string?
             */
            inline bool operator==(const util::Regex& re) const;
            inline bool operator!=(const util::Regex& re) const;
            ///@}

        private:
            std::string _name;
            std::string _cat;
            std::string _dir;
            std::string _full;
            mutable portage::versions *_versions;
    };

    inline Package::operator const std::string&() const { return _full; }
    inline const std::string& Package::category() const { return _cat; }
    inline void Package::set_category(const std::string& cat) { _cat.assign(cat); }
    inline const std::string& Package::name() const { return _name; }
    inline const std::string& Package::portdir() const { return _dir; }
    inline void Package::set_portdir(const std::string& dir) { _dir.assign(dir); }

    inline bool
    Package::operator< (const Package& that) const { return (_full < that._full); }
    inline bool
    Package::operator<=(const Package& that) const { return (_full <= that._full); }
    inline bool
    Package::operator> (const Package& that) const { return (_full > that._full); }
    inline bool
    Package::operator>=(const Package& that) const { return (_full >= that._full); }
    inline bool
    Package::operator==(const Package& that) const { return (_full == that._full); }
    inline bool
    Package::operator!=(const Package& that) const { return (_full != that._full); }
    inline bool
    Package::operator==(const util::Regex& re) const { return (re == _full); }
    inline bool
    Package::operator!=(const util::Regex& re) const { return (re != _full); }

    inline const portage::versions&
    Package::versions() const
    {
        if (not _versions)
            _versions = new portage::versions(_dir+"/"+_full);
        return *_versions;
    }

    /**
     * @class PackageList
     * @brief Represents a sorted package list of all directories inside valid
     * categories.  Note that for speed reasons, no validation is done (other
     * than checking that it's a directory and it exists), so you should use
     * the portage::is_pkg_dir() function or the portage::IsPkgDir() function
     * object to validate an element before using it.
     */

    class PackageList : public util::VectorBase<Package>
    {
        public:
            /// Default constructor.
            PackageList();

            /** Constructor.
             * @param portdir PORTDIR to search.
             * @param overlays const reference to a vector of strings denoting
             * overlays (defaults to empty).
             */
            PackageList(const std::string& portdir, const std::vector<std::string>&
                overlays = std::vector<std::string>());

            /// Fill container.
            void fill();

            /// Implicit conversion to const vector<Package>&
            operator const container_type&() const { return this->container(); }

        private:
            const std::string& _portdir;
            const std::vector<std::string>& _overlays;
    };

    /**
     * @class PackageFinder
     * @brief Interface for portage package searching.
     */

    class PackageFinder
    {
        public:
            /** Constructor.
             * @param pkglist const reference to a PackageList object.
             */
            PackageFinder(const PackageList& pkglist);

            /// Clear search results.
            void clear_results() { _results.clear(); }
            /// Get search results.
            const std::vector<Package>& results() const { return _results; }

            /** Perform search on the given criteria.
             * @param v const reference to either a std::string or a
             * util::Regex.
             * @returns const reference to search results.
             */
            template <typename T>
            const std::vector<Package>&
            operator()(const T& v) throw (NonExistentPkg);

            const std::vector<Package>&
            operator()(const char * const v)
            { return operator()(std::string(v)); }

        private:
            template <typename T>
            struct PkgMatches : std::binary_function<Package, T, bool>
            {
                bool operator()(const Package& pkg, const T& criteria) const
                {           /* criteria matches cat/pkg string? */
                    return ((criteria == std::string(pkg)) or
                            /* or matches just the pkg string? */
                            (criteria == pkg.name())) and
                            /* and is a valid package directory? */
                             is_pkg_dir(pkg.portdir()+"/"+std::string(pkg));
                }
            };

            const PackageList& _pkglist;
            std::vector<Package> _results;
    };

    PackageFinder::PackageFinder(const PackageList& pkglist)
        : _pkglist(pkglist), _results() { }

    template <typename T>
    const std::vector<Package>&
    PackageFinder::operator()(const T& v) throw (NonExistentPkg)
    {
        util::copy_if(_pkglist.begin(), _pkglist.end(),
            std::back_inserter(_results),
            std::bind2nd(PkgMatches<T>(), v));

        if (_results.empty())
            throw NonExistentPkg(v);

        return _results;
    }

    /**
     * @class PackageWhich
     * @brief Interface for finding the newest ebuild of a package.
     */

    class PackageWhich
    {
        public:
            void clear_results() { _results.clear(); }
            const std::vector<std::string>& results() const { return _results; }

            template <typename T>
            const std::vector<std::string>&
            operator()(const T& v,
                       const std::vector<Package>& results) throw (NonExistentPkg);

            template <typename T>
            const std::vector<std::string>&
            operator()(const T& v, const PackageList& pkglit) throw (NonExistentPkg);

        private:
            struct GetWhichFromPkg
            {
                std::string operator()(const Package& pkg) const
                {
                    const versions& versions(pkg.versions());
                    if (versions.empty())
                        throw NonExistentPkg(pkg);
                    return versions.back().ebuild();
                }
            };

            std::vector<std::string> _results;
    };

    template <typename T>
    const std::vector<std::string>&
    PackageWhich::operator()(const T& v,
                const std::vector<Package>& finder_results) throw (NonExistentPkg)
    {
        std::transform(finder_results.begin(), finder_results.end(),
            std::back_inserter(_results), GetWhichFromPkg());
        
        if (_results.empty())
            throw NonExistentPkg(v);

        return _results;
    }

    template <typename T>
    const std::vector<std::string>&
    PackageWhich::operator()(const T& v,
                             const PackageList& pkglist) throw (NonExistentPkg)
    {
        PackageFinder find(pkglist);
        const std::vector<Package>& finder_results(find(v));

        std::transform(finder_results.begin(), finder_results.end(),
            std::back_inserter(_results), GetWhichFromPkg());

        if (_results.empty())
            throw NonExistentPkg(v);

        return _results;
    }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE__PACKAGE_HH */

/* vim: set tw=80 sw=4 et : */
