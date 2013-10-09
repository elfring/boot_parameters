#ifndef PARAMETER_LEXER_DEF_H_135C106D3F254A1D901866154CA00B5C
#define PARAMETER_LEXER_DEF_H_135C106D3F254A1D901866154CA00B5C
/*
 * This is an implemention for a class which manages the lexing of input.
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

namespace parameters
{
   export
   template <typename L>
   my_lexer<L>::my_lexer(unsigned int flags, id_type first_id)
    : bsl::lexer<L>(flags, first_id),
      dot('.'),
      assign('='),
      identifier("{white_space}+"),
      separation("{identification_character}+")
   {
      this->self.add_pattern("white_space", "[" PARAMETER_WHITE_SPACE_CHARACTERS "]");
      this->self.add_pattern("identification_character", "[^.=" PARAMETER_WHITE_SPACE_CHARACTERS "]");
      this->self.add
                 (dot)
                 (assign)
                 (identifier)
                 (separation)
                 ;
   }
}

#endif
