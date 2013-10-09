#ifndef PARAMETER_MultiIndex_H_F8C51549E51946EA9C418C2D9DC80EF7
#define PARAMETER_MultiIndex_H_F8C51549E51946EA9C418C2D9DC80EF7
/*
 * This is a declaration for a class which stores data.
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

  struct setting
  {
   std::string primary, secondary, text;

   setting(std::string const& primary,
	   std::string const& secondary,
	   std::string const& text)
          : primary(primary), secondary(secondary), text(text) {}

   bool operator<(setting const& s) const { return    (primary < s.primary)
                                                   && (secondary < s.secondary); }
  };

  typedef bm::multi_index_container<
          setting,
          indexed_by<
             ordered_non_unique<identity<setting, std::string, &setting::primary> >,
             ordered_non_unique<member<setting, std::string, &setting::secondary> >
             >
          > settings;
}

#endif
