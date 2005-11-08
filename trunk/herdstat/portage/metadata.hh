/*
 * libherdstat -- herdstat/portage/metadata.hh
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

#ifndef _HAVE_METADATA_HH
#define _HAVE_METADATA_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/metadata.hh
 * @brief Defines the metadata class.
 */

#include <string>
#include <herdstat/util/regex.hh>
#include <herdstat/portage/herd.hh>

namespace herdstat {
namespace portage {

    /**
     * @class metadata
     * @brief Represents the data contained in a metadata.xml file.
     */

    class metadata
    {
        public:
            /// Default constructor.
            metadata();

            /** Constructor.
             * @param pkg Package name.
             */
            metadata(const std::string &pkg);

            /// Destructor.
            ~metadata();

            /// Is this metadata from a cateogry?
            inline bool is_category() const;
            /// Get package name this metadata belongs to.
            inline const std::string& pkg() const;
            /// Get package name this metadata belongs to.
            inline const std::string& name() const; /* synonym for pkg() */
            /// Get long description.
            inline const std::string& longdesc() const;

            /// Set whether this is a category metadata.
            inline void set_category(bool cat);
            /// Set package name.
            inline void set_pkg(const std::string &pkg);
            /// Set long description.
            inline void set_longdesc(const std::string &longdesc);

            /// Get herds contained in this metadata.
            inline Herds& herds();
            /// Get herds contained in this metadata.
            inline const Herds& herds() const;
            /// Get developers contained in this metadata.
            inline Developers& devs();
            /// Get developers contained in this metadata.
            inline const Developers& devs() const;

        private:
            std::string _pkg;
            std::string _longdesc;
            bool _cat;
            mutable Herds *_herds;
            mutable Developers *_devs;
    };

    inline bool metadata::is_category() const { return _cat; }
    inline const std::string& metadata::pkg() const { return _pkg; }
    inline const std::string& metadata::name() const { return _pkg; }
    inline const std::string& metadata::longdesc() const { return _longdesc; }
    inline void metadata::set_category(bool cat) { _cat = cat; }
    inline void metadata::set_pkg(const std::string& pkg) { _pkg.assign(pkg); }
    inline void metadata::set_longdesc(const std::string& longdesc)
    { _longdesc.assign(longdesc); }

    inline const Herds&
    metadata::herds() const
    {
        if (not _herds) _herds = new Herds();
        return *_herds;
    }

    inline const Developers&
    metadata::devs() const
    {
        if (not _devs) _devs = new Developers();
        return *_devs;
    }

    inline Herds&
    metadata::herds()
    {
        if (not _herds) _herds = new Herds();
        return *_herds;
    }

    inline Developers&
    metadata::devs()
    {
        if (not _devs) _devs = new Developers();
        return *_devs;
    }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_METADATA_HH */

/* vim: set tw=80 sw=4 et : */
