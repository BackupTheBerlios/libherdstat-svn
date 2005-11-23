/*
 * libherdstat -- herdstat/doxygen.hh
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

#ifndef _HAVE_HERDSTAT_DOXYGEN_HH
#define _HAVE_HERDSTAT_DOXYGEN_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/doxygen.hh
 * @brief Main page documentation for Doxygen.
 */

/**
 * @mainpage libherdstat API Documentation
 *
 * @section overview Overview
 *
 * libherdstat is a C++ library offering interfaces for portage-related
 * things such as Gentoo-specific XML files, package searching, and
 * version sorting.  Many general-purpose utility classes/functions are
 * also offered.
 */

/**
 * @page Authors Authors
 * @section Authors
 * 
 * libherdstat was written by Aaron Walker <ka0ttic@gentoo.org>.
 */

/**
 * @page ChangeLog ChangeLog
 * @section ChangeLog ChangeLog
 * @verbinclude ChangeLog
 */

/**
 * @page License License
 * @section License License
 * @verbinclude COPYING
 */

/**
 * @namespace herdstat
 * @brief Main namespace all of libherdstat resides in.
 */

/**
 * @namespace herdstat::xml
 * @brief XML-related classes.
 */

/**
 * @namespace herdstat::util
 * @brief General-purpose utility classes/functions.
 */

/**
 * @namespace herdstat::portage
 * @brief portage-related classes/functions.
 */

#endif /* _HAVE_HERDSTAT_DOXYGEN_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
