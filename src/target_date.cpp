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

#include "pascha/target_date.h"

#include <ctime>

namespace pascha
{

void TargetDate::shift(int days, Date& date) const
{
  std::tm t{};
  t.tm_year = date.year - 1900;
  t.tm_mon = date.month - 1;
  t.tm_mday = date.day + days;

  std::mktime(&t);

  date.year = t.tm_year + 1900;
  date.month = t.tm_mon + 1;
  date.day = t.tm_mday;
}

Date TargetDate::calculate(Year year) const
{
  Date date = calculation_method().calculate(year);
  shift(m_shift_amount, date);
  return date;
}

} // namespace pascha
