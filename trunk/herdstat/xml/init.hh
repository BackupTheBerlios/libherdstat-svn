/*
 * herdstat -- xml/init.hh
 * $Id: init.hh 537 2005-09-08 13:15:10Z ka0ttic $
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

#ifndef _HAVE_INIT_HH
#define _HAVE_INIT_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/xml/init.hh
 * @brief Defines the Init class.
 */

#include <xmlwrapp/init.h>

namespace herdstat {
namespace xml {

    /**
     * XML initialization object.
     * Calls underlying libxml2 initializations.
     */

    class Init
    {
        public:
            Init(bool validate = false);

        private:
            static ::xml::init _init;
    };

} // namespace xml
} // namespace herdstat

#endif /* _HAVE_INIT_HH */

/* vim: set tw=80 sw=4 et : */
