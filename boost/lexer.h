#ifndef PARAMETER_LEXER_H_EA4CA0F57FCB41938C7DDD77B2ECA8A9
#define PARAMETER_LEXER_H_EA4CA0F57FCB41938C7DDD77B2ECA8A9
/*
 * This is a declaration for a class which manages the lexing of input.
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

#include <string>
#include <boost/spirit/include/lex_lexertl.hpp>

namespace parameters
{
#define PARAMETER_WHITE_SPACE_CHARACTERS " \n\a\b\f\r\t\v"
 namespace bsl = boost::spirit::lex;

 template <typename L>
 struct my_lexer : bsl::lexer<L>
 {
   typedef bsl::lexer<L> lexer_type;
   typedef typename bsl::lexer<L>::id_type id_type;
   typedef typename bsl::lexer<L>::char_type char_type;
   typedef typename bsl::lexer<L>::iterator_type iterator_type;
   typedef my_lexer base_type;

   my_lexer<L>(unsigned int flags = bsl::match_flags::match_default,
               id_type first_id = id_type(bsl::min_token_id));

   bsl::token_def<char_type> dot, assign;
   bsl::token_def<std::string> identifier, separation;
 };
}

#ifndef CXX_USE_EXPORT_KEY_WORD
#define export
#include <lexer_def.h>
#endif

#endif
