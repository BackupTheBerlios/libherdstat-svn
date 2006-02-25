/*
 * libherdstat -- herdstat/email_address.hh
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

#ifndef _HAVE_EMAIL_ADDRESS_HH
#define _HAVE_EMAIL_ADDRESS_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/email_address.hh
 * @brief Defines the EmailAddress class.
 */

#include <string>

namespace herdstat {

    /**
     * @class EmailAddress email_address.hh herdstat/email_address.hh
     * @brief Represents an email address string.
     */

    class EmailAddress
    {
        public:
            /// Default constructor.
            EmailAddress();

            /** Constructor.
             * @param email email address string.
             * @exception MalformedEmail
             */
            EmailAddress(const std::string& email);

            /** Constructor.
             * @param user user name string.
             * @param domain domain name string.
             * @exception MalformedEmail
             */
            EmailAddress(const std::string& user,
                         const std::string& domain);

            /// Destructor.
            virtual ~EmailAddress() throw();

            /// Implicit conversion to std::string.
            inline operator const std::string&() const;

            /** Assignment operator.
             * @param email email address string.
             * @exception MalformedEmail
             * @returns Reference to this.
             */
            inline EmailAddress&
            operator= (const std::string& email);

            /// Clear email address.
            inline void clear();

            /** Assign new email address string.
             * @param email email address string.
             * @exception MalformedEmail
             */
            inline void assign(const std::string& email);
            
            /** Assign a new EmailAddress object.
             * @param that const reference to another EmailAddress object.
             * @exception MalformedEmail
             */
            inline void assign(const EmailAddress& that);

            /// Get user name.
            inline const std::string& user() const;
            /// Get domain name.
            inline const std::string& domain() const;
            /// Get full email.
            inline const std::string& str() const;
        
            /// Set user name.
            void set_user(const std::string& user);
            /// Set domain.
            void set_domain(const std::string& domain);

        protected:
            virtual bool parse(const std::string& email);

        private:
            void set_email();
            std::string _email, _user, _domain;
    };

    inline EmailAddress::operator const std::string&() const
    { return _email; }
    inline EmailAddress&
    EmailAddress::operator= (const std::string& email)
    { if (not this->parse(email)) throw MalformedEmail(email); return *this; }
    inline void EmailAddress::assign(const std::string& email)
    { if (not this->parse(email)) throw MalformedEmail(email); }
    inline void EmailAddress::assign(const EmailAddress& that)
    { *this = that; }
    inline const std::string& EmailAddress::user() const { return _user; }
    inline const std::string& EmailAddress::domain() const { return _domain; }
    inline const std::string& EmailAddress::str() const { return _email; }
    inline void EmailAddress::set_email() { _email.assign(_user+"@"+_domain); }
    inline void EmailAddress::set_user(const std::string& user)
    { _user.assign(user); set_email(); }
    inline void EmailAddress::set_domain(const std::string& domain)
    { _domain.assign(domain); set_email(); }
    inline void EmailAddress::clear()
    { _email.clear();_user.clear();_domain.clear(); }

} // namespace herdstat

#endif /* _HAVE_EMAIL_ADDRESS_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
