/*
 * herdstat -- herdstat/util/file.cc
 * $Id: file.cc 655 2005-10-02 16:15:01Z ka0ttic $
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <algorithm>
#include <functional>
#include <iterator>
#include <utility>
#include <cstring>
#include <cassert>

#include <herdstat/util/file.hh>
#include <herdstat/exceptions.hh>

namespace herdstat {
namespace util {
/*****************************************************************************/
Stat::Stat()
    : _path(), _type(REGULAR), _exists(false), _opened(false)
{
}
/*****************************************************************************/
Stat::Stat(const std::string &p, bool opened)
    : _path(p), _type(REGULAR), _exists(false), _opened(opened)
{
    this->operator()();
}
/*****************************************************************************/
void
Stat::assign(const std::string &p, bool opened)
{
    this->_opened = opened;
    this->_path.assign(p);
    this->operator()();
}
/*****************************************************************************/
bool
Stat::operator() ()
{
    if (this->_opened)
    {
        /* TODO: figure out how to fstat an open stream. */
    }
    else
    {
        this->_exists = (::stat(this->_path.c_str(), this) == 0);
    }

    if (S_ISREG(this->st_mode))
        this->_type = REGULAR;
    else if (S_ISDIR(this->st_mode))
        this->_type = DIRECTORY;
    else if (S_ISCHR(this->st_mode))
        this->_type = CHARACTER;
    else if (S_ISBLK(this->st_mode))
        this->_type = BLOCK;
    else if (S_ISFIFO(this->st_mode))
        this->_type = FIFO;
    else if (S_ISLNK(this->st_mode))
        this->_type = LINK;
    else if (S_ISSOCK(this->st_mode))
        this->_type = SOCKET;

    return this->_exists;
}
/*****************************************************************************/
BaseFileObject::BaseFileObject()
    : _stat(), _opened(false)
{
}
/*****************************************************************************/
BaseFileObject::BaseFileObject(const std::string &path)
    : _stat(path), _opened(false)
{
}
/*****************************************************************************/
BaseFileObject::~BaseFileObject()
{
}
/*****************************************************************************/
BaseFile::BaseFile() : stream(NULL)
{
}
/*****************************************************************************/
BaseFile::BaseFile(const std::string &path, std::ios_base::openmode mode)
    : BaseFileObject(path), stream(NULL)
{
    this->open(this->path().c_str(), mode);
}
/*****************************************************************************/
BaseFile::~BaseFile()
{
    if (this->is_open())
        this->close();
}
/*****************************************************************************/
void
BaseFile::open(const char *n, std::ios_base::openmode mode)
{
    if (this->is_open())
        return;

    if (this->path() != n)
        this->stat().assign(n);

    if (this->stream)
    {
        if (this->stream->is_open())
        {
            this->set_open(true);
            return;
        }
        
        this->stream->open(n, mode);
    }
    else
        this->stream = new std::fstream(n, mode);

    if (not this->stream->is_open())
        throw FileException(n);

    this->set_open(true);
}
/*****************************************************************************/
void
BaseFile::open()
{
    this->open(this->path().c_str(), DEFAULT_MODE);
}
/*****************************************************************************/
void
BaseFile::open(std::ios_base::openmode mode)
{
    this->open(this->path().c_str(), mode);
}
/*****************************************************************************/
void
BaseFile::close()
{
    if (not this->is_open())
        return;

    delete this->stream;
    this->stream = NULL;

    this->set_open(false);
}
/*****************************************************************************/
File::File(const std::string &path, std::ios_base::openmode mode)
    : BaseFile(path, mode), _contents()
{
    this->read();
}
/*****************************************************************************/
File::~File()
{
}
/*****************************************************************************/
void
File::read()
{
    assert(this->stream and this->stream->is_open());

    std::string line;
    while (std::getline(*(this->stream), line))
        this->push_back(std::string(line));
}
/*****************************************************************************/
bool
File::operator== (const File &that) const
{
    if (this->bufsize() != that.bufsize())
        return false;

    return std::equal(this->begin(), this->end(), that.begin());
}
/*****************************************************************************/
void
File::dump(std::ostream &os) const
{
    std::copy(this->begin(), this->end(),
        std::ostream_iterator<value_type>(os, "\n"));
}
/*****************************************************************************/
void
File::write()
{
    this->dump(*(this->stream));
    this->clear();
}
/*****************************************************************************/
Directory::Directory() : _dirp(NULL), _contents()
{
}
/*****************************************************************************/
Directory::Directory(const std::string &path)
    : BaseFileObject(path), _dirp(NULL), _contents()
{
    this->open();
    this->read();
}
/*****************************************************************************/
Directory::~Directory()
{
    if (this->is_open())
        this->close();
}
/*****************************************************************************/
void
Directory::close()
{
    if (not this->is_open())
        return;

#ifdef CLOSEDIR_VOID
    closedir(this->_dirp);
#else /* CLOSEDIR_VOID */
    if (closedir(this->_dirp) != 0)
        throw ErrnoException("closedir: " + this->path());
#endif /* CLOSEDIR_VOID */

    this->set_open(false);
}
/*****************************************************************************/
void
Directory::open()
{
    if (this->is_open())
        return;

    assert(not this->path().empty());

    this->_dirp = opendir(this->path().c_str());
    if (not this->_dirp)
        throw FileException(this->path());

    this->set_open(true);
}
/*****************************************************************************/
void
Directory::read()
{
    struct dirent *d = NULL;
    while ((d = readdir(this->_dirp)))
    {
        /* skip . and .. */
        if ((std::strcmp(d->d_name, ".") == 0) or
            (std::strcmp(d->d_name, "..") == 0))
            continue;

        this->push_back(this->path() + "/" + d->d_name);
    }
}
/*****************************************************************************/
Directory::iterator
Directory::find(const std::string &base)
{
    const std::string path(this->path()+"/"+base);
    return std::find(this->begin(), this->end(), path);
}
/*****************************************************************************/
Directory::const_iterator
Directory::find(const std::string &base) const
{
    const std::string path(this->path()+"/"+base);
    return std::find(this->begin(), this->end(), path);
}
/*****************************************************************************/
Directory::iterator
Directory::find(const Regex& regex)
{
    return std::find_if(this->begin(), this->end(),
        std::bind1st(regexMatch(), regex));
}

/*****************************************************************************/
Directory::const_iterator
Directory::find(const Regex& regex) const
{
    return std::find_if(this->begin(), this->end(),
        std::bind1st(regexMatch(), regex));
}
/*****************************************************************************
 * general purpose file-related functions                                    *
 *****************************************************************************/
std::string
basename(const std::string& path)
{
    std::string result(path);
    std::string::size_type pos;

    /* chop all trailing /'s */
    while (result[result.length() - 1] == '/' and result.length() > 1)
	result.erase(result.length() - 1);

    if ((pos = result.rfind('/')) != std::string::npos)
	result = result.substr(pos + 1);

    return ( result.empty() ? std::string("/") : result );
}
/*****************************************************************************/
std::string
dirname(const std::string& path)
{
    std::string result(path);
    std::string::size_type pos;

    /* chop all trailing /'s */
    while (result[result.length() - 1] == '/' and result.length() > 1)
	result.erase(result.length() - 1);

    if ((pos = result.rfind('/')) != std::string::npos)
        result.erase(pos);
    else
        result.assign(".");

    return ( result.empty() ? std::string("/") : result );
}
/*****************************************************************************/
const char *
chop_fileext(const std::string& path, unsigned short depth)
{
    std::string result(path);

    for (; depth > 0 ; --depth)
    {
        std::string::size_type pos = result.rfind('.');
        if (pos != std::string::npos)
            result = result.substr(0, pos);
    }

    return result.c_str();
}
/*****************************************************************************/
void
copy_file(const std::string& from, const std::string& to)
{
    /* remove to if it exists */
    if (is_file(to) and (unlink(to.c_str()) != 0))
	throw FileException(to);

    std::ifstream ffrom(from.c_str());
    std::ofstream fto(to.c_str());

    if (not ffrom)
	throw FileException(from);
    if (not fto)
	throw FileException(to);

    /* read from ffrom and write to fto */
    std::string line;
    while (std::getline(ffrom, line))
	fto << line << std::endl;
}
/*****************************************************************************/
void
move_file(const std::string& from, const std::string& to)
{
    copy_file(from, to);
    if (unlink(from.c_str()) != 0)
	throw FileException(from);
}
/*****************************************************************************/
} // namespace util
} // namespace herdstat

/* vim: set tw=80 sw=4 et : */
