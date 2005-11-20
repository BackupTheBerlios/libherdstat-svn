/*
 * libherdstat -- util/container_base.hh
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

#ifndef _HAVE_CONTAINER_BASE_HH
#define _HAVE_CONTAINER_BASE_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <vector>
#include <map>
#include <set>
#include <functional>

/**
 * @file container_base.hh
 * @brief Defines the ContainerBase base class template.
 */

namespace herdstat {
namespace util {

    /**
     * @class ContainerBase container_base.hh herdstat/util/container_base.hh
     * @brief Base for classes who should act like standard containers.
     */

    template <typename C>
    class ContainerBase
    {
        public:
            typedef C container_type;
            typedef typename container_type::iterator iterator;
            typedef typename container_type::const_iterator const_iterator;
            typedef typename container_type::reverse_iterator reverse_iterator;
            typedef typename container_type::const_reverse_iterator const_reverse_iterator;
            typedef typename container_type::reference reference;
            typedef typename container_type::const_reference const_reference;
            typedef typename container_type::value_type value_type;
            typedef typename container_type::size_type size_type;
            typedef typename container_type::difference_type difference_type;

            /// Default constructor.
            ContainerBase();

            /** Constructor.
             * @param c const reference to container_type.
             */
            explicit ContainerBase(const container_type& c);

            /** Constructor.  Initialize with range [begin,end).
             * @param begin Beginning iterator.
             * @param end Ending iterator.
             */
            template <typename In>
            ContainerBase(In begin, In end);

            /// Destructor.
            virtual ~ContainerBase();

            //@{
            /// Operations common among all standard containers.

            container_type& operator= (const container_type& c)
            { this->swap(c); }

            iterator begin() { return _c.begin(); }
            const_iterator begin() const { return _c.begin(); }
            iterator end() { return _c.end(); }
            const_iterator end() const { return _c.end(); }
            reverse_iterator rbegin() { return _c.rbegin(); }
            const_reverse_iterator rbegin() const { return _c.rbegin(); }
            reverse_iterator rend() { return _c.rend(); }
            const_reverse_iterator rend() const { return _c.rend(); }

            size_type size() const { return _c.size(); }
            size_type max_size() const { return _c.max_size(); }

            bool empty() const { return _c.empty(); }
            void clear() { _c.clear(); }
            void swap(const container_type& c) { _c.swap(c); }
            //@}
    
        protected:
            //@{
            /// For derived classes to use when the container itself is needed.
            container_type& container() { return _c; }
            const container_type& container() const { return _c; }
            //@}

        private:
            container_type _c;
    };

    template <typename T>
    ContainerBase<T>::ContainerBase()
    {
    }

    template <typename T>
    ContainerBase<T>::ContainerBase(const container_type& c)
        : _c(c)
    {
    }

    template <typename T>
    template <typename In>
    ContainerBase<T>::ContainerBase(In begin, In end)
        : _c(begin, end)
    {
    }

    template <typename T>
    ContainerBase<T>::~ContainerBase()
    {
    }

    /**
     * @class VectorBase container_base.hh herdstat/util/container_base.hh
     * @brief Base class template for classes acting like vector<T>.
     */

    template <typename T>
    class VectorBase : public ContainerBase<std::vector<T> >
    {
        public:
            typedef ContainerBase<std::vector<T> > base_type;
            typedef typename base_type::container_type container_type;
            typedef typename container_type::size_type size_type;
            typedef typename container_type::difference_type difference_type;
            typedef typename container_type::value_type value_type;
            typedef typename container_type::iterator iterator;
            typedef typename container_type::const_iterator const_iterator;

            VectorBase();
            VectorBase(const container_type& c);
            template <typename In>
            VectorBase(In begin, In end);

            virtual ~VectorBase();

            template <typename In>
            void assign(In begin, In end)
            { this->container().assign(begin, end); }

            void assign(size_type n, const value_type& v)
            { this->container().assign(n, v); }

            void resize(size_type sz, value_type c = value_type())
            { this->container().resize(sz, c); }

            size_type capacity() const { return this->container().capacity(); }

            void reserve(size_type n) { this->container().reserve(n); }

            value_type& operator[](size_type n)
            { return (this->container())[n]; }
            const value_type& operator[](size_type n) const
            { return (this->container())[n]; }
            const value_type& at(size_type n) { return this->container().at(n); }

            value_type& front() { return this->container().front(); }
            const value_type& front() const { return this->container().front(); }
            value_type& back() { return this->container().back(); }
            const value_type& back() const { return this->container().back(); }

            void push_back(const value_type& v)
            { this->container().push_back(v); }
            void pop_back() { this->container().pop_back(); }

            iterator insert(iterator pos, const value_type& v)
            { return this->container().insert(pos, v); }

            void insert(iterator pos, size_type n, const value_type& v)
            { this->container().insert(pos, n, v); }

            iterator erase(iterator pos) { return this->container().erase(pos); }
            iterator erase(iterator begin, iterator end)
            { return this->container().erase(begin, end); }

            template <typename In>
            void insert(iterator pos, In begin, In end)
            { this->container().insert(pos, begin, end); }
    };

    template <typename T>
    VectorBase<T>::VectorBase()
    {
    }

    template <typename T>
    VectorBase<T>::VectorBase(const container_type& c)
        : base_type(c)
    {
    }
    
    template <typename T>
    template <typename In>
    VectorBase<T>::VectorBase(In begin, In end)
        : base_type(begin, end)
    {
    }

    template <typename T>
    VectorBase<T>::~VectorBase()
    {
    }

    /**
     * @class SetBase container_base.hh herdstat/util/container_base.hh
     * @brief Base class template for classes that act like a set<T>.
     */

    template <typename T, typename Compare = std::less<T> >
    class SetBase : public ContainerBase<std::set<T, Compare> >
    {
        public:
            typedef ContainerBase<std::set<T> > base_type;
            typedef typename base_type::container_type container_type;
            typedef typename container_type::size_type size_type;
            typedef typename container_type::difference_type difference_type;
            typedef typename container_type::value_type value_type;
            typedef typename container_type::iterator iterator;
            typedef typename container_type::const_iterator const_iterator;
            typedef value_type key_type;
            typedef Compare key_compare;
            typedef Compare value_compare;

            SetBase();
            SetBase(const container_type& c);
            template <class In>
            SetBase(In begin, In end);

            virtual ~SetBase();

            std::pair<iterator, bool> insert(const value_type& v)
            { return this->container().insert(v); }
            iterator insert(iterator hintpos, const value_type& v)
            { return this->container().insert(hintpos, v); }
            template <typename In>
            void insert(In begin, In end)
            { this->container().insert(begin, end); }

            void erase(iterator pos) { this->container().erase(pos); }
            size_type erase(const key_type& k)
            { return this->container().erase(k); }
            void erase(iterator begin, iterator end)
            { this->container().erase(begin, end); }

            key_compare key_comp() const
            { return this->container().key_comp(); }
            value_compare value_comp() const
            { return this->container().value_comp(); }

            iterator find(const key_type& k)
            { return this->container().find(k); }
            const_iterator find(const key_type& k) const
            { return this->container().find(k); }
            size_type count(const key_type& k) const
            { return this->container().count(k); }

            iterator lower_bound(const key_type& k) const
            { return this->container().lower_bound(k); }
            iterator upper_bound(const key_type& k) const
            { return this->container().upper_bound(k); }
            std::pair<iterator, iterator> equal_range(const key_type& k) const
            { return this->container().equal_range(k); }
    };

    template <typename T, typename Compare>
    SetBase<T, Compare>::SetBase()
    {
    }

    template <typename T, typename Compare>
    SetBase<T, Compare>::SetBase(const container_type& c)
        : base_type(c)
    {
    }
    
    template <typename T, typename Compare>
    template <class In>
    SetBase<T, Compare>::SetBase(In begin, In end)
        : base_type(begin, end)
    {
    }

    template <typename T, typename Compare>
    SetBase<T, Compare>::~SetBase()
    {
    }

    /**
     * @class MapBase container_base.hh herdstat/util/container_base.hh
     * @brief Base class template for classes that act like a map<K,V>.
     */

    template <typename K, typename V, typename Compare = std::less<K> >
    class MapBase : public ContainerBase<std::map<K, V, Compare> >
    {
        public:
            typedef ContainerBase<std::map<K, V, Compare> > base_type;
            typedef typename base_type::container_type container_type;
            typedef typename container_type::size_type size_type;
            typedef typename container_type::difference_type difference_type;
            typedef typename container_type::value_type value_type;
            typedef typename container_type::iterator iterator;
            typedef typename container_type::const_iterator const_iterator;
            typedef K key_type;
            typedef V mapped_type;
            typedef Compare key_compare;
            typedef typename container_type::value_compare value_compare;

            MapBase();
            MapBase(const container_type& c);
            template <typename In>
            MapBase(In begin, In end);

            virtual ~MapBase();

            mapped_type& operator[](const key_type& k)
            { return (this->container())[k]; }

            std::pair<iterator, bool> insert(const value_type& v)
            { return this->container().insert(v); }
            iterator insert(iterator hintpos, const value_type& v)
            { return this->container().insert(hintpos, v); }
            template <typename In>
            void insert(In begin, In end)
            { this->container().insert(begin, end); }

            void erase(iterator pos) { this->container().erase(pos); }
            size_type erase(const key_type& k)
            { return this->container().erase(k); }
            void erase(iterator begin, iterator end)
            { this->container().erase(begin, end); }

            key_compare key_comp() const
            { return this->container().key_comp(); }
            value_compare value_comp() const
            { return this->container().value_comp(); }

            iterator find(const key_type& k)
            { return this->container().find(k); }
            const_iterator find(const key_type& k) const
            { return this->container().find(k); }

            size_type count(const key_type& k) const
            { return this->container().count(k); }

            iterator lower_bound(const key_type& k)
            { return this->container().lower_bound(k); }
            const_iterator lower_bound(const key_type& k) const
            { return this->container().lower_bound(k); }
            iterator upper_bound(const key_type& k)
            { return this->container().upper_bound(k); }
            const_iterator upper_bound(const key_type& k) const
            { return this->container().upper_bound(k); }
            std::pair<iterator, iterator> equal_range(const key_type& k)
            { return this->container().equal_range(k); }
            std::pair<const_iterator, const_iterator>
            equal_range(const key_type& k) const
            { return this->container().equal_range(k); }
    };

    template <typename K, typename V, typename Compare>
    MapBase<K,V,Compare>::MapBase()
    {
    }
    
    template <typename K, typename V, typename Compare>
    MapBase<K,V,Compare>::MapBase(const container_type& c) 
        : base_type(c)
    {
    }
    
    template <typename K, typename V, typename Compare>
    template <typename In>
    MapBase<K,V,Compare>::MapBase(In begin, In end)
        : base_type(begin, end)
    {
    }

    template <typename K, typename V, typename Compare>
    MapBase<K,V,Compare>::~MapBase()
    {
    }

} // namespace util
} // namespace herdstat

#endif /* _HAVE_CONTAINER_BASE_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
