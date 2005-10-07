/*
 * herdstat -- herdstat/exceptions.hh
 * $Id$
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

#ifndef _HAVE_HERDSTAT_EXCEPTIONS_HH
#define _HAVE_HERDSTAT_EXCEPTIONS_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/exceptions.hh
 * @brief Defines exception classes used in libherdstat.
 */

#include <exception>
#include <stdexcept>
#include <sys/types.h>
#include <regex.h>

/// Main namespace all of libherdstat resides in.
namespace herdstat {

    /**
     * @mainpage
     *
     * libherdstat is a C++ library offering interfaces for portage-related
     * things such as Gentoo-specific XML files, package searching, and
     * version sorting.  Many general-purpose utility classes/functions are
     * also offered.
     */

    /**
     * @class BaseException
     * @brief Base exception class.  All exception classes defined by libherdstat
     * derive from this class.
     */
    class BaseException : public std::exception { };

    /**
     * @class Exception
     * @brief Generic exception class.
     */
    class Exception : public BaseException
    {
        public:
            /// Default constructor.
            Exception();

            /// Copy constructor.
            Exception(const Exception& that);

            /** Constructor.
             * @param fmt printf-like format string.
             * @param v va_list.
             */
            Exception(const char *fmt, va_list v);

            //@{
            /** Constructor.
             * @param fmt printf-like format string.
             * @param ... variable args.
             */
            Exception(const char *fmt, ...);
            Exception(const std::string& fmt, ...);
            //@}

            /// Copy assignment operator.
            Exception& operator= (const Exception& that);

            /// Destructor.
            virtual ~Exception() throw();

            /// Get error message.
            virtual const char *what() const throw();

        protected:
            const char *message() const { return _buf; }

        private:
            char *_buf;
            va_list _v;
    };

    /**
     * @class ErrnoException
     * @brief Exception class for errors where errno is set.
     */
    class ErrnoException : public Exception
    {
        public:
            /// Default constructor.
            ErrnoException();

            //@{
            /** Constructor.
             * @param msg Error message prefix.
             */
            ErrnoException(const char *msg);
            ErrnoException(const std::string& msg);
            //@}

            /// Destructor.
            virtual ~ErrnoException() throw() { }

            /// Get error message prefix + strerror(errno).
            virtual const char *what() const throw();

            /// Get error code (errno) for this error.
            int code() const { return _code; }

        private:
            int _code;
    };
    
    /**
     * @class FileException
     * @brief Exception for file-related errors.
     */
    class FileException : public ErrnoException
    {
        public:
            /// Default constructor.
            FileException();

            //@{
            /** Constructor.
             * @param msg Error message prefix.
             */
            FileException(const char *msg);
            FileException(const std::string& msg);
            //@}
            
            /// Destructor.
            virtual ~FileException() throw() { }
    };

    /**
     * @class BadCast
     * @brief Exception for bad type casts.
     */
    class BadCast : public Exception
    {
        public:
            /// Default constructor.
            BadCast();

            //@{
            /** Constructor.
             * @param msg Error message.
             */
            BadCast(const char *msg);
            BadCast(const std::string& msg);
            //@}

            /// Destructor.
            virtual ~BadCast() throw() { }
    };

    /**
     * @class BadRegex
     * @brief Exception for regular expression errors.
     */
    class BadRegex : public Exception
    {
        public:
            /// Default constructor.
            BadRegex();

            /** Constructor.
             * @param e error code.
             * @param re regex_t associated with this error.
             */
            BadRegex(int e, const regex_t *re);

            /** Constructor.
             * @param s Error message.
             */
            BadRegex(const std::string& s);

            /// Destructor.
            virtual ~BadRegex() throw() { }

            /// Get error message.
            virtual const char *what() const throw();

        private:
            int _err;
            const regex_t *_re;
    };

    /**
     * @class BadDate
     * @brief Exception for invalid dates.
     */
    class BadDate : public Exception
    {
        public:
            /// Default constructor.
            BadDate();

            //@{
            /** Constructor.
             * @param msg Error message.
             */
            BadDate(const char *msg);
            BadDate(const std::string& msg);
            //@}

            /// Destructor.
            virtual ~BadDate() throw() { }
    };

    /**
     * @class FetchException
     * @brief Exception for fetching errors.
     */
    class FetchException : public Exception
    {
        public:
            /// Default constructor.
            FetchException();

            //@{
            /** Constructor.
             * @param msg Error message.
             */
            FetchException(const char *msg);
            FetchException(const std::string& msg);
            //@}
            
            /// Destructor.
            virtual ~FetchException() throw() { }
    };

    /**
     * @class MalformedEmail
     * @brief Exception for malformed email addresses.
     */
    class MalformedEmail : public Exception
    {
        public:
            /// Default constructor.
            MalformedEmail();

            //@{
            /** Constructor.
             * @param msg Error message.
             */
            MalformedEmail(const char *msg);
            MalformedEmail(const std::string& msg);
            //@}

            /// Destructor.
            virtual ~MalformedEmail() throw() { }
    };

} // namespace herdstat

#endif /* _HAVE_HERDSTAT_EXCEPTIONS_HH */

/* vim: set tw=80 sw=4 et : */
