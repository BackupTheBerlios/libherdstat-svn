/*
 * herdstat -- portage/developer.hh
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

#include <herdstat/portage/functional.hh>
#include <herdstat/portage/gentoo_email_address.hh>

namespace herdstat {
namespace portage {

    /**
     * Represents a Gentoo developer.
     */

    class Developer
    {
        public:
            /// Default constructor.
            Developer();

            /** Constructor.
             * @param user user name.
             * @param email email address (defaults to empty).
             * @param name  real name (defaults to empty).
             */
            Developer(const std::string &user,
                      const std::string &email = "",
                      const std::string &name = "");

            ~Developer();

            /** Implicit conversion to std::string.
             * @returns Developer user name.
             */
            inline operator std::string() const;

            /** Determine if this developer is equal to that developer.
             * @param user user name.
             * @returns True if user name is equivelent.
             */
            inline bool operator== (const std::string& user) const;

            /** Determine if this developer is equal to that developer.
             * @param dev const reference to Developer object.
             * @returns True if user name is equivelent.
             */
            inline bool operator== (const Developer& dev) const;

            /** Determine if this developer is equal to that developer.
             * @param re const reference to a Regex object
             * @returns True if regex matches our user name.
             */
            inline bool operator== (const util::Regex& re) const;

            /** Determine if this developer is not equal to that developer.
             * @param user user name.
             * @returns True if user name is not equivelent.
             */
            inline bool operator!= (const std::string& user) const;

            /** Determine if this developer is not equal to that developer.
             * @param dev const reference to Developer object.
             * @returns True if user name is not equivelent.
             */
            inline bool operator!= (const Developer& dev) const;

            /** Determine if this developer is not equal to that developer.
             * @param re const reference to a Regex object
             * @returns True if regex does not match our user name.
             */
            inline bool operator!= (const util::Regex& re) const;

            /** Determine if this developer is greater than that developer.
             * @param user user name.
             * @returns True if our user name is greater than user.
             */
            inline bool operator>  (const std::string& user) const;

            /** Determine if this developer is greater than that developer.
             * @param dev const reference to Developer object.
             * @returns True if our user name is greater than their user name.
             */
            inline bool operator>  (const Developer& dev) const;

            /** Determine if this developer is greater than or equal to that
             * developer.
             * @param user user name.
             * @returns True if our user name is greater than or equal to user.
             */
            inline bool operator>= (const std::string& user) const;

            /** Determine if this developer is greater than or equal to that
             * developer.
             * @param dev const reference to Developer object.
             * @returns True if our user name is greater than or equal to their
             * user name.
             */
            inline bool operator>= (const Developer& dev) const;

            /** Determine if this developer is less than that developer.
             * @param user user name.
             * @returns True if our user name is less than user.
             */
            inline bool operator<  (const std::string& user) const;

            /** Determine if this developer is less than that developer.
             * @param dev const reference to Developer object.
             * @returns True if our user name is less than their user name.
             */
            inline bool operator<  (const Developer& dev) const;

            /** Determine if this developer is less than or equal to that
             * developer.
             * @param user user name.
             * @returns True if our user name is less than or equal to user.
             */
            inline bool operator<= (const std::string& user) const;

            /** Determine if this developer is less than or equal to that
             * developer.
             * @param dev const reference to Developer object.
             * @returns True if our user name is less than or equal to their
             * user name.
             */
            inline bool operator<= (const Developer& dev) const;

            /// Get user name.
            inline const std::string& user() const;
            /// Get email address.
            inline const std::string& email() const;
            /// Get full name.
            inline const std::string& name() const;
            /// Get PGP Key Id.
            inline const std::string& pgpkey() const;
            /// Get joined date.
            inline const std::string& joined() const;
            /// Get birth date.
            inline const std::string& birthday() const;
            /// Get status.
            inline const std::string& status() const;
            /// Get roles.
            inline const std::string& role() const;
            /// Get location.
            inline const std::string& location() const;
            /// Get away message.
            inline const std::string& awaymsg() const;
            /// Get herds.
            inline const std::vector<std::string>& herds() const;
            /// Is this developer away?
            inline bool is_away() const;

            /// Set user name.
            inline void set_user(const std::string& user);
            /// Set email address.
            inline void set_email(const std::string& email);
            /// Set full name.
            inline void set_name(const std::string& name);
            /// Set PGP key ID.
            inline void set_pgpkey(const std::string& pgpkey);
            /// Set joined date.
            inline void set_joined(const std::string& date);
            /// Set birth date.
            inline void set_birthday(const std::string& date);
            /// Set status.
            inline void set_status(const std::string& status);
            /// Set roles.
            inline void set_role(const std::string& role);
            /// Set location.
            inline void set_location(const std::string& location);
            /// Set away message.
            inline void set_awaymsg(const std::string& msg);
            /// Set herds vector.
            inline void set_herds(const std::vector<std::string>& herds);
            /// Append to herds vector.
            inline void append_herd(const std::string& herd);
            /// Set as away.
            inline void set_away(const bool away);

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
            std::vector<std::string> _herds;
    };

    inline Developer::operator std::string() const { return _user; }
    inline bool Developer::operator== (const std::string& user) const
    { return (_user == user); }
    inline bool Developer::operator== (const Developer& that) const
    { return (_user == that._user); }
    inline bool Developer::operator== (const util::Regex& re) const
    { return (re == _user); }
    inline bool Developer::operator!= (const std::string& user) const
    { return not (*this == user); }
    inline bool Developer::operator!= (const Developer& that) const
    { return not (*this == that); }
    inline bool Developer::operator!= (const util::Regex& re) const
    { return (re != _user); }
    inline bool Developer::operator<  (const std::string& user) const
    { return (_user < user); }
    inline bool Developer::operator<  (const Developer& dev) const
    { return (_user < dev._user); }
    inline bool Developer::operator<= (const std::string& user) const
    { return (_user <= user); }
    inline bool Developer::operator<= (const Developer& dev) const
    { return (_user <= dev._user); }
    inline bool Developer::operator>  (const std::string& user) const
    { return (_user > user); }
    inline bool Developer::operator>  (const Developer& dev) const
    { return (_user > dev._user); }
    inline bool Developer::operator>= (const std::string& user) const
    { return (_user >= user); }
    inline bool Developer::operator>= (const Developer& dev) const
    { return (_user >= dev._user); }

    inline const std::string& Developer::user() const { return _user; }
    inline const std::string& Developer::email() const { return _email.str(); }
    inline const std::string& Developer::name() const { return _name; }
    inline const std::string& Developer::pgpkey() const { return _pgpkey; }
    inline const std::string& Developer::joined() const { return _joined; }
    inline const std::string& Developer::birthday() const { return _birth; }
    inline const std::string& Developer::status() const { return _status; }
    inline const std::string& Developer::role() const { return _role; }
    inline const std::string& Developer::location() const { return _location; }
    inline const std::string& Developer::awaymsg() const { return _awaymsg; }
    inline bool Developer::is_away() const { return _away; }
    inline const std::vector<std::string>& Developer::herds() const
    { return _herds; }

    inline void Developer::set_user(const std::string& user)
    { _user.assign(user); }
    inline void Developer::set_email(const std::string& email)
    { _email.assign(email); }
    inline void Developer::set_name(const std::string& name)
    { _name.assign(name); }
    inline void Developer::set_pgpkey(const std::string& pgpkey)
    { _pgpkey.assign(pgpkey); }
    inline void Developer::set_joined(const std::string& date)
    { _joined.assign(date); }
    inline void Developer::set_birthday(const std::string& date)
    { _birth.assign(date); }
    inline void Developer::set_status(const std::string& status)
    { _status.assign(status); }
    inline void Developer::set_role(const std::string& role)
    { _role.assign(role); }
    inline void Developer::set_location(const std::string& location)
    { _location.assign(location); }
    inline void Developer::set_awaymsg(const std::string& msg)
    { _awaymsg.assign(msg); }
    inline void Developer::set_herds(const std::vector<std::string>& herds)
    { _herds = herds; }
    inline void Developer::append_herd(const std::string& herd)
    { _herds.push_back(herd); }
    inline void Developer::set_away(const bool away) { _away = away; }

    /**
     * Developer container.
     */

    class Developers
    {
        public:
            typedef std::set<Developer> container_type;
            typedef container_type::iterator iterator;
            typedef container_type::const_iterator const_iterator;
            typedef container_type::reverse_iterator reverse_iterator;
            typedef container_type::const_reverse_iterator const_reverse_iterator;
            typedef container_type::value_type value_type;
            typedef container_type::size_type size_type;
            typedef container_type::reference reference;
            typedef container_type::const_reference const_reference;

            /// Default constructor.
            Developers();

            /** Constructor. Assign a container_type.
             * @param v A reference to a container_type.
             */
            Developers(const container_type& v);

            /** Instantiate a Developer for each developer nick in the given
             * vector.
             * @param v vector of developer nicks.
             */
            Developers(const std::vector<std::string>& v);

            /// Destructor.
            virtual ~Developers();

            /// Implicit conversion to std::vector<std::string>.
            operator std::vector<std::string>() const;

            /** Assign a new container_type.
             * @param v Reference to container_type.
             * @returns Reference to this.
             */
            Developers& operator= (const container_type& v);

            /** Instantiate a Developer object for each developer
             * user name in the given vector.
             * @param v vector of developer usernames.
             * @returns Reference to this.
             */
            Developers& operator= (const std::vector<std::string>& v);

            inline iterator begin();
            inline const_iterator begin() const;
            inline iterator end();
            inline const_iterator end() const;
            inline reverse_iterator rbegin();
            inline const_reverse_iterator rbegin() const;
            inline reverse_iterator rend();
            inline const_reverse_iterator rend() const;

            inline value_type& front();
            inline const value_type& front() const;
            inline value_type& back();
            inline const value_type& back() const;

            inline iterator find(const std::string& dev) const;
            inline iterator find(const value_type& dev) const;
            inline iterator find(const util::Regex &regex) const;

            inline size_type size() const;
            inline bool empty() const;
            inline void clear();

            inline iterator insert(iterator pos, const value_type& dev);

            template <class In>
            inline void insert(In begin, In end);

            inline std::pair<iterator, bool> insert(const value_type& v);

            inline void erase(iterator pos);
            inline size_type erase(const value_type& v);
            inline void erase(iterator begin, iterator end);

        private:
            container_type _devs;
    };

    inline Developers::iterator Developers::begin() { return _devs.begin(); }
    inline Developers::const_iterator Developers::begin() const { return _devs.begin(); }
    inline Developers::iterator Developers::end() { return _devs.end(); }
    inline Developers::const_iterator Developers::end() const { return _devs.end(); }
    inline Developers::reverse_iterator Developers::rbegin() { return _devs.rbegin(); }
    inline Developers::const_reverse_iterator Developers::rbegin() const
    { return _devs.rbegin(); }
    inline Developers::reverse_iterator Developers::rend() { return _devs.rend(); }
    inline Developers::const_reverse_iterator Developers::rend() const
    { return _devs.rend(); }
    
    inline Developers::size_type Developers::size() const { return _devs.size(); }
    inline bool Developers::empty() const { return _devs.empty(); }
    inline void Developers::clear() { return _devs.clear(); }

    inline void Developers::erase(iterator pos) { _devs.erase(pos); }
    inline Developers::size_type Developers::erase(const value_type& v)
    { return _devs.erase(v); }
    inline void Developers::erase(iterator begin, iterator end)
    { return _devs.erase(begin, end); }
    inline Developers::iterator Developers::insert(iterator pos, const value_type& dev)
    { return _devs.insert(pos, dev); }
    template <class In> inline void
    Developers::insert(In begin, In end) { _devs.insert(begin, end); }

    inline std::pair<Developers::iterator, bool>
    Developers::insert(const value_type& v) { return _devs.insert(v); }

    inline Developers::iterator Developers::find(const value_type& dev) const
    { return _devs.find(dev); }

    inline Developers::iterator Developers::find(const std::string& dev) const
    { return _devs.find(Developer(dev)); }

    inline Developers::iterator Developers::find(const util::Regex& regex) const
    {
        return std::find_if(_devs.begin(), _devs.end(), std::bind1st(
            UserRegexMatch<Developer>(), regex));
    }

    inline Developers::value_type&
    Developers::front()
    {
        assert(not _devs.empty());
        return const_cast<value_type&>(*_devs.begin());
    }
    
    inline const Developers::value_type&
    Developers::front() const
    {
        assert(not _devs.empty());
        return *(_devs.begin());
    }

    inline Developers::value_type&
    Developers::back()
    {
        assert(not _devs.empty());
        iterator i(_devs.end());
        return const_cast<value_type&>(*(--i));
    }
    
    inline const Developers::value_type&
    Developers::back() const
    {
        assert(not _devs.empty());
        iterator i(_devs.end());
        return *(--i);
    }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_DEVELOPER_HH */

/* vim: set tw=80 sw=4 et : */
