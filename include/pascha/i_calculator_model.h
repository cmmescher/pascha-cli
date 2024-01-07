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

#ifndef PASCHA_I_CALCULATOR_MODEL_H
#define PASCHA_I_CALCULATOR_MODEL_H

#include "i_calculation_method.h"
#include "i_observable.h"
#include "typedefs.h"

#include <iostream>
#include <memory>

namespace pascha
{

class ICalculatorModel : public IObservable
{
 public:
  virtual ~ICalculatorModel() = default;
  virtual void setCalculationMethod(std::unique_ptr<ICalculationMethod>) = 0;
  virtual void calculate(Year) const = 0;
  // Calculate the number of days until Pascha in the given year.
  virtual void daysUntil(Year) const = 0;
  // Calculate the number of days between the dates calculated by the two
  // methods, for the given year. Typically this will be between the Julian and
  // Gregorian methods for calculating Pascha.
  virtual void weeksBetween(Year, std::unique_ptr<ICalculationMethod>,
                            std::unique_ptr<ICalculationMethod>) const = 0;
}; // class ICalculatorModel

} // namespace pascha

#endif // !PASCHA_I_CALCULATOR_MODEL_H
