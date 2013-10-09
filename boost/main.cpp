/*
 * This is an implemention for a start function of a program.
 * Copyright 2013  Markus Elfring
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public Licence (version 3.1
 * with the Runtime Library Exception) as published by the
 * Free Software Foundation.
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
#include <iostream>
//#include <algorithm>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <parameter_extractor.h>

static void display_entry(std::pair<std::string const, std::string const> const& p)
{
 std::cout << '|' << p.first << "|: |" << p.second << '|' << std::endl;
}

int main(int argc, char* argv[])
{
 try
 {
    parameters::extractor ex;

    ex.parse(argc == 1 ? "/proc/cmdline" : argv[1]);
    std::cout << ex.table.size() << " assignments" << std::endl;

    //std::for_each(ex.table.begin(), ex.table.end(), display_entry);
    for (auto& x: ex.table)
    {
       display_entry(x);
    }
 }
 catch (std::bad_alloc const& b)
 {
    (void) std::fputs("out of memory\n", stderr);
    return EXIT_FAILURE;
 }
 catch (std::exception const& x)
 {
    (void) std::fprintf(stderr, "A kind of standard%s\n%s\n", " exception was caught.", x.what());
    return EXIT_FAILURE;
 }
 catch (...)
 {
    (void) std::fprintf(stderr, "An unknown%s\n", " exception was caught.");
    throw;
 }
}
