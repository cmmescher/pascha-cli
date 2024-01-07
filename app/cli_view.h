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

#ifndef PASCHA_CLIVIEW_H
#define PASCHA_CLIVIEW_H

#include "pascha/i_calculator_model.h"
#include "pascha/i_controller.h"
#include "pascha/i_view.h"

#include <string>

namespace pascha
{

class CliView : public IView
{
 public:
  CliView(IController& controller, ICalculatorModel& model, int argc,
          char* argv[], std::string_view date_separator = "-");
  ~CliView();

  // IView interface
  void createView() override;

  // IObserver interface (from IView)
  void update(const Date& date) override;
  void update(Weeks weeks) override;
  void update(Days days) override;
  void update(std::string_view message) override;

 private:
  IController& m_controller;
  ICalculatorModel& m_model;
  int m_argc;
  char** m_argv;
  std::string m_date_separator;
  bool m_suppress_year{false};
  bool m_suppress_pascha{false};
  bool m_chronological{false};
  Year m_year{};
  bool m_given_year{false};
  bool m_days_until{false};
  bool m_weeks_between{false};
  bool m_meatfare{false};
  bool m_cheesefare{false};
  bool m_ash_wednesday{false};
  bool m_midfeast{false};
  bool m_leavetaking{false};
  bool m_ascension{false};
  bool m_pentecost{false};

  CalculationOptions parseArgs(int argc, char* argv[]);
  void printUsage(char* argv[]) const;
};

namespace e_output_option
{

enum
{
  verbose = pascha::e_output_option::last,
  easter,
}; // enum

} // namespace e_output_option
//
} // namespace pascha
#endif // !PASCHA_CLIVIEW_H
