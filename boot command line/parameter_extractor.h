#ifndef PARAMETER_EXTRACTOR_H_AC98DD830BD8446A8304769900790C10
#define PARAMETER_EXTRACTOR_H_AC98DD830BD8446A8304769900790C10
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public Licence along
 * with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <string>
#include <map>
#include <parser.hpp>

namespace parameters
{
 class extractor
 {
 public:
  virtual ~extractor();

  std::map<std::string, std::string> parameters;

  bool trace_scanning;

  // Whether parser traces should be generated.
  bool trace_parsing;

  // Run the parser on the specified file.
  void parse(std::string const& f);

 private:
  // The name of the file being parsed.
  // Used later to pass the file name to the location tracker.
  std::string file;

  void scan_begin();
  void scan_end();

  void error(yy::location const& l, std::string const& m);
  void error(std::string const& m);

  friend class yy::my_parser;
 };
}

#define YY_DECL yy::my_parser::symbol_type yylex(parameters::extractor& driver)
YY_DECL;

#endif
