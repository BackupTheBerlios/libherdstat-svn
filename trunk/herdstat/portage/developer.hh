/*
 * libherdstat -- herdstat/portage/developer.hh
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

#ifndef _HAVE_DEVELOPER_HH
#define _HAVE_DEVELOPER_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/developer.hh
 * @brief Defines the Developer/Developers classes.
 */

#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include <herdstat/util/string.hh>
#include <herdstat/util/functional.hh>
#include <herdstat/portage/gentoo_email_address.hh>

namespace herdstat {
namespace portage {

    /**
     * @class Developer developer.hh herdstat/portage/developer.hh
     * @brief Represents a Gentoo developer.
     */

    class Developer
    {
        public:
            /// Default constructor.
            Developer() throw();

            /// Copy constructor.
            Developer(const Developer& that) throw();

            /** Constructor.
             * @param user user name.
             * @param email email address (defaults to empty).
             * @param name  real name (defaults to empty).
             */
            Developer(const std::string &user,
                      const std::string &email = "",
                      const std::string &name = "") throw();

            /// Destructor.
            ~Developer() throw();

            /// Copy assignment operator.
            Developer& operator=(const Developer& that) throw();

            /** Implicit conversion to std::string.
             * @returns Developer user name.
             */
            inline operator std::string() const throw();

            /** Determine if this developer is equal to that developer.
             * @param user user name.
             * @returns True if user name is equivelent.
             */
            inline bool operator== (const std::string& user) const throw();

            /** Determine if this developer is equal to that developer.
             * @param dev const reference to Developer object.
             * @returns True if user name is equivelent.
             */
            inline bool operator== (const Developer& dev) const throw();

            /** Determine if this developer is equal to that developer.
             * @param re const reference to a Regex object
             * @returns True if regex matches our user name.
             */
            inline bool operator== (const util::Regex& re) const throw();

            /** Determine if this developer is not equal to that developer.
             * @param user user name.
             * @returns True if user name is not equivelent.
             */
            inline bool operator!= (const std::string& user) const throw();

            /** Determine if this developer is not equal to that developer.
             * @param dev const reference to Developer object.
             * @returns True if user name is not equivelent.
             */
            inline bool operator!= (const Developer& dev) const throw();

            /** Determine if this developer is not equal to that developer.
             * @param re const reference to a Regex object
             * @returns True if regex does not match our user name.
             */
            inline bool operator!= (const util::Regex& re) const throw();

            /** Determine if this developer is greater than that developer.
             * @param user user name.
             * @returns True if our user name is greater than user.
             */
            inline bool operator>  (const std::string& user) const throw();

            /** Determine if this developer is greater than that developer.
             * @param dev const reference to Developer object.
             * @returns True if our user name is greater than their user name.
             */
            inline bool operator>  (const Developer& dev) const throw();

            /** Determine if this developer is greater than or equal to that
             * developer.
             * @param user user name.
             * @returns True if our user name is greater than or equal to user.
             */
            inline bool operator>= (const std::string& user) const throw();

            /** Determine if this developer is greater than or equal to that
             * developer.
             * @param dev const reference to Developer object.
             * @returns True if our user name is greater than or equal to their
             * user name.
             */
            inline bool operator>= (const Developer& dev) const throw();

            /** Determine if this developer is less than that developer.
             * @param user user name.
             * @returns True if our user name is less than user.
             */
            inline bool operator<  (const std::string& user) const throw();

            /** Determine if this developer is less than that developer.
             * @param dev const reference to Developer object.
             * @returns True if our user name is less than their user name.
             */
            inline bool operator<  (const Developer& dev) const throw();

            /** Determine if this developer is less than or equal to that
             * developer.
             * @param user user name.
             * @returns True if our user name is less than or equal to user.
             */
            inline bool operator<= (const std::string& user) const throw();

            /** Determine if this developer is less than or equal to that
             * developer.
             * @param dev const reference to Developer object.
             * @returns True if our user name is less than or equal to their
             * user name.
             */
            inline bool operator<= (const Developer& dev) const throw();

            /// Get user name.
            inline const std::string& user() const throw();
            /// Get email address.
            inline const std::string& email() const throw();
            /// Get full name.
            inline const std::string& name() const throw();
            /// Get PGP Key Id.
            inline const std::string& pgpkey() const throw();
            /// Get joined date.
            inline const std::string& joined() const throw();
            /// Get birth date.
            inline const std::string& birthday() const throw();
            /// Get status.
            inline const std::string& status() const throw();
            /// Get roles.
            inline const std::string& role() const throw();
            /// Get location.
            inline const std::string& location() const throw();
            /// Get away message.
            inline const std::string& awaymsg() const throw();
            /// Get herds.
            inline const std::vector<std::string>& herds() const throw();
            /// Is this developer away?
            inline bool is_away() const throw();

            /// Set user name.
            inline void set_user(const std::string& user) throw();
            /// Set email address.
            inline void set_email(const std::string& email) throw();
            /// Set full name.
            inline void set_name(const std::string& name) throw();
            /// Set PGP key ID.
            inline void set_pgpkey(const std::string& pgpkey) throw();
            /// Set joined date.
            inline void set_joined(const std::string& date) throw();
            /// Set birth date.
            inline void set_birthday(const std::string& date) throw();
            /// Set status.
            inline void set_status(const std::string& status) throw();
            /// Set roles.
            inline void set_role(const std::string& role) throw();
            /// Set location.
            inline void set_location(const std::string& location) throw();
            /// Set away message.
            inline void set_awaymsg(const std::string& msg) throw();
            /// Set herds vector.
            inline void set_herds(const std::vector<std::string>& herds) throw();
            /// Append to herds vector.
            inline void append_herd(const std::string& herd) throw();
            /// Set as away.
            inline void set_away(const bool away) throw();

        private:
            std::string _user;
            GentooEmailAddress _email;
            std::string _name;
            std::string _pgpkey;
            std::string _joined;
            std::string _birth;
            std::string _status;
            std::string _role;
            std::string _location;
            std::string _awaymsg;
            bool _away;
            mutable std::vector<std::string> *_herds;
    };

    inline Developer::operator std::string() const throw() { return _user; }
    inline bool Developer::operator== (const std::string& user) const throw()
    { return (_user == user); }
    inline bool Developer::operator== (const Developer& that) const throw()
    { return (_user == that._user); }
    inline bool Developer::operator== (const util::Regex& re) const throw()
    { return (_user == re); }
    inline bool Developer::operator!= (const std::string& user) const throw()
    { return not (*this == user); }
    inline bool Developer::operator!= (const Developer& that) const throw()
    { return not (*this == that); }
    inline bool Developer::operator!= (const util::Regex& re) const throw()
    { return (_user != re); }
    inline bool Developer::operator<  (const std::string& user) const throw()
    { return (_user < user); }
    inline bool Developer::operator<  (const Developer& dev) const throw()
    { return (_user < dev._user); }
    inline bool Developer::operator<= (const std::string& user) const throw()
    { return (_user <= user); }
    inline bool Developer::operator<= (const Developer& dev) const throw()
    { return (_user <= dev._user); }
    inline bool Developer::operator>  (const std::string& user) const throw()
    { return (_user > user); }
    inline bool Developer::operator>  (const Developer& dev) const throw()
    { return (_user > dev._user); }
    inline bool Developer::operator>= (const std::string& user) const throw()
    { return (_user >= user); }
    inline bool Developer::operator>= (const Developer& dev) const throw()
    { return (_user >= dev._user); }

    inline const std::string& Developer::user() const throw() { return _user; }
    inline const std::string& Developer::email() const throw() { return _email.str(); }
    inline const std::string& Developer::name() const throw() { return _name; }
    inline const std::string& Developer::pgpkey() const throw() { return _pgpkey; }
    inline const std::string& Developer::joined() const throw() { return _joined; }
    inline const std::string& Developer::birthday() const throw() { return _birth; }
    inline const std::string& Developer::status() const throw() { return _status; }
    inline const std::string& Developer::role() const throw() { return _role; }
    inline const std::string& Developer::location() const throw() { return _location; }
    inline const std::string& Developer::awaymsg() const throw() { return _awaymsg; }
    inline bool Developer::is_away() const throw() { return _away; }
    inline const std::vector<std::string>& Developer::herds() const throw()
    {
        if (not _herds) _herds = new std::vector<std::string>();
        return *_herds;
    }

    inline void Developer::set_user(const std::string& user) throw()
    { _user.assign(user); }
    inline void Developer::set_email(const std::string& email) throw()
    { _email.assign(email); }
    inline void Developer::set_name(const std::string& name) throw()
    { _name.assign(name); }
    inline void Developer::set_pgpkey(const std::string& pgpkey) throw()
    { _pgpkey.assign(pgpkey); }
    inline void Developer::set_joined(const std::string& date) throw()
    { _joined.assign(date); }
    inline void Developer::set_birthday(const std::string& date) throw()
    { _birth.assign(date); }
    inline void Developer::set_status(const std::string& status) throw()
    { _status.assign(status); }
    inline void Developer::set_role(const std::string& role) throw()
    { _role.assign(role); }
    inline void Developer::set_location(const std::string& location) throw()
    { _location.assign(location); }
    inline void Developer::set_awaymsg(const std::string& msg) throw()
    { _awaymsg.assign(msg); }
    inline void Developer::set_herds(const std::vector<std::string>& herds) throw()
    {
        if (not _herds) _herds = new std::vector<std::string>(herds);
        else           *_herds = herds;
    }
    inline void Developer::append_herd(const std::string& herd) throw()
    {
        if (not _herds) _herds = new std::vector<std::string>(1, herd);
        else            _herds->push_back(herd);
    }
    inline void Developer::set_away(const bool away) throw() { _away = away; }

    /**
     * @class Developers developer.hh herdstat/portage/developer.hh
     * @brief Developer container.
     */

    class Developers : public util::SetBase<Developer>
    {
        public:
            /// Default constructor.
            Developers() throw();

            /** Constructor. Assign a container_type.
             * @param v A reference to a container_type.
             */
            Developers(const container_type& v) throw();

            /** Instantiate a Developer for each developer nick in the given
             * vector.
             * @param v vector of developer nicks.
             */
            Developers(const std::vector<std::string>& v) throw();

            /// Destructor.
            virtual ~Developers() throw();

            /// Implicit conversion to std::vector<std::string>.
            operator std::vector<std::string>() const throw();

            /** Assign a new container_type.
             * @param v Reference to container_type.
             * @returns Reference to this.
             */
            Developers& operator= (const container_type& v) throw();

            /** Instantiate a Developer object for each developer
             * user name in the given vector.
             * @param v vector of developer usernames.
             * @returns Reference to this.
             */
            Developers& operator= (const std::vector<std::string>& v) throw();

            inline value_type& front() throw();
            inline const value_type& front() const throw();
            inline value_type& back() throw();
            inline const value_type& back() const throw();

            /** Find developer with the given user name.
             * @param dev user name string.
             * @returns iterator to the first matching or end() if no match.
             */
            inline iterator find(const std::string& dev) throw();
            inline const_iterator find(const std::string& dev) const throw();

            /** Find developer whose user name matches the given Regex.
             * @param regex const reference to Regex.
             * @returns iterator to the first matching or end() if no match.
             */
            inline iterator find(const util::Regex &regex) throw();
            inline const_iterator find(const util::Regex& regex) const throw();
    };

    inline Developers::iterator Developers::find(const std::string& dev) throw()
    { return util::SetBase<Developer>::find(Developer(dev)); }

    inline Developers::const_iterator
    Developers::find(const std::string& dev) const throw()
    { return util::SetBase<Developer>::find(Developer(dev)); }

    inline Developers::iterator
    Developers::find(const util::Regex& regex) throw()
    {
        return std::find_if(this->begin(), this->end(),
                util::compose_f_gx(
                    std::bind1st(util::regexMatch(), regex),
                    std::mem_fun_ref(&Developer::user)));
    }

    inline Developers::const_iterator
    Developers::find(const util::Regex& regex) const throw()
    {
        return std::find_if(this->begin(), this->end(),
                util::compose_f_gx(
                    std::bind1st(util::regexMatch(), regex),
                    std::mem_fun_ref(&Developer::user)));
    }

    inline Developers::value_type&
    Developers::front() throw()
    {
        assert(not this->empty());
        return const_cast<value_type&>(*this->begin());
    }
    
    inline const Developers::value_type&
    Developers::front() const throw()
    {
        assert(not this->empty());
        return *(this->begin());
    }

    inline Developers::value_type&
    Developers::back() throw()
    {
        assert(not this->empty());
        iterator i(this->end());
        return const_cast<value_type&>(*(--i));
    }
    
    inline const Developers::value_type&
    Developers::back() const throw()
    {
        assert(not this->empty());
        iterator i(this->end());
        return *(--i);
    }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_DEVELOPER_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
