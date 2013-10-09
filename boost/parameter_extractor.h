#ifndef PARAMETER_EXTRACTOR_H_87902AB38378461EA61BE1548BFFD171
#define PARAMETER_EXTRACTOR_H_87902AB38378461EA61BE1548BFFD171
/*
 * This is a declaration for a class which can iniate a parsing process.
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

#ifdef PARAMETER_USE_MultiIndex
#include <boost/multi_index_container.hpp>
#else
#include <map>
#endif

#include <string>
#include <parser.h>

namespace parameters
{
#ifdef PARAMETER_USE_MultiIndex
 namespace bm = ::boost::multi_index;
#endif

 class extractor
 {
 public:
  virtual ~extractor();

#ifdef PARAMETER_USE_MultiIndex
#include <multi_index.h>
  settings table;
#else
  std::map<std::string, std::string> table;
#endif

  // Run the parser on the specified file.
  void parse(std::string const& f);

 private:
 };
}

#endif
