// Copyright (C) 2024 Christopher Michael Mescher
//
// pascha-cli: A CLI Pascha (Easter) date calculator.
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

#include "cli_controller.h"
#include "cli_view.h"

#include "pascha/calculation_methods.h"
#include "pascha/output_calendars.h"
#include "pascha/output_options.h"
#include "pascha/target_dates.h"

namespace pascha
{

CliController::CliController(ICalculatorModel& model) : m_model{&model} {}

void CliController::calculate(const CalculationOptions& options) const
{
  using namespace std::literals; // for sv

  // Ensure the year is valid before continuing.
  if (!validateYear(options.year)) {
    m_model->notify("Invalid year"sv);
    return;
  }

  // Check the options for verbose output and Pascha name.
  bool verbose{false};
  std::string_view pascha_name{"Pascha"sv};

  for (auto option : options.options) {
    switch (option) {
      case (e_output_option::verbose): {
        verbose = true;
        break;
        case (e_output_option::easter): {
          pascha_name = "Easter"sv;
          break;
        }
      }
    }
  }

  for (auto target_output : options.target_outputs) {

    // Check if we are calculating weeks between two methods, before creating
    // the method object. If so, perform the calculation and continue.
    if (target_output == e_target_output::weeksBetween) {
      std::unique_ptr<ICalculationMethod> julian_method{
          new JulianCalculationMethod{}};
      std::unique_ptr<ICalculationMethod> gregorian_method{
          new GregorianCalculationMethod{}};
      std::cout << "Weeks between calendars: ";
      m_model->weeksBetween(options.year, std::move(julian_method),
                            std::move(gregorian_method));
      continue;
    }

    std::unique_ptr<ICalculationMethod> method{nullptr};

    // 1. get the calculation method from the options.
    // Default to Julian.
    switch (options.calculation_method) {
      case e_calculation_method::gregorian: {
        method = std::unique_ptr<ICalculationMethod>{
            new GregorianCalculationMethod{}};
        break;
      }
      default: {
        method =
            std::unique_ptr<ICalculationMethod>{new JulianCalculationMethod{}};
        break;
      }
    }

    // 2. Get the target date.
    // Default to Pascha.
    switch (target_output) {
      case e_target_output::daysUntil: {
        m_model->setCalculationMethod(std::move(method));
        if (verbose) std::cout << "Days until " << pascha_name << ": ";
        m_model->daysUntil(options.year);
        continue;
      }
      case e_target_output::meatfare: {
        method = std::unique_ptr<ICalculationMethod>{
            new Meatfare{std::move(method)}};
        if (verbose) std::cout << "Meatfare: ";
        break;
      }
      case e_target_output::cheesefare: {
        method = std::unique_ptr<ICalculationMethod>{
            new Cheesefare{std::move(method)}};
        if (verbose) std::cout << "Cheesefare: ";
        break;
      }
      case e_target_output::ashWednesday: {
        method = std::unique_ptr<ICalculationMethod>{
            new AshWednesday{std::move(method)}};
        if (verbose) std::cout << "Ash Wednesday: ";
        break;
      }
      case e_target_output::midfeastPentecost: {
        method = std::unique_ptr<ICalculationMethod>{
            new MidfeastPentecost{std::move(method)}};
        if (verbose) std::cout << "Midfeast of Pentecost: ";
        break;
      }
      case e_target_output::leavetakingPascha: {
        method = std::unique_ptr<ICalculationMethod>{
            new LeavetakingPascha{std::move(method)}};
        if (verbose) std::cout << "Leavetaking of Pascha: ";
        break;
      }
      case e_target_output::ascension: {
        method = std::unique_ptr<ICalculationMethod>{
            new Ascension{std::move(method)}};
        if (verbose) std::cout << "Ascension: ";
        break;
      }
      case e_target_output::pentecost: {
        method = std::unique_ptr<ICalculationMethod>{
            new Pentecost{std::move(method)}};
        if (verbose) std::cout << "Pentecost: ";
        break;
      }
      default: {
        // Pascha is calculated by default already.
        if (verbose) std::cout << pascha_name << ": ";
        break;
      }
    }

    // 3. Set the output calendar.
    // Default to Julian.
    switch (options.output_calendar) {
      case e_output_calendar::gregorian: {
        // Gregorian is used by default for calculations.
        break;
      }
      case e_output_calendar::rev_julian: {
        method = std::unique_ptr<ICalculationMethod>{
            new RevisedJulianOutputCalendar{std::move(method)}};
        break;
      }
      default: { // Julian
        method = std::unique_ptr<ICalculationMethod>{
            new JulianOutputCalendar{std::move(method)}};
        break;
      }
    }

    // 4. Apply the options.
    for (auto option : options.options) {
      switch (option) {
        case (e_output_option::byzantine): {
          method = std::unique_ptr<ICalculationMethod>{
              new ByzantineDate{std::move(method)}};
          break;
        }
      }
    }

    // 5. Set the calculation method and calculate.
    m_model->setCalculationMethod(std::move(method));
    m_model->calculate(options.year);
  }

} // CliController::calculate(const CalculationOptions&) const

void CliController::addView(IView& view)
{
  m_views.push_back(&view);
} // CliController::addView(IView&)

void CliController::removeView(IView& view)
{
  std::erase(m_views, &view);
} // CliController::removeView(IView&)

void CliController::start()
{
  for (auto* view : m_views) { view->createView(); }
} // CliController::start()

bool CliController::validateYear(const Year& year) const
{
  // TODO: add year validation
  return true;
} // CliController::validateYear(const Year&) const

} // namespace pascha
