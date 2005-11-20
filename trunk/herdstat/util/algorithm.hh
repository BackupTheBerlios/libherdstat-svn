/*
 * libherdstat -- herdstat/util/algorithm.hh
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

#ifndef _HAVE_UTIL_ALGORITHM_HH
#define _HAVE_UTIL_ALGORITHM_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/util/algorithm.hh
 * @brief Defines the general purpose algorithms.
 */

#include <iterator>

namespace herdstat {
namespace util {

    /**
     * @fn transform_if
     * @brief For each element in the range [first,last) for which UnaryPred
     * returns true, assign the result of UnaryOp to the given output iterator.
     * Like std::transform, but only "transforms" if UnaryPred returns true.
     * For times where std::replace_copy_if is not appropriate.
     */

    template <typename InputIterator, typename OutputIterator,
              typename UnaryOp, typename UnaryPred>
    OutputIterator
    transform_if(InputIterator first, InputIterator last,
                 OutputIterator result, UnaryPred pred, UnaryOp op)
    {
        for ( ; first != last ; ++first)
        {
            if (pred(*first))
                *result++ = op(*first);
        }

        return result;
    }

    /**
     * @fn copy_if
     * @brief For each element in the range [first,last) for which UnaryPred
     * returns true, copy to the given output iterator.  Like std::copy but only
     * copies if UnaryPred returns true.
     */

    template <typename InputIterator, typename OutputIterator,
              typename UnaryPred>
    OutputIterator
    copy_if(InputIterator first, InputIterator last,
            OutputIterator result, UnaryPred pred)
    {
        for ( ; first != last ; ++first )
        {
            if (pred(*first))
                *result++ = *first;
        }

        return result;
    }

    /**
     * @fn all_equal
     * @brief Determine whether all elements in the range [first,last) are
     * equal.
     */

    template <typename InputIterator>
    bool
    all_equal(InputIterator first, InputIterator last)
    {
        typename std::iterator_traits<InputIterator>::value_type v(*first);
        const typename std::iterator_traits<InputIterator>::difference_type size =
            std::distance(first, last);
        return (size == std::count(first, last, v));
    }

    /**
     * @fn all_equal
     * @brief Determine whether the return values of UnaryOp run on each in the
     * range [first,last) are equal.
     */

    template <typename InputIterator, typename UnaryOp>
    bool
    all_equal(InputIterator first, InputIterator last, UnaryOp op)
    {
        typename std::iterator_traits<InputIterator>::value_type v(op(*first++));

        while (first != last)
        {
	    if (v != op(*first++))
	        return false;
        }

        return true;
    }

} // namespace util
} // namespace herdstat

#endif /* _HAVE_UTIL_ALGORITHM_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
