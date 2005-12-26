/*
 * libherdstat -- herdstat/util/readline.hh
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

#ifndef _HAVE_UTIL_READLINE_HH
#define _HAVE_UTIL_READLINE_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <string>
#include <herdstat/exceptions.hh>
#include <readline/readline.h>
#include <readline/history.h>

namespace herdstat {
namespace util {

    /// ReadLine EOF exception, thrown when readline encounters an EOF
    class ReadLineEOF : public BaseException { };

    /**
     * @class ReadLine
     * @brief Interface to the readline library.  Note that the interface is
     * currently incomplete.  Stuff will be added as it is needed/requested.
     *
     * @section example Example
     * 
     * Below is a simple example of using the ReadLine class:
     *
@code
try
{
    herdstat::util::ReadLine rl("MyApp", "prompt> ");
    std::string input;

    while (input != "quit" and input != "exit")
    {
        input = rl();
        if (input.empty())
            continue;

        ...

        if (input == "foo")
            rl.set_prompt("foo> ");
    }
}
catch (const herdstat::util::ReadLineEOF&)
{

}
@endcode
     */

    class ReadLine
    {
        public:
            /** Default constructor.
             * @param name Application name (rl_readline_name) for conditional
             * parsing of inputrc.
             * @param prompt prompt text to use when displaying the prompt.
             */
            ReadLine(const std::string& name = "",
                     const std::string& prompt = "") throw();

            /** Constructor.
             * @param startup_hook function pointer to readline startup hook.
             */
            ReadLine(rl_hook_func_t *startup_hook) throw();

            /** Constructor.
             * @param name Application name (rl_readline_name) for conditional
             * parsing of inputrc.
             * @param prompt prompt text to use when displaying the prompt.
             * @param startup_hook function pointer to readline startup hook.
             */
            ReadLine(const std::string& name,
                     const std::string& prompt,
                     rl_hook_func_t *startup_hook) throw();

            /// Destructor.
            ~ReadLine() throw();

            /// Set name (rl_readline_name).
            inline void set_name(const std::string& name);
            /// Get name (rl_readline_name).
            inline const std::string& name() const { return _name; }
            /// Set prompt (rl_prompt).
            inline void set_prompt(const std::string& prompt)
            { _prompt.assign(prompt); }
            /// Get prompt (rl_prompt).
            inline const std::string& prompt() const { return _prompt; }
            
            /** Set attempted completion function
             * (rl_attempted_completion_function).
             */
            inline void set_attempted_comp_hook(rl_completion_func_t *hook);

            /// Set completion entry function (rl_completion_entry_function).
            inline void set_completion_entry_hook(rl_compentry_func_t *hook);

            /** Get user input (also adds input to history).
             * @param text preexisting text to be present when the prompt is
             * shown (defaults to empty).
             * @returns user input.
             * @exception ReadLineEOF
             */
            std::string operator()(const std::string& text = "") const
                throw (ReadLineEOF);

        private:
            void _init() throw();

            std::string _name;
            std::string _prompt;
            rl_hook_func_t *_inithook;
    };

    inline void
    ReadLine::set_name(const std::string& name)
    {
        _name.assign(name);
        if (not _name.empty())
            rl_readline_name = _name.c_str();
    }

    inline void
    ReadLine::set_attempted_comp_hook(rl_completion_func_t *hook)
    {
        assert(hook);
        rl_attempted_completion_function = hook;
    }

    inline void
    ReadLine::set_completion_entry_hook(rl_compentry_func_t *hook)
    {
        assert(hook);
        rl_completion_entry_function = hook;
    }

} // namespace util
} // namespace herdstat

#endif /* _HAVE_UTIL_READLINE_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
