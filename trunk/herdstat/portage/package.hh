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

#include <herdstat/exceptions.hh>
#include <herdstat/util/timer.hh>
#include <herdstat/util/regex.hh>
#include <herdstat/util/algorithm.hh>
#include <herdstat/portage/misc.hh>
#include <herdstat/portage/exceptions.hh>
#include <herdstat/portage/version.hh>
#include <herdstat/portage/keywords.hh>

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

            /// Get full category/package name.
            inline const std::string& full() const;
            /// Set full category/package name.
            void set_full(const std::string& full);

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

            /// Get path to package directory.
            inline const std::string& path() const;
            /// Set path to package directory.
            inline void set_path(const std::string& path);

            /// Is this package located in an overlay?
            inline bool in_overlay() const;

            /// Get a KeywordsMap object for each ebuild of this package.
            inline const KeywordsMap& keywords() const;

            ///@{
            /** Compare that Package to this Package.
             * Compares the full category/package string and portdir.
             */
            inline bool operator< (const Package& that) const;
            inline bool operator<=(const Package& that) const;
            inline bool operator> (const Package& that) const;
            inline bool operator>=(const Package& that) const;
            inline bool operator==(const Package& that) const;
            inline bool operator!=(const Package& that) const;
            ///@}

            ///@{
            /// Does the given string match this full category/package name?
            inline bool operator< (const std::string& full) const;
            inline bool operator<=(const std::string& full) const;
            inline bool operator> (const std::string& full) const;
            inline bool operator>=(const std::string& full) const;
            inline bool operator==(const std::string& full) const;
            inline bool operator!=(const std::string& full) const;
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
            std::string _path;
            mutable KeywordsMap *_kwmap;
    };

    inline Package::operator const std::string&() const { return _full; }
    inline const std::string& Package::category() const { return _cat; }
    inline void Package::set_category(const std::string& cat) { _cat.assign(cat); }
    inline const std::string& Package::name() const { return _name; }
    inline const std::string& Package::portdir() const { return _dir; }
    inline const std::string& Package::full() const { return _full; }
    inline void Package::set_portdir(const std::string& dir) { _dir.assign(dir); }
    inline void Package::set_path(const std::string& path) { _path.assign(path); }
    inline const std::string& Package::path() const { return _path; }

    inline bool Package::in_overlay() const
    {
        static const std::string& portdir(GlobalConfig().portdir());
        return (_dir != portdir);
    }

    inline bool
    Package::operator< (const Package& that) const
    {
        /* if package names are equal, this is only less than that if this
         * portdir is the real portdir and that portdir isn't */
        return (_full == that._full ?
                    not ((not in_overlay() and not that.in_overlay()) or
                        not that.in_overlay()) : _full < that._full);
    }

    inline bool
    Package::operator<=(const Package& that) const
    { return not (*this > that); }

    inline bool
    Package::operator> (const Package& that) const
    { return (that < *this); }
    
    inline bool
    Package::operator>= (const Package& that) const
    { return not (*this < that); }
    
    inline bool
    Package::operator== (const Package& that) const
    { return ((_full == that._full) and (_dir == that._dir)); }
    
    inline bool
    Package::operator!= (const Package& that) const
    { return not (*this == that); }

    inline bool
    Package::operator< (const std::string& full) const
    { return (_full < full); }
    inline bool
    Package::operator<=(const std::string& full) const
    { return (_full <= full); }
    inline bool
    Package::operator> (const std::string& full) const
    { return (_full > full); }
    inline bool
    Package::operator>=(const std::string& full) const
    { return (_full >= full); }
    inline bool
    Package::operator==(const std::string& full) const
    { return (_full == full); }
    inline bool
    Package::operator!=(const std::string& full) const
    { return (_full != full); }

    inline bool
    Package::operator==(const util::Regex& re) const
    { return (re == _full); }

    inline bool
    Package::operator!=(const util::Regex& re) const
    { return (re != _full); }

    inline const KeywordsMap&
    Package::keywords() const
    {
        if (not _kwmap)
            _kwmap = new KeywordsMap(_path);
        return *_kwmap;
    }

    inline bool
    operator< (const std::string& lhs, const Package& rhs)
    {
        return (lhs < rhs.full());
    }

    inline bool
    operator<=(const std::string& lhs, const Package& rhs)
    {
        return (lhs <= rhs.full());
    }

    inline bool
    operator> (const std::string& lhs, const Package& rhs)
    {
        return (lhs > rhs.full());
    }

    inline bool
    operator>=(const std::string& lhs, const Package& rhs)
    {
        return (lhs >= rhs.full());
    }

    inline bool
    operator==(const std::string& lhs, const Package& rhs)
    {
        return (lhs == rhs.full());
    }

    inline bool
    operator!=(const std::string& lhs, const Package& rhs)
    {
        return (lhs != rhs.full());
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
            /** Default constructor.
             * @param fill Fill with all packages in the tree?
             */
            PackageList(bool fill = true);

            /** Constructor.
             * @param portdir PORTDIR to search.
             * @param overlays const reference to a vector of strings denoting
             * overlays (defaults to empty).
             * @param fill Fill with all packages in the tree?
             */
            PackageList(const std::string& portdir, const std::vector<std::string>&
                overlays = std::vector<std::string>(), bool fill = true);

            /// Destructor.
            ~PackageList();

            /// Fill container.
            void fill();
            /// Has our container been fill()'d?
            bool filled() const { return _filled; }

            ///@{
            /// Is the specified package present in our container?
            inline bool has_package(const std::string& pkg) const;
            inline bool has_package(const Package& pkg) const;
            ///@}

            /// Implicit conversion to const vector<Package>&
            operator const container_type&() const { return this->container(); }

        private:
            const std::string& _portdir;
            const std::vector<std::string>& _overlays;
            bool _filled;
    };

    inline bool
    PackageList::has_package(const std::string& pkg) const
    {
        return std::binary_search(this->begin(), this->end(), pkg);
    }

    inline bool
    PackageList::has_package(const Package& pkg) const
    {
        return has_package(pkg.full());
    }

    /**
     * @struct FullPkgName
     * @brief Function object for explicit conversion from Package to
     * std::string (the category/package string).
     */

    struct FullPkgName : std::unary_function<Package, std::string>
    {
        std::string operator()(const Package& pkg) const
        { return pkg.full(); }
    };

    /**
     * @struct FullPkgNameLess
     * @brief Function object for sorting by full package name only (Package
     * operators sort by name and portdir).
     */
    
    struct FullPkgNameLess : std::binary_function<Package, Package, bool>
    {
        bool operator()(const Package& p1, const Package& p2) const
        { return (p1.full() < p2.full()); }
    };

    /**
     * @struct FullPkgNameEqual
     * @brief Function object for sorting by full package name only (Package
     * operators sort by name and portdir).
     */

    struct FullPkgNameEqual
        : std::binary_function<Package, Package, bool>
    {
        bool operator()(const Package& p1, const Package& p2) const
        { return (p1.full() == p2.full()); }
    };

    /**
     * @struct NewPackage
     * @brief Function object for instantiating a Package class with the given
     * path (to the package directory) and a portdir (may be an overlay).
     */

    struct NewPackage
        : std::binary_function<std::string, std::string, Package>
    {
        Package
        operator()(const std::string& path, const std::string& portdir) const
        { return Package(get_pkg_from_path(path), portdir); }
    };

    /**
     * @struct GetWhichFromPackage
     * @brief Function object for retrieving the path to the newest ebuild for
     * the given Package object.
     */

    struct GetWhichFromPackage : std::unary_function<Package, std::string>
    {
        std::string operator()(const Package& pkg) const
        {
            BacktraceContext c("herdstat::portage::GetWhichFromPackage::operator()("+pkg.full()+")");

            const KeywordsMap& versions(pkg.keywords());
            if (versions.empty())
                throw NonExistentPkg(pkg);
            return versions.back().first.ebuild();
        }
    };

    /**
     * @struct PackageMatches
     * @brief Function object for comparing a Package object with an object of
     * type T.
     */

    template <typename T>
    struct PackageMatches : std::binary_function<Package, T, bool>
    {
        bool operator()(const Package& pkg, const T& criteria) const
        {    
                    /* criteria matches cat/pkg string? */
            return ((pkg.full() == criteria) or
                    /* or matches just the pkg string? */
                    (pkg.name() == criteria));
        }
    };

    /**
     * @struct PackageIsValid
     * @brief Function object for determining whether the given Package object
     * has a valid package directory.
     */

    struct PackageIsValid : std::unary_function<Package, bool>
    {
        bool operator()(const Package& pkg) const
        { return is_pkg_dir(pkg.path()); }
    };

    /**
     * @struct PackageLivesInOverlay
     * @brief Function object that determines whether the given Package object
     * represents a package that exists in an overlay (or technically one whose
     * portdir member is not the real PORTDIR).
     */

    struct PackageLivesInOverlay : std::unary_function<Package, bool>
    {
        bool operator()(const Package& pkg) const
        { return pkg.in_overlay(); }
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

            /// Destructor.
            ~PackageFinder();

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
            operator()(const T& v, util::Timer *timer = NULL)
                throw (NonExistentPkg);

            const std::vector<Package>&
            operator()(const char * const v, util::Timer *timer = NULL)
                throw (NonExistentPkg)
            { return operator()(std::string(v), timer); }

        private:
            const PackageList& _pkglist;
            std::vector<Package> _results;
    };

    template <typename T>
    const std::vector<Package>&
    PackageFinder::operator()(const T& v, util::Timer *timer) throw (NonExistentPkg)
    {
        BacktraceContext c("herdstat::portage::PackageFinder::operator()");

        if (timer and not timer->is_running())
            timer->start();

        /* copy those packages in _pkglist that
         *      a) match the given criteria (v), and
         *      b) have a valid package directory
         * to our _results vector.
         */
        util::copy_if(_pkglist.begin(), _pkglist.end(),
            std::back_inserter(_results),
            util::compose_f_gx_hx(std::logical_and<bool>(),
                    std::bind2nd(PackageMatches<T>(), v),
                    PackageIsValid()));

        if (timer)
            timer->stop();

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
            /// Default constructor.
            PackageWhich();

            /// Destructor.
            ~PackageWhich();

            /// Clear search results.
            void clear_results() { _results.clear(); }
            /// Get search results.
            const std::vector<std::string>& results() const { return _results; }

            /** Get the latest ebuild for each package in the given vector. Any
             * vector<Package> will do, but this is mainly offered for use with
             * PackageFinder results.
             * @param results const reference to a std::vector<Package>.
             * @returns vector of ebuild paths.
             */
            const std::vector<std::string>&
            operator()(const std::vector<Package>& results) throw (NonExistentPkg);

            /** Get the latest ebuild(s) for the given package string/portdir.
             * @param pkg Full category/package string.
             * @parma portdir PORTDIR the package is located in.
             * @returns vector of ebuild paths.
             */
            inline const std::vector<std::string>&
            operator()(const std::string& pkg, const std::string& portdir)
                throw (NonExistentPkg);

            /** Get the latest ebuild(s) for those packages matching the given
             * type T using the given PackageList.  Uses PackageFinder to get
             * the list of matching packages.
             * @param v search criteria of type T.
             * @param pkglist const reference to a PackageList.
             * @returns vector of ebuild paths.
             */
            template <typename T>
            inline const std::vector<std::string>&
            operator()(const T& v, const PackageList& pkglist) throw (NonExistentPkg);

        private:
            std::vector<std::string> _results;
    };

    inline const std::vector<std::string>&
    PackageWhich::operator()(const std::string& pkg, const std::string& portdir)
        throw (NonExistentPkg)
    {
        BacktraceContext c("herdstat::portage::PackageWhich::operator()("+pkg+", "+portdir+")");

        if (not util::is_dir(portdir+"/"+pkg))
            throw NonExistentPkg(pkg);

        Package p(pkg, portdir);
        const KeywordsMap& v(p.keywords());
        _results.push_back(v.back().first.ebuild());
        return _results;
    }

    template <typename T>
    inline const std::vector<std::string>&
    PackageWhich::operator()(const T& v,
                             const PackageList& pkglist) throw (NonExistentPkg)
    {
        PackageFinder find(pkglist);
        return operator()(find(v));
    }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE__PACKAGE_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
