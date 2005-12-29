/*
 * libherdstat -- herdstat/readline/history.hh
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

#ifndef _HAVE_READLINE_HISTORY_HH
#define _HAVE_READLINE_HISTORY_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/readline/history.hh
 * @brief Provides the History class definition.
 */

#include <string>
#include <vector>
#include <herdstat/exceptions.hh>
#include <readline/history.h>

namespace herdstat {
namespace readline {

    ///@{
    /// typedefs for naming consistency
    typedef HIST_ENTRY HistoryEntry;
    typedef HIST_ENTRY ** HistoryList;
    typedef HISTORY_STATE HistoryState;
    typedef histdata_t HistoryData;
    ///@}

    /**
     * @class History history.hh herdstat/readline/history.hh
     * @brief Interface to readline's libhistory.
     */

    class History
    {
        public:
            /// Default constructor.
            History() throw();

            /* Constructor.
             * @param path path to history file.
             */
            History(const std::string& path) throw();

            /// Destructor.
            ~History() throw();

            /// Get path to history file.
            inline const std::string& path() const { return _path; }

            /// Set path to history file.
            inline void set_path(const std::string& path)
            { _path.assign(path); }

            /// Add line to history.
            inline void add(const std::string& line)
            { add_history(line.c_str()); }
            
            /** Remove line from history.
             * @param offset offset of entry to remove.
             * @returns removed history entry.
             */
            inline HistoryEntry *remove(int offset)
            { return remove_history(offset); }

            /// Free history entry.
            inline HistoryData free(HistoryEntry *entry)
            { return free_history_entry(entry); }

            /// Replace history entry.
            inline HistoryEntry *replace(int which, const std::string& line,
                    HistoryData data)
            { return replace_history_entry(which, line.c_str(), data); }

            /// Get offset of current HistoryElement.
            inline int offset() { return where_history(); }

            /// Set current history offset.
            inline bool set_offset(int offset)
            { return history_set_pos(offset); }

            /// Get current history entry.
            inline HistoryEntry *current_entry() { return current_history(); }

            /// Get history entry at the specified offset.
            inline HistoryEntry *entry_at_offset(int offset)
            { return history_get(offset); }

            /// Clear history.
            inline void clear() { clear_history(); }

            /// Is the history stifled?
            inline bool stifled() const { return history_is_stifled(); }

            /** Stifle history.
             * @param max maximum number of entries to remember.
             */
            inline void stifle(int max) { stifle_history(max); }

            /** Unstifle history.
             * @returns previously-set maximum number of history entries (or a
             * negative value if history was not previously stifled).
             */
            inline int unstifle() { return unstifle_history(); }

            /// Read history from disk.
            void read() throw (FileException);

            /** Read history range [from,to) from disk.
             * @param from starting line number.
             * @param to ending line number.
             */
            void read(int from, int to) throw (FileException);
            
            /// Write history to disk.
            void write() throw (FileException);

        private:
            void _init() throw();

            std::string _path;
    };

} // namespace readline
} // namespace herdstat

#endif /* _HAVE_READLINE_HISTORY_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
