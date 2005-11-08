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
     * @class BadVersionSuffix
     * @brief Bad version suffix exception.
     */

    class BadVersionSuffix : public Exception
    {
        public:
            BadVersionSuffix() { }
            BadVersionSuffix(const char *msg) : Exception(msg) { }
            BadVersionSuffix(const std::string &msg) : Exception(msg) { }
            virtual ~BadVersionSuffix() throw() { }
            virtual const char *what() const throw()
            {
                std::string s("Invalid version suffix: ");
                s += this->message();
                return s.c_str();
            }
    };

    /**
     * @class AmbiguousPkg
     * @brief Ambiguous package name exception.
     */

    class AmbiguousPkg : public Exception
    {
        public:
            AmbiguousPkg() : packages() { }
            AmbiguousPkg(const std::vector<std::string> &v)
                : packages(v) { }
            template <typename InputIterator>
            AmbiguousPkg(InputIterator first, InputIterator last)
                : packages(first, last) { }
            virtual ~AmbiguousPkg() throw() { }

            virtual const std::string name() const
            {
                std::string s;
                if (not this->packages.empty())
                {
                    std::string::size_type pos = this->packages.front().find('/');
                    if (pos == std::string::npos)
                        s = this->packages.front();
                    else
                        s = this->packages.front().substr(pos + 1);
                }
                return s;
            }

            /// Vector of possible matches.
            const std::vector<std::string> packages;
    };

    /**
     * @class NonExistentPkg
     * @brief Non-existent package exception.
     */

    class NonExistentPkg : public Exception
    {
        public:
            NonExistentPkg() : regex(false) { }
            NonExistentPkg(const char *msg) : Exception(msg), regex(false) { }
            NonExistentPkg(const std::string &msg) : Exception(msg), regex(false) { }
            NonExistentPkg(const util::Regex& re)  : Exception(re()), regex(true) { }
            virtual ~NonExistentPkg() throw() { }
            virtual const char *what() const throw()
            {
                if (regex)
                    return (std::string("Failed to find any packages matching '") +
                            this->message() + "'.").c_str();

                return (std::string(this->message()) +
                        " doesn't seem to exist.").c_str();
            }

        private:
            const bool regex;
    };

    /**
     * @class QAException
     * @brief Quality Assurance exception.
     */

    class QAException : public Exception
    {
        public:
            QAException() { }
            QAException(const char *msg) : Exception(msg) { }
            QAException(const std::string &msg) : Exception(msg) { }
            virtual ~QAException() throw() { }
    };

    /**
     * @class QAErrnoException
     * @brief Quality Assurance (with strerror()) exception.
     */

    class QAErrnoException : public ErrnoException
    {
        public:
            QAErrnoException() { }
            QAErrnoException(const char *msg) : ErrnoException(msg) { }
            QAErrnoException(const std::string &msg) : ErrnoException(msg) { }
            virtual ~QAErrnoException() throw() { }
            virtual const char *what() const throw()
            {
                std::string s("QA Violation: ");
                s += ErrnoException::what();
                return s.c_str();
            }
    };

    /**
     * @class InvalidKeywordMask
     * @brief Exception for invalid mask characters ('~' in ~arch).
     */

    class InvalidKeywordMask : public Exception
    {
        public:
            InvalidKeywordMask(const char c) : _mask(c) { }
            virtual ~InvalidKeywordMask() throw() { }
            virtual const char *what() const throw()
            {
                std::string s("Invalid keyword mask character '");
                s += _mask + "'.";
                return s.c_str();
            }

        private:
            const char _mask;
    };

    class InvalidArch : public Exception
    {
        public:
            InvalidArch(const std::string& arch) : Exception(arch) { }
            virtual ~InvalidArch() throw() { }
            virtual const char *what() const throw()
            {
                std::string s("Invalid arch '");
                s += std::string(this->message()) + "'.";
                return s.c_str();
            }
    };

} // namespace portage
} // namespace herdstat

#endif

/* vim: set tw=80 sw=4 et : */
