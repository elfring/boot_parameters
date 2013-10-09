%{
/*
 * This is a specification for a the lexing of input.
 * Copyright 2013  Markus Elfring
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public Licence (version 3)
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public Licence for more details.
 *
 * You should have received a copy of the GNU General Public Licence along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <config.h>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <string>
#include <parameter_extractor.h>
#include <parser.hpp>

/* http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231 */
#undef yywrap
#define yywrap() 1

static yy::location loc;
%}

%option noyywrap nounput batch debug noinput

white_space [ \n\a\b\f\r\t\v]
identification_character [^.= \n\a\b\f\r\t\v]

%{
#define YY_USER_ACTION loc.columns(yyleng);
%}

%%

%{
loc.step();
%}

{white_space}+ { return yy::my_parser::make_SEPARATION(yytext, loc); }
{identification_character}+ { return yy::my_parser::make_IDENTIFIER(yytext, loc); }
= { return yy::my_parser::make_ASSIGN(*yytext, loc); }
\. { return yy::my_parser::make_DOT(*yytext, loc); }
<<EOF>> { return yy::my_parser::make_END(loc); }
