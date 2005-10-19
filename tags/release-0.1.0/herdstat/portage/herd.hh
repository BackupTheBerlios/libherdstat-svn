/*
 * libherdstat -- herdstat/portage/herd.hh
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

#ifndef _HAVE_HERD_HH
#define _HAVE_HERD_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/herd.hh
 * @brief Defines the Herd/Herds classes.
 */

#include <herdstat/portage/developer.hh>

namespace herdstat {
namespace portage {

    /**
     * @class Herd
     * @brief Represents a herd.
     * Techically a herd is a group of packages, however here it makes more
     * sense to represent them as a group of developers.
     */

    class Herd : public Developers
    {
        public:
            /// Default constructor.
            Herd();

            /** Constructor.
             * @param name Herd name.
             * @param email Herd email address.
             * @param desc Herd description.
             */
            Herd(const std::string &name,
                 const std::string &email = "",
                 const std::string &desc  = "");

            /** Constructor.  Assign a container_type.
             * @param v Reference to a container_type.
             */
            Herd(const container_type& v);

            /** Constructor.  Instantiate a new Developer object
             * for each developer user name in the given vector.
             * @param v Reference to a vector of developer usernames.
             */
            Herd(const std::vector<std::string>& v);

            /// Destructor.
            virtual ~Herd();

            /** Copy assignment operator.
             * @param that Reference to another Herd object.
             */
            Herd& operator= (const Herd& that);

            /// Implicit conversion to std::string.
            inline operator std::string() const;

            //@{
            /** Determine equivelance of this herd compared to that herd name.
             * @param name herd name.
             * @returns Boolean value.
             */
            inline bool operator== (const std::string& name) const;
            inline bool operator!= (const std::string& name) const;
            inline bool operator<  (const std::string& name) const;
            inline bool operator>  (const std::string& name) const;
            inline bool operator<= (const std::string& name) const;
            inline bool operator>= (const std::string& name) const;
            //@}

            //@{
            /** Determine equivelance of this herd compared to that herd.
             * @param herd const reference to another Herd object.
             * @returns Boolean value.
             */
            inline bool operator== (const Herd& herd) const;
            inline bool operator!= (const Herd& herd) const;
            inline bool operator<  (const Herd& herd) const;
            inline bool operator>  (const Herd& herd) const;
            inline bool operator<= (const Herd& herd) const;
            inline bool operator>= (const Herd& herd) const;
            //@}

            //@{
            /** Determine equivelance of this herd compared to the regex.
             * @param re const reference to a Regex object.
             * @returns Boolean value.
             */
            inline bool operator== (const util::Regex& re) const;
            inline bool operator!= (const util::Regex& re) const;
            //@}

            /// Get herd name.
            inline const std::string& name() const;
            /// Get herd email address.
            inline const std::string& email() const;
            /// Get herd description.
            inline const std::string& desc() const;
            /// Set herd name.
            inline void set_name(const std::string &name);
            /// Set herd email address.
            inline void set_email(const std::string &email);
            /// Set herd description.
            inline void set_desc(const std::string &desc);

        private:
            std::string _name;
            GentooEmailAddress _email;
            std::string _desc;
    };

    inline Herd::operator std::string() const { return _name; }
    inline bool Herd::operator== (const std::string& name) const
    { return (_name == name); }
    inline bool Herd::operator== (const Herd& herd) const
    { return (_name == herd._name); }
    inline bool Herd::operator== (const util::Regex& re) const
    { return (re == _name); }
    inline bool Herd::operator!= (const std::string& name) const
    { return (_name != name); }
    inline bool Herd::operator!= (const Herd& herd) const
    { return (_name != herd._name); }
    inline bool Herd::operator!= (const util::Regex& re) const
    { return (re != _name); }
    inline bool Herd::operator< (const std::string& name) const
    { return (_name < name); }
    inline bool Herd::operator< (const Herd& herd) const
    { return (_name < herd._name); }
    inline bool Herd::operator> (const std::string& name) const
    { return (_name > name); }
    inline bool Herd::operator> (const Herd& herd) const
    { return (_name > herd._name); }
    inline bool Herd::operator<= (const std::string& name) const
    { return (_name <= name); }
    inline bool Herd::operator<= (const Herd& herd) const
    { return (_name <= herd._name); }
    inline bool Herd::operator>= (const std::string& name) const
    { return (_name >= name); }
    inline bool Herd::operator>= (const Herd& herd) const
    { return (_name >= herd._name); }
    inline const std::string& Herd::name() const { return _name; }
    inline const std::string& Herd::email() const { return _email.str(); }
    inline const std::string& Herd::desc() const { return _desc; }
    inline void Herd::set_name(const std::string& name) { _name.assign(name); }
    inline void Herd::set_email(const std::string& email) { _email.assign(email); }
    inline void Herd::set_desc(const std::string& desc) { _desc.assign(desc); }

    /**
     * @class Herds
     * @brief Herd container.
     */

    class Herds : public util::SetBase<Herd>
    {
        public:
            /// Default constructor.
            Herds();

            /** Constructor.  Initialize this herd with a container_type.
             * @param v Reference to a container_type.
             */
            Herds(const container_type& v);

            /// Destructor.
            ~Herds();

            /// Implicit conversion to container_type.
            inline operator container_type() const;
            /// Implicit conversion to std::vector<std::string>.
            operator std::vector<std::string>() const;

            /** Assign a new container_type.
             * @param v Reference to a container_type object.
             * @returns Reference to this.
             */
            Herds& operator= (const container_type& v);

            /** Instantiate a Herd for each string in the given vector and
             * insert it into our container.
             * @param v Reference to a std::vector<std::string> of herd names.
             * @returns Reference to this.
             */
            Herds& operator= (const std::vector<std::string>& v);

            inline value_type& front();
            inline const value_type& front() const;
            inline value_type& back();
            inline const value_type& back() const;

            /** Find herd with given herd name.
             * @param herd Herd name.
             * @returns iterator to first match or end() if no match.
             */
            inline iterator find(const std::string& herd);
            inline const_iterator find(const std::string& herd) const;

            /** Find herd with name matching given regular expression.
             * @param regex Regular expression.
             * @returns iterator to first match or end() if no match.
             */
            inline iterator find(const util::Regex& regex);
            inline const_iterator find(const util::Regex& regex) const;
    };

    inline Herds::operator
    Herds::container_type() const
    {
        return this->container();
    }

    inline Herds::iterator
    Herds::find(const std::string& h)
    {
        return util::SetBase<Herd>::find(Herd(h));
    }

    inline Herds::const_iterator
    Herds::find(const std::string& h) const
    {
        return util::SetBase<Herd>::find(Herd(h));
    }
    
    inline Herds::iterator
    Herds::find(const util::Regex& regex)
    {
        return std::find_if(this->begin(), this->end(), std::bind1st(
                    NameRegexMatch<Herd>(), regex));
    }

    inline Herds::const_iterator
    Herds::find(const util::Regex& regex) const
    {
        return std::find_if(this->begin(), this->end(), std::bind1st(
                    NameRegexMatch<Herd>(), regex));
    }

    inline Herds::value_type&
    Herds::front()
    {
        assert(not this->empty());
        return const_cast<value_type&>(*this->begin());
    }
    
    inline const Herds::value_type&
    Herds::front() const
    {
        assert(not this->empty());
        return *(this->begin());
    }

    inline Herds::value_type&
    Herds::back()
    {
        assert(not this->empty());
        iterator i(this->end());
        return const_cast<value_type&>(*(--i));
    }
    
    inline const Herds::value_type&
    Herds::back() const
    {
        assert(not this->empty());
        iterator i(this->end());
        return *(--i);
    }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_HERD_H */

/* vim: set tw=80 sw=4 et : */
