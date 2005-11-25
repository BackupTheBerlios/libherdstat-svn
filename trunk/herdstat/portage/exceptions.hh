/*
 * libherdstat -- herdstat/portage/exceptions.hh
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

#ifndef HAVE_PORTAGE_EXCEPTIONS_HH
#define HAVE_PORTAGE_EXCEPTIONS_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/exceptions.hh
 * @brief Defines portage-related exception classes.
 */

#include <iostream>
#include <vector>

#include <herdstat/exceptions.hh>
#include <herdstat/util/regex.hh>

namespace herdstat {
namespace portage {

    /**
     * @class BadVersionSuffix exceptions.hh herdstat/portage/exceptions.hh
     * @brief Bad version suffix exception.
     */

    class BadVersionSuffix : public Exception
    {
        public:
            BadVersionSuffix(const std::string &msg) throw();
            virtual ~BadVersionSuffix() throw();
            virtual const char *what() const throw();
    };

    /**
     * @class AmbiguousPkg exceptions.hh herdstat/portage/exceptions.hh
     * @brief Ambiguous package name exception.
     */

    class AmbiguousPkg : public Exception
    {
        public:
            AmbiguousPkg(const std::vector<std::string>& pkgs) throw();
            template <typename InputIterator>
            AmbiguousPkg(InputIterator first, InputIterator last) throw()
                : _name(), _packages(first, last) { _set_name(*first); }
            virtual ~AmbiguousPkg() throw();

            const std::string& name() const throw() { return _name; }
            const std::vector<std::string>& packages() const throw()
            { return _packages; }

        private:
            void _set_name(const std::string& name) throw();

            /// Ambiguous name.
            std::string _name;
            /// Vector of possible matches.
            const std::vector<std::string> _packages;
    };

    /**
     * @class NonExistentPkg exceptions.hh herdstat/portage/exceptions.hh
     * @brief Non-existent package exception.
     */

    class NonExistentPkg : public Exception
    {
        public:
            NonExistentPkg(const std::string &msg) throw();
            NonExistentPkg(const util::Regex& re) throw();
            virtual ~NonExistentPkg() throw();
            virtual const char *what() const throw();
        
        private:
            const bool _regex;
    };

    /**
     * @class QAException exceptions.hh herdstat/portage/exceptions.hh
     * @brief Quality Assurance exception.
     */

    class QAException : public Exception
    {
        public:
            QAException(const std::string &msg) throw();
            virtual ~QAException() throw();
    };

    /**
     * @class QAErrnoException exceptions.hh herdstat/portage/exceptions.hh
     * @brief Quality Assurance (with strerror()) exception.
     */

    class QAErrnoException : public ErrnoException
    {
        public:
            QAErrnoException(const std::string &msg) throw();
            virtual ~QAErrnoException() throw();
            virtual const char *what() const throw();
    };

    /**
     * @class InvalidKeywordMask exceptions.hh herdstat/portage/exceptions.hh
     * @brief Exception for invalid mask characters ('~' in ~arch).
     */

    class InvalidKeywordMask : public Exception
    {
        public:
            InvalidKeywordMask(const char c) throw();
            virtual ~InvalidKeywordMask() throw();
            virtual const char *what() const throw();

        private:
            const char _mask;
    };

    /**
     * @class InvalidArch exceptions.hh herdstat/portage/exceptions.hh
     * @brief Exception for invalid architectures.
     */

    class InvalidArch : public Exception
    {
        public:
            InvalidArch(const std::string& arch) throw();
            virtual ~InvalidArch() throw();
            virtual const char *what() const throw();
    };

} // namespace portage
} // namespace herdstat

#endif

/* vim: set tw=80 sw=4 fdm=marker et : */
