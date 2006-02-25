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

    // {{{ Herd
    /**
     * @class Herd herd.hh herdstat/portage/herd.hh
     * @brief Represents a herd.
     *
     * @section overview Overview
     *
     * Techically a herd is a group of packages, however here it makes more
     * sense to represent them as a group of Developer objects.  The Herd class
     * derives from the Developers class since it is a Developer container.  The
     * only difference between the two is that a Herd represents a group of
     * related developers.  Unlike Developers, a Herd has a name, a description,
     * and an email address.
     *
     * @see Developers for additional documentation.
     */

    class Herd : public Developers
    {
        public:
            /// Default constructor.
            Herd();

            /** Constructor.
             * @param name %Herd name.
             * @param email %Herd email address.
             * @param desc %Herd description.
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
            virtual ~Herd() throw();

            /** Copy assignment operator.
             * @param that Reference to another Herd object.
             */
            Herd& operator= (const Herd& that);

            /// Implicit conversion to std::string.
            inline operator std::string() const;

            //@{
            /** Determine equivalence of this herd compared to that herd name.
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
            /** Determine equivalence of this herd compared to that herd.
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
            /** Determine equivalence of this herd compared to the regex.
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

    ///@{
    /** Comparison operators for when a Herd object is on the right hand side.
     * @param lhs const reference to a herd name string.
     * @param rhs const reference to a Herd object.
     * @returns A boolean value.
     */
    inline bool
    operator==(const std::string& lhs, const Herd& rhs)
    {
        return (rhs == lhs);
    }

    inline bool
    operator!=(const std::string& lhs, const Herd& rhs)
    {
        return (rhs != lhs);
    }

    inline bool
    operator< (const std::string& lhs, const Herd& rhs)
    {
        return (rhs > lhs);
    }

    inline bool
    operator<=(const std::string& lhs, const Herd& rhs)
    {
        return (rhs >= lhs);
    }

    inline bool
    operator> (const std::string& lhs, const Herd& rhs)
    {
        return (rhs < lhs);
    }

    inline bool
    operator>=(const std::string& lhs, const Herd& rhs)
    {
        return (rhs <= lhs);
    }
    ///@}
    
    ///@{
    /** Comparison operators for when a Herd object is on the right hand side.
     * @param lhs const reference to a util::Regex object.
     * @param rhs const reference to a Herd object.
     * @returns A boolean value.
     */
    inline bool
    operator==(const util::Regex& lhs, const Herd& rhs)
    {
        return (rhs == lhs);
    }

    inline bool
    operator!=(const util::Regex& lhs, const Herd& rhs)
    {
        return (rhs != lhs);
    }
    ///@}
    // }}}

    // {{{ Herds
    /**
     * @class Herds herd.hh herdstat/portage/herd.hh
     * @brief Herd container.
     *
     * @section usage Usage
     *
     * Use the Herds class like you would a std::set<Herd>.
     *
     * @section example Example
     *
     * Below is a simple example of using the Herds class:
     *
@code
herdstat::portage::Herd h1("netmon");
herdstat::portage::Herd h2("cpp");
herdstat::portage::Herds herds;
herds.insert(h1);
herds.insert(h2);
...
std::vector<herdstat::portage::Herd> other_herds;
...
herds.insert(other_herds.begin(), other_herds.end());
...
std::cout << "Herds(" << herds.size() << "):" << std::endl;
std::transform(herds.begin(), herds.end(),
    std::ostream_iterator<std::string>(std::cout, " "),
    std::mem_fun_ref(&herdstat::portage::Herd::name));
@endcode
     *
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
            ~Herds() throw();

            /// Implicit conversion to underlying container (std::set<Herd>).
            inline operator const container_type&() const;
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

            ///@{
            /** Get "least" element (as determined by std::less<Herd>).
             * @returns reference to "least" element.
             * @exception Exception.
             */
            inline value_type& front();
            inline const value_type& front() const;
            ///@}
            
            ///@{
            /** Get "greatest" element (as determined by std::less<Herd>).
             * @returns reference to "greatest" element.
             * @exception Exception.
             */
            inline value_type& back();
            inline const value_type& back() const;
            ///@}

            ///@{
            /** Find herd with given herd name.
             * @param herd Herd name.
             * @returns iterator to first match or end() if no match.
             */
            inline iterator find(const std::string& herd);
            inline const_iterator find(const std::string& herd) const;
            ///@}

            ///@{
            /** Find herd with name matching given regular expression.
             * @param regex Regular expression.
             * @returns iterator to first match or end() if no match.
             */
            inline iterator find(const util::Regex& regex);
            inline const_iterator find(const util::Regex& regex) const;
            ///@}
    };

    inline Herds::operator
    const Herds::container_type&() const
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
        return std::find_if(this->begin(), this->end(),
                util::compose_f_gx(
                    std::bind1st(util::regexMatch(), regex),
                    std::mem_fun_ref(&Herd::name)));
    }

    inline Herds::const_iterator
    Herds::find(const util::Regex& regex) const
    {
        return std::find_if(this->begin(), this->end(),
                util::compose_f_gx(
                    std::bind1st(util::regexMatch(), regex),
                    std::mem_fun_ref(&Herd::name)));
    }

    inline Herds::value_type&
    Herds::front()
    {
        if (this->empty())
            throw Exception("Herds::front() called on an empty Herds instance.");

        return const_cast<value_type&>(*this->begin());
    }
    
    inline const Herds::value_type&
    Herds::front() const
    {
        if (this->empty())
            throw Exception("Herds::front() called on an empty Herds instance.");

        return *(this->begin());
    }

    inline Herds::value_type&
    Herds::back()
    {
        if (this->empty())
            throw Exception("Herds::back() called on an empty Herds instance.");

        iterator i(this->end());
        return const_cast<value_type&>(*(--i));
    }
    
    inline const Herds::value_type&
    Herds::back() const
    {
        if (this->empty())
            throw Exception("Herds::back() called on an empty Herds instance.");

        iterator i(this->end());
        return *(--i);
    }
    // }}}

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_HERD_H */

/* vim: set tw=80 sw=4 fdm=marker et : */
