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

#ifndef PASCHA_TARGET_DATE_H
#define PASCHA_TARGET_DATE_H

#include "calculation_method_decorator.h"
#include "date.h"
#include "i_calculation_method.h"

#include <memory>

namespace pascha
{

class TargetDate : public CalculationMethodDecorator
{
 public:
  TargetDate(std::shared_ptr<ICalculationMethod> calculation_method, int shift_amount)
    : CalculationMethodDecorator{calculation_method}, m_shift_amount{shift_amount} {}
  virtual ~TargetDate() = default;
  Date calculate(Year) const override;

 private:
  int m_shift_amount{};
  void shift(int, Date&) const;
}; // class TargetDate

} // namespace pascha

#endif // !PASCHA_TARGET_DATE_H
