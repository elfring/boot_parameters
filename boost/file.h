#ifndef PARAMETER_FILE_H_9EF4980AF2D84725A12FB3B8FAEEB02F
#define PARAMETER_FILE_H_9EF4980AF2D84725A12FB3B8FAEEB02F
/*
 * Functionality around file handling
 * Copyright 2013  Markus Elfring
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public Licence (version 3.1
 * with the Runtime Library Exception) as published by the
 * Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public Licence for more details.
 *
 * You should have received a copy of the GNU General Public Licence along
 * with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <fstream>
#include <string>

namespace parameters
{
   inline
   std::string 
   get_file_content(char const* name)
   {
       std::ifstream in(name);

       if (! in.is_open())
          throw std::runtime_error("File open failure");

       in.unsetf(std::ios::skipws);

       return std::string(std::istreambuf_iterator<char>(in.rdbuf()),
                          std::istreambuf_iterator<char>());
   }
}

#endif
