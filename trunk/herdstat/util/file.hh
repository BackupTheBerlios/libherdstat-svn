/*
 * libherdstat -- herdstat/util/file.hh
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

#ifndef HAVE_FILE_HH
#define HAVE_FILE_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/util/file.hh
 * @brief Defines file/directory-related classes/functions.
 */

#include <ios>
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cerrno>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#include <herdstat/util/regex.hh>
#include <herdstat/util/container_base.hh>

/**
 * @def DEFAULT_MODE
 * @brief Default open mode used when none is specified.
 */

#define DEFAULT_MODE    std::ios::in

namespace herdstat {
namespace util {

    /**
     * Does the specified path exist?
     * @param path Path.
     * @returns A boolean value.
     */

    inline bool
    file_exists(const std::string& path)
    {
        return (access(path.c_str(), F_OK) == 0);
    }

    /**
     * Is the given path a directory?
     * @param p Path.
     * @returns A boolean value.
     */

    inline bool
    is_dir(const std::string &p)
    {
        struct stat s;
        return ((stat(p.c_str(), &s) == 0) ? S_ISDIR(s.st_mode) : false);
    }

    /**
     * Is the file associated with the given stat structure a directory?
     * @param s Reference to a struct stat.
     * @returns A boolean value.
     */

    inline bool is_dir(const struct stat &s) { return S_ISDIR(s.st_mode); }

    /**
     * Is the given path a regular file?
     * @param p Path.
     * @returns A boolean value.
     */

    inline bool
    is_file(const std::string &p)
    {
        struct stat s;
        return ((stat(p.c_str(), &s) == 0) ? S_ISREG(s.st_mode) : false);
    }

    /**
     * Is the file associated with the given stat structure a regular file?
     * @param s Reference to a struct stat.
     * @returns A boolean value.
     */

    inline bool is_file(const struct stat &s) { return S_ISREG(s.st_mode); }

    /**
     * Return the basename of the given path.
     * @param p Path.
     */

    std::string basename(const std::string &p);
    
    /**
     * Return the directory name the given path is located in.
     * @param p Path.
     */

    std::string dirname(const std::string &p);

    /**
     * Chop file extension from the given path.
     * @param p Path.
     * @param depth Number of period-delimited extensions to chop.
     * @returns A pointer of type char.
     */

    const char *chop_fileext(const std::string &p, unsigned short depth = 1);

    /**
     * Copy file 'from' to file 'to'.
     * @param from Source location.
     * @param to   Destination location.
     */

    void copy_file(const std::string &to, const std::string &from);

    /**
     * Move file 'from' to file 'to'.
     * @param from Source location.
     * @param to   Destination location.
     */

    void move_file(const std::string &to, const std::string &from);

    /**
     * @enum ftype
     * @brief Denotes file type.
     */

    enum ftype { REGULAR, DIRECTORY, CHARACTER, BLOCK, FIFO, LINK, SOCKET };

    /**
     * @class Stat file.hh herdstat/util/file.hh
     * @brief A wrapper for struct stat and the stat() system call.
     */

    class Stat : public stat
    {
        public:
            typedef dev_t   device_type;
            typedef ino_t   inode_type;
            typedef mode_t  mode_type;
            typedef uid_t   uid_type;
            typedef gid_t   gid_type;
            typedef off_t   size_type;
            typedef time_t  time_type;

            /// Default constructor.
            Stat();

            /** Constructor.
             * @param p Path.
             * @param opened Has the file associated with this been opened?
             */
            Stat(const std::string &p, bool opened = false);

            device_type device()   const { return this->st_dev; }
            inode_type  inode()    const { return this->st_ino; }
            mode_type   mode()     const { return this->st_mode; }
            uid_type    uid()      const { return this->st_uid; }
            gid_type    gid()      const { return this->st_gid; }
            size_type   size()     const { return this->st_size; }
            time_type   atime()    const { return this->st_atime; }
            time_type   mtime()    const { return this->st_mtime; }
            time_type   ctime()    const { return this->st_ctime; }
            const std::string& path()    const { return this->_path; }
            ftype       type()     const { return this->_type; }

            /// Assign a new path and stat it.
            void assign(const std::string &p, bool opened = false);

            /** Does the file associated with this exist?
             * @returns A boolean value.
             */
            bool exists() const { return this->_exists; }

            /** stat() wrapper.
             * @returns A boolean value (exists()).
             */
            bool operator() ();

        protected:
            std::string _path;
            ftype _type;
            bool _exists, _opened;
    };

    /**
     * @class BaseFileObject file.hh herdstat/util/file.hh
     * @brief Abstract file object.
     */

    class BaseFileObject
    {
        public:
            /// Default constructor.
            BaseFileObject();

            /** Constructor.
             * @param path Path.
             */
            BaseFileObject(const std::string &path);

            /// Destructor.
            virtual ~BaseFileObject();

            /// Get path of file.
            const std::string& path() const { return _stat.path(); }
            /// Set path of file.
            void set_path(const std::string& path) { _stat.assign(path); }
            /// Get reference to stat member.
            Stat& stat() { return _stat; }
            /// Get const reference to stat member.
            const Stat& stat() const { return _stat; }

            /** Has this file object been opened?
             * @returns A boolean value.
             */
            bool is_open() const { return _opened; }

            /** Dump our internal contents to disk.
             * @param s Output stream.
             */
            virtual void dump(std::ostream &s) const { }

            /// Open file object.
            virtual void open()     = 0;

            /// Close file object.
            void close();

            /// Read file object, filling internal container.
            void read();
            void read(const std::string& path);

        protected:
            /// Manually override whether this file is opened or not.
            void set_open(const bool opened) { _opened = opened; }

            /// Read file object, filling internal container.
            virtual void do_read() = 0;

            /// Close
            virtual void do_close() = 0;

        private:
            /// stat object associated with this file object.
            Stat  _stat;
            /// whether this file has been opened.
            bool    _opened;
    };

    /**
     * @class BaseFile file.hh herdstat/util/file.hh
     * @brief Base type for representing regular files.
     */

    class BaseFile : public BaseFileObject
    {
        public:
            typedef std::fstream stream_type;

            /// Default constructor.
            BaseFile();

            /// Copy constructor
            BaseFile(const BaseFile& that);

            /** Constructor.  Opens file.
             * @param path Path to file.
             * @param mode Open mode (defaults to DEFAULT_MODE).
             */
            BaseFile(const std::string &path,
                    std::ios_base::openmode mode = DEFAULT_MODE);

            /// Destructor.  Closes file if opened.
            virtual ~BaseFile();

            /// Copy assignment operator.
            BaseFile& operator= (const BaseFile& that);

            const std::ios_base::openmode& mode() const { return _mode; }

            /// Open file with default open mode.
            virtual void open();

            /** Open specified path with specified open mode.
             * @param path Path to file.
             * @param mode Open mode (defaults to DEFAULT_MODE).
             */
            virtual void open(const char *path,
                std::ios_base::openmode mode = DEFAULT_MODE);

            /** Open with specified open mode.
             * @param mode Open mode.
             */
            virtual void open(std::ios_base::openmode mode);

        protected:
            void set_mode(std::ios_base::openmode mode) { _mode = mode; }

            /// close file
            virtual void do_close();

            /// Get stream associated with this.
            stream_type& stream() { assert(_stream); return *_stream; }

        private:
            /// stream associated with this.
            stream_type *_stream;
            /// open mode
            std::ios_base::openmode _mode;
    };

    /**
     * @class File file.hh herdstat/util/file.hh
     * @brief Represents a regular file using a vector of std::string's for
     * storing file contents.
     */

    class File : public BaseFile,
                 public VectorBase<std::string>
    {
        public:
            /** Constructor.  Opens and reads file.
             * @param path Path to file.
             * @param mode Open mode (defaults to DEFAULT_MODE).
             */
            File(const std::string &path,
                   std::ios_base::openmode mode = DEFAULT_MODE);

            /// Destructor.
            virtual ~File();

            /** File size.
             * @returns An unsigned integer value.
             */
            Stat::size_type filesize() const { return this->stat().size(); }

            /** Internal buffer size (number of lines in file).
             * @returns An unsigned integer value.
             */
            size_type bufsize() const { return this->size(); }

            /** Determine if two files are equal.
             * @param f File object.
             * @returns A boolean value.
             */
            bool operator== (const File &f) const;

            /** Determine if two files are not equal.
             * @param f File object.
             * @returns A boolean value.
             */
            bool operator!= (const File &f) const
            { return not (*this == f); }

            /** Dump internal container to specified stream.
             * @param s Output stream.
             */
            virtual void dump(std::ostream &s) const;

            /// Dump internal container to disk.
            virtual void write();

        protected:
            /// read contents into container
            virtual void do_read();
    };

    /**
     * @class Directory file.hh herdstat/util/file.hh
     * @brief A directory using a vector of std::string's to represent
     * directory contents.
     */

    class Directory  : public BaseFileObject,
                       public VectorBase<std::string>
    {
        public:
            /// Default constructor.
            Directory();

            /** Constructor.  Opens and reads directory.
             * @param path Path.
             */
            Directory(const std::string& path);

            /// Destructor. Closes directory if opened.
            virtual ~Directory();

            /// Open directory.
            virtual void open();

            /** Find element with the specified name.
             * @param p Path.
             * @returns An iterator to the element (or end() if not found).
             */
            iterator find(const value_type& p);

            /** Find element that matches the specified regular expression.
             * @param r Reference to a util::Regex object.
             * @returns An iterator to the element (or end() if not found).
             */
            iterator find(const Regex& r);

            /** Find element with the specified name.
             * @param p Path.
             * @returns A const_iterator to the element (or end() if not found).
             */
            const_iterator find(const value_type& p) const;

            /** Find element that matches the specified regular expression.
             * @param r Reference to a util::Regex object.
             * @returns A const_iterator to the element (or end() if not found).
             */
            const_iterator find(const Regex& r) const;

        protected:
            /// Read directory.
            virtual void do_read();

            /// Close directory.
            virtual void do_close();

        private:
            /// Internal DIR pointer.
            DIR *_dirp;
    };

} // namespace util
} // namespace herdstat

#endif /* HAVE_FILE_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
