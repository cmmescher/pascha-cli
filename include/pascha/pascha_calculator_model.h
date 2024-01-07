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

#ifndef PASCHA_PASCHA_CALCULATOR_MODEL_H
#define PASCHA_PASCHA_CALCULATOR_MODEL_H

#include "i_calculator_model.h"
#include <vector>
#include <memory>

namespace pascha
{

class PaschaCalculatorModel : public ICalculatorModel
{
 public:
  PaschaCalculatorModel() = default;
  PaschaCalculatorModel(const PaschaCalculatorModel&) = delete;
  PaschaCalculatorModel(PaschaCalculatorModel&&) = delete;
  PaschaCalculatorModel& operator=(const PaschaCalculatorModel&) = delete;
  PaschaCalculatorModel& operator=(PaschaCalculatorModel&&) = delete;
  virtual ~PaschaCalculatorModel() = default;

  virtual void
      setCalculationMethod(std::unique_ptr<ICalculationMethod>) override;
  virtual void calculate(Year) const override;
  virtual void daysUntil(Year) const override;
  virtual void weeksBetween(Year, std::unique_ptr<ICalculationMethod>,
                            std::unique_ptr<ICalculationMethod>) const override;
  virtual void addObserver(IObserver&) override;
  virtual void removeObserver(IObserver&) override;
  virtual void notify(const Date&) const override;
  virtual void notify(Weeks) const override;
  virtual void notify(Days) const override;
  virtual void notify(std::string_view) const override;

 private:
  std::unique_ptr<ICalculationMethod> m_calculation_method{nullptr};
  std::vector<IObserver*> m_observers{};
}; // class PaschaCalculatorModel

} // namespace pascha
#endif // !PASCHA_PASCHA_CALCULATOR_MODEL_H
