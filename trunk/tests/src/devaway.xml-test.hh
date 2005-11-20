/*
 * libherdstat -- tests/src/devaway.xml-test.hh
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

#ifndef _HAVE__DEVAWAY_XML_TEST_HH
#define _HAVE__DEVAWAY_XML_TEST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/util/file.hh>
#include <herdstat/util/string.hh>
#include <herdstat/xml/init.hh>
#include <herdstat/portage/devaway_xml.hh>
#include "test_handler.hh"

DECLARE_TEST_HANDLER(DevawayXMLTest)

void
DevawayXMLTest::operator()(const opts_type& opts) const
{
    assert(not opts.empty());

    herdstat::xml::GlobalInit();

    const std::string& path(opts.front());
    assert(herdstat::util::is_file(path));
    
    herdstat::portage::devaway_xml devaway;
    devaway.parse(path);

    const herdstat::portage::Developers& devs(devaway.devs());

    std::cout << "Away developers(" << devs.size() << ")" << std::endl;

    herdstat::portage::Developers::const_iterator i;
    for (i = devs.begin() ; i != devs.end() ; ++i)
        std::cout << i->user() << ": "
            << herdstat::util::tidy_whitespace(i->awaymsg()) << std::endl;

    std::cout << std::endl;

    assert((i = devs.find("lv")) != devs.end());
    std::cout << i->user() << " - "
        << herdstat::util::tidy_whitespace(i->awaymsg()) << std::endl;
}

#endif /* _HAVE__DEVAWAY.XML_TEST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */