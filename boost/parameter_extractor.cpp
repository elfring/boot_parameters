/*
 * This is an implemention for a class which can iniate a parsing process.
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

#include <config.h>
#include <iostream>
#include <lexer.h>
#include <file.h>
#include <parameter_extractor.h>

namespace parameters
{
   namespace lx = boost::spirit::lex;

   extractor::~extractor()
   {
   }

   void
   extractor::parse(std::string const& f)
   {
      typedef lx::lexertl::token<char const*, boost::mpl::vector<std::string>> token_type;
      typedef lx::lexertl::lexer<token_type> lexer_type;
      typedef my_lexer<lexer_type>::iterator_type iterator_type;
      my_lexer<lexer_type> le;
      my_grammar<iterator_type, decltype(table)> gr(le, table);
      std::string text(get_file_content(f.c_str()));
      char const* first = text.c_str();
      char const* last = &first[text.size()];
      bool r = lx::tokenize_and_parse(first, last, le, gr);

      if (!r)
      {
         std::cerr << "stopped at: \"" << std::string(first, last) << '"' << std::endl;
         throw std::runtime_error("Parsing failure");
      }
   }
}
