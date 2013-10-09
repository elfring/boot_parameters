#ifndef PARAMETER_PARSER_DEF_H_0E1F243E10F149A99446D512CBB54807
#define PARAMETER_PARSER_DEF_H_0E1F243E10F149A99446D512CBB54807
/*
 * This is an implemention for a class which performs data parsing.
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

#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/spirit/include/phoenix_container.hpp>
#include <boost/spirit/home/phoenix/bind.hpp>
#include <boost/spirit/include/qi_no_skip.hpp>
#include <boost/spirit/include/qi_optional.hpp>
#include <boost/spirit/include/qi_kleene.hpp>
#include <boost/spirit/include/qi_eoi.hpp>
#include <boost/spirit/include/qi_eps.hpp>

namespace parameters
{
   export
   template <typename I, typename T>
   void
   my_grammar<I, T>::add_entry(std::string primary,
                               typename T::mapped_type value)
   {
#ifdef PARAMETER_USE_MultiIndex
      table[key] = value;
#else
      table[primary] = value;
#endif
   }

   export
   template <typename I, typename T>
   void
   my_grammar<I, T>::add_entry(std::string primary,
                               std::string secondary,
                               typename T::mapped_type value)
   {
#ifdef PARAMETER_USE_MultiIndex
      table[key] = value;
#else
      table[(primary += '.') += secondary] = value;
#endif
   }

   export
   template <typename I, typename T>
   template <typename TD>
   my_grammar<I, T>::my_grammar(TD const& td, T& t)
    : my_grammar<I, T>::base_type(start),
//      value("[^" PARAMETER_WHITE_SPACE_CHARACTERS "]+"),
//      value(bsq::no_skip[+ bsq::graph]),
      allow_also_in_value(td.dot | td.assign),
      table(t)
   {
      using bsq::_1;
      using bsq::_2;
      using bsq::_3;
      using bsq::_4;
      using bsq::eoi;
      value = *( ( - td.identifier ) >> allow_also_in_value )
              >> ( td.identifier | allow_also_in_value )
      ;
      non_empty_assignment = (td.identifier >> td.assign >> value)
                             [bind(&my_grammar<I, T>::add_entry, _1, _3)]
                             | (td.identifier >> td.dot >> td.identifier >> td.assign >> value)
                               [bind(&my_grammar<I, T>::add_entry, _1, _3, bsq::_5)]
                             | (td.identifier >> td.dot >> td.assign >> value)
                               [bind(&my_grammar<I, T>::add_entry, _1, "", _4)]
      ;
      assignment_without_input_end = non_empty_assignment
                                     | (td.identifier >> - (td.assign >> value))
                                       [bind(&my_grammar<I, T>::add_entry, _1, _3)]
                                     | (td.identifier >> td.dot >> td.identifier)
                                       [bind(&my_grammar<I, T>::add_entry, _1, _3, "")]
                                     | (td.dot >> td.identifier >> td.assign >> value)
                                       [bind(&my_grammar<I, T>::add_entry, "", _2, _4)]
      ;
      assignment_at_input_end = ( non_empty_assignment
                                | (td.identifier >> td.assign)
                                  [bind(&my_grammar<I, T>::add_entry, _1)]
                                | (td.identifier >> td.dot >> td.assign)
                                  [bind(&my_grammar<I, T>::add_entry, _1, "", "")]
                                | (td.identifier >> td.dot >> td.identifier >> - td.assign)
                                  [bind(&my_grammar<I, T>::add_entry, _1, _3, "")]
                                | (td.dot >> td.identifier >> td.assign)
                                  [bind(&my_grammar<I, T>::add_entry, "", _2, "")]
                                ) >> eoi
      ;
      assignment_with_leading_delimiter = td.separation >> assignment_without_input_end
      ;
      assignments = ( ( *assignment_with_leading_delimiter ) >> assignment_at_input_end )
                    | (
                        (
                          (
                            (
                            - ( assignment_with_leading_delimiter
                              | ( assignment_without_input_end >> ( *assignment_with_leading_delimiter ) )
                              )
                            ) >> td.separation
                          )
                          | bsq::eps /* empty */
                        ) >> eoi
                      )
      ;

      start =  bsq::no_skip[assignments];
   }
}

#endif
