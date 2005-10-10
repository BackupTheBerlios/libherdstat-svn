/*
 * libherdstat -- herdstat/portage/categories.hh
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

#ifndef _HAVE_CATEGORIES_HH
#define _HAVE_CATEGORIES_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/categories.hh
 * @brief Defines the Categories class.
 */

#include <herdstat/portage/portage_file.hh>

namespace herdstat {
namespace portage {

    /**
     * @class Categories
     * @brief Represents a container of portage package categories.
     */

    class Categories : public PortageFileBase
    {
        public:
            /** Default constructor.
             * @param validate Validate whether categories are valid?
             */
            Categories(bool validate = false);

            /** Constructor.
             * @param portdir PORTDIR to look in.
             * @param validate Validate whether categories are valid?
             */
            Categories(const std::string& portdir, bool validate = false);

        protected:
            virtual void validate() const;
            virtual void read();

        private:
            const std::string& _portdir;
            const bool _validate;
    };

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_CATEGORIES_HH */

/* vim: set tw=80 sw=4 et : */
