#ifndef PARAMETER_PARSER_H_A5C56D7CE59747E7BA1CA880DAEC22AF
#define PARAMETER_PARSER_H_A5C56D7CE59747E7BA1CA880DAEC22AF
/*
 * This is a declaration for a class which performs data parsing.
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
#include <boost/spirit/include/qi.hpp>

namespace parameters
{
 namespace bsq = boost::spirit::qi;

 template <typename I, typename T>
 struct my_grammar : bsq::grammar<I>
 {
    template <typename TD>
    my_grammar(TD const& td, T& t);

    bsq::rule<I> start,
                 allow_also_in_value,
                 value,
                 non_empty_assignment,
                 assignment_without_input_end,
                 assignment_at_input_end,
                 assignment_with_leading_delimiter,
                 assignments;

 private:
    //T::reference table; // Surprising messages from compilers ...?
    T& table;

    void add_entry(std::string primary, typename T::mapped_type value = "");
    void add_entry(std::string primary, std::string secondary, typename T::mapped_type value = "");
 };
}

#ifndef CXX_USE_EXPORT_KEY_WORD
#define export
#include <parser_def.h>
#endif

#endif
