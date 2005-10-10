/*
 * libherdstat -- herdstat/portage/portage_file.hh
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

#ifndef _HAVE_PORTAGE_FILE_HH
#define _HAVE_PORTAGE_FILE_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file portage_file.hh
 * @brief Defines the PortageFileBase base class.
 */

#include <string>
#include <set>
#include <algorithm>
#include <functional>

#include <herdstat/noncopyable.hh>
#include <herdstat/util/container_base.hh>
#include <herdstat/util/regex.hh>
#include <herdstat/util/functional.hh>

namespace herdstat {
namespace portage {

    /**
     * @class PortageFileBase
     * @brief Base class for classes representing files containing unique
     * contents (one per line).
     */

    class PortageFileBase : public util::SetBase<std::string>,
                            private noncopyable
    {
        public:
            /// Default constructor.
            PortageFileBase() { }

            /** Constructor.
             * @param path Path to file.
             */
            PortageFileBase(const std::string& path);

            /// Destructor.
            virtual ~PortageFileBase() { }

            /** Find first element matching given regular expression.
             * @param re const reference to a util::Regex object.
             * @returns iterator to first element found or end() if not found.
             */
            inline iterator find(const util::Regex& re);

            /** Find first element matching given regular expression.
             * @param re const reference to a util::Regex object.
             * @returns const_iterator to first element found or end() if not
             * found.
             */
            inline const_iterator find(const util::Regex& re) const;

        protected:
            /// validate contents
            virtual void validate() const { }
            /// Read file contents into container.
            virtual void read();

            /// Get path.
            inline const std::string& path() const;
            /// Set path.
            inline void set_path(const std::string& path);

        private:
            std::string _path;
    };

    inline PortageFileBase::iterator
    PortageFileBase::find(const util::Regex& re)
    {
        return std::find_if(this->begin(), this->end(),
            std::bind1st(util::regexMatch(), re));
    }
    inline PortageFileBase::const_iterator
    PortageFileBase::find(const util::Regex& re) const
    {
        return std::find_if(this->begin(), this->end(),
            std::bind1st(util::regexMatch(), re));
    }
    inline const std::string& PortageFileBase::path() const { return _path; }
    inline void PortageFileBase::set_path(const std::string& path)
    { _path.assign(path); }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_PORTAGE_FILE_HH */

/* vim: set tw=80 sw=4 et : */
