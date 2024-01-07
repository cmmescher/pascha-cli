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

#ifndef PASCHA_CALCULATION_METHODS_H
#define PASCHA_CALCULATION_METHODS_H

#include "i_calculation_method.h"

namespace pascha
{

class JulianCalculationMethod : public ICalculationMethod
{
 public:
  ~JulianCalculationMethod() = default;
  Date calculate(Year year) const override;
}; // class JulianCalculationMethod

class GregorianCalculationMethod : public ICalculationMethod
{
 public:
  ~GregorianCalculationMethod() = default;
  Date calculate(Year year) const override;
}; // class GregorianCalculationMethod

} // namespace pascha

#endif // !PASCHA_CALCULATION_METHODS_H
