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
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <iostream>
#include <parameter_extractor.h>

extern int yy_flex_debug;
extern FILE* yyin;

namespace parameters
{
   extractor::~extractor()
   {
   }

   void
   extractor::parse(std::string const& f)
   {
       file = f;
       scan_begin();
       yy::my_parser p(*this);
       p.set_debug_level(trace_parsing);
       int x = p.parse();
       scan_end ();

       if (!x)
          throw std::runtime_error("Parsing failure");
   }

   void
   extractor::error(yy::location const& l, std::string const& m)
   {
      std::cerr << l << ": " << m << std::endl;
   }

   void
   extractor::error(std::string const& m)
   {
       std::cerr << m << std::endl;
   }

   void
   extractor::scan_begin()
   {
       yy_flex_debug = trace_scanning;

       if (file.empty() || file == "-")
          yyin = stdin;
       else if ( !(yyin = std::fopen(file.c_str(), "r")) )
       {
          error("could not open " + file + ": " + std::strerror(errno));
          exit(EXIT_FAILURE);
       }
   }

   void
   extractor::scan_end()
   {
       int x = std::fclose(yyin);

       if (!x)
       {
          error("could not close " + file + ": " + std::strerror(errno));
          exit(EXIT_FAILURE);
       }
   }
}
