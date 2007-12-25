/* 

                          Firewall Builder

                 Copyright (C) 2000 NetCitadel, LLC

  Author:  Vadim Kurland     vadim@vk.crocodile.org

  $Id: Tools.h 808 2004-09-08 05:34:53Z vkurland $


  This program is free software which we release under the GNU General Public
  License. You may redistribute and/or modify this program under the terms
  of that license as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 
  To get a copy of the GNU General Public License, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

/*
 * This file contains various utility methods
 */

#ifndef __FW_TOOLS_HH_FLAG__
#define __FW_TOOLS_HH_FLAG__

#ifndef SAME
# define SAME 0
#endif

#ifndef nil
# define nil NULL
#endif

#include <string>
#include <map>
#include <list>

#ifndef _WIN32
#  include <dirent.h>
#else
#  include <io.h>
#endif

#include <fwbuilder/FWException.h>

namespace libfwbuilder
{

    /**
     * This method should be called to initialize the library
     * before any calls to it are made. The argument is a full path
     * to the executable that wants to initialize the library. Just
     * pass argv[0] there. This method passes substring between 
     * the beginning of exec_path and position of the last '/' or '\'
     * to XMLTools::init; this information is later used to find DTD
     * if template directory is defined as relative path. This is especially
     * useful on Mac and Win32 where API is not installed in the absolute
     * predetermined path.
     */
    void init();

    /**
     * Reentrant-safe version of strtok. It is available on Linux and *BSD,
     * but does not exist on Windows. We reimplement it if it does not exist.
     *
     * pthread_win32 defines macro "strtok_r", so we can't use this name
     */
    char *cxx_strtok_r(char *s, const char *delim, char **save_ptr);

    /**
     * case insensitive string comparison. We reimplement it on win32
     */
    int   cxx_strcasecmp(const char *s1, const char *s2);

    char *cxx_strdup(const char *x);
    char *cxx_strdup(const std::string &x);

    std::string int2string(int n);

    /**
     * Replace all occurences of ${MACRO} in the source string
     * with value from given map. If value not found, depending on
     * value of 'strict' flag eitehr exception is thrown or empty 
     * value is inserted.
     */
    std::string substituteMacros(const std::string &source, const std::map<std::string, std::string> &macros, bool strict=false) throw(libfwbuilder::FWException);


    /**
     * portable function that gets a list of files that reside in a given
     * directory and have specified extension
     */
    std::list<std::string> getDirList(const std::string &dir,
                                      const std::string &ext);
    /**
     * just a portable version of sleep
     */
    unsigned int cxx_sleep(unsigned int seconds);
    
}

#endif


