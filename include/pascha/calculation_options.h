// Copyright (C) 2022, 2024 Christopher Michael Mescher
//
// pascha-lib: A library for calculating the date of Pascha (Easter).
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// Contact !(echo \<pascha-mescher+faith\>|sed s/\+/./g\;s/\-/@/) for bug
// reporting.

#ifndef PASCHA_CALCULATION_OPTIONS_H
#define PASCHA_CALCULATION_OPTIONS_H

#include "typedefs.h"

#include <vector>

namespace pascha
{

using ECalculationMethod = int;
using EOutputCalendar = int;
using ETargetOutput = int;
using EOutputOption = int;

struct CalculationOptions
{
  ECalculationMethod calculation_method;
  std::vector<ETargetOutput> target_outputs;
  EOutputCalendar output_calendar;
  std::vector<EOutputOption> options;
  Year year;
}; // struct CalculationOptions


namespace e_calculation_method
{

enum {
  julian = 0,
  gregorian,
  last, // for extensions
}; // enum

} // namespace ECalculationMethod

namespace e_target_output
{

enum {
  pascha = 0,
  daysUntil,
  weeksBetween,
  meatfare,
  cheesefare,
  ashWednesday,
  midfeastPentecost,
  leavetakingPascha,
  ascension,
  pentecost,
  last, // for extensions
}; // enum

} // namespace e_target_date

namespace e_output_calendar
{

enum {
  julian = 0,
  gregorian,
  rev_julian,
  last, // for extensions
}; // enum

} // namespace e_output_calendar

namespace e_output_option
{

enum {
  byzantine = 0,
  last, // for extensions
}; // enum

} // namespace e_output_option

} // namespace pascha

#endif // !PASCHA_CALCULATION_OPTIONS_H
