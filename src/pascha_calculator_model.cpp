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

#include "pascha/pascha_calculator_model.h"

#include "pascha/calendar_conversion.h"

#include <ctime>

namespace pascha
{

void PaschaCalculatorModel::setCalculationMethod(
    std::unique_ptr<ICalculationMethod> calculation_method)
{
  m_calculation_method = std::move(calculation_method);
}

void PaschaCalculatorModel::calculate(Year year) const
{
  using namespace std::literals; // for sv

  if (!m_calculation_method)
  {
    notify("No calculation method set!"sv);
    return;
  }

  try {
    Date date = m_calculation_method->calculate(year);
    notify(date);
  } catch (const std::overflow_error& e) {
    notify(e.what());
  }
} // PaschaCalculatorModel::calculate

void PaschaCalculatorModel::daysUntil(Year year) const
{
  using namespace std::literals; // for sv

  if (!m_calculation_method)
  {
    notify("No calculation method set!"sv);
    return;
  }

  try {
    CalcInt dateJdn{gregorianToJdn(m_calculation_method->calculate(year))};

    std::time_t t = std::time(0); // get time now
    std::tm* now = std::localtime(&t);
    Date nowDate{};
    nowDate.year = now->tm_year + 1900;
    nowDate.month = now->tm_mon + 1;
    nowDate.day = now->tm_mday;
    CalcInt nowJdn{gregorianToJdn(nowDate)};

    notify(Days{dateJdn - nowJdn});
  } catch (const std::overflow_error& e) {
    notify(e.what());
  }
} // PaschaCalculatorModel::daysUntil

void PaschaCalculatorModel::weeksBetween(
    Year year, std::unique_ptr<ICalculationMethod> method1,
    std::unique_ptr<ICalculationMethod> method2) const
{
  using namespace std::literals; // for sv

  if (!method1 || !method2)
  {
    notify("No calculation method set!"sv);
    return;
  }

  try {
    CalcInt date1Jdn{gregorianToJdn(method1->calculate(year))};
    CalcInt date2Jdn{gregorianToJdn(method2->calculate(year))};

    notify(Weeks{(date1Jdn - date2Jdn) / 7});
  } catch (const std::overflow_error& e) {
    notify(e.what());
  }
} // PaschaCalculatorModel::weeksBetween

void PaschaCalculatorModel::addObserver(IObserver& observer)
{
  m_observers.push_back(&observer);
} // PaschaCalculatorModel::addObserver

void PaschaCalculatorModel::removeObserver(IObserver& observer)
{
  std::erase(m_observers, &observer);
} // PaschaCalculatorModel::removeObserver

void PaschaCalculatorModel::notify(const Date& date) const
{
  for (IObserver* observer : m_observers) {
    observer->update(date);
  }
} // PaschaCalculatorModel::notify

void PaschaCalculatorModel::notify(Weeks weeks) const
{
  for (IObserver* observer : m_observers) {
    observer->update(weeks);
  }
} // PaschaCalculatorModel::notify

void PaschaCalculatorModel::notify(Days days) const
{
  for (IObserver* observer : m_observers) {
    observer->update(days);
  }
} // PaschaCalculatorModel::notify

void PaschaCalculatorModel::notify(std::string_view message) const
{
  for (IObserver* observer : m_observers) {
    observer->update(message);
  }
} // PaschaCalculatorModel::notify

} // namespace pascha
