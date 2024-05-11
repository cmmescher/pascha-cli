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

#include "cli_view.h"
#include "pascha/calculation_options.h"

#include <getopt.h>
#include <iomanip>
#include <string>
#include <string_view>

namespace pascha
{
CliView::CliView(IController& controller, ICalculatorModel& model, int argc,
                 char* argv[], std::string_view date_separator)
    : m_controller{controller},
      m_model{model},
      m_argc{argc},
      m_argv{argv},
      m_date_separator{date_separator}
{
  m_model.addObserver(*this);
  // m_controller.addView(*this);
} // CliView::CliView()

CliView::~CliView()
{
  m_model.removeObserver(*this);
  // m_controller.removeView(*this);
} // CliView::~CliView()

void CliView::createView()
{
  CalculationOptions options = parseArgs(m_argc, m_argv);
  m_controller.calculate(options);

} // CliView::createView()

void CliView::update(const Date& date)
{
  std::cout << std::setfill('0') << std::setw(2) << date.month
            << m_date_separator << std::setfill('0') << std::setw(2)
            << date.day;
  if (!m_suppress_year && m_given_year) {
    std::cout << m_date_separator << date.year;
  }
  std::cout << '\n';
} // CliView::update(const Date&)

void CliView::update(Weeks weeks)
{
  std::cout << weeks.value << '\n';
} // CliView::update(Weeks)

void CliView::update(Days days)
{
  std::cout << days.value << '\n';
} // CliView::update(Days)

void CliView::update(std::string_view message)
{
  std::cerr << "Error: " << message << '\n';
} // CliView::update(std::string_view)

CalculationOptions CliView::parseArgs(int argc, char* argv[])
{
  int opt{};
  CalculationOptions options{};
  m_year = -9223372036854775807; // indicates no year given

  while ((opt = getopt(argc, argv, ":jgJRGbsdDmcaMlApxXvVs:y:h")) != -1) {
    switch (opt) {
      case 'j':
        options.calculation_method = e_calculation_method::julian;
        break;
      case 'g':
        options.calculation_method = e_calculation_method::gregorian;
        break;
      case 'J': options.output_calendar = e_output_calendar::julian; break;
      case 'R': options.output_calendar = e_output_calendar::rev_julian; break;
      case 'G': options.output_calendar = e_output_calendar::gregorian; break;
      case 'b': options.options.push_back(e_output_option::byzantine); break;
      case 's': m_suppress_year = true; break;
      case 'd': m_days_until = true; break;
      case 'D': m_weeks_between = true; break;
      case 'm': m_meatfare = true; break;
      case 'c': m_cheesefare = true; break;
      case 'a': m_ash_wednesday = true; break;
      case 'M': m_midfeast = true; break;
      case 'l': m_leavetaking = true; break;
      case 'A': m_ascension = true; break;
      case 'p': m_pentecost = true; break;
      case 'x': m_suppress_pascha = true; break;
      case 'X':
        m_chronological = true;
        m_suppress_pascha = true;
        break;
      case 'v': options.options.push_back(e_output_option::verbose); break;
      case 'V':
        options.options.push_back(e_output_option::verbose);
        options.options.push_back(e_output_option::easter);
        break;
      case 'S': m_date_separator = optarg; break;
      case 'y':
        try {
          m_year = Year{std::stoi(optarg)};
          m_given_year = true;
        } catch (std::invalid_argument& e) {
          std::cerr << "Error: Invalid year: " << optarg << '\n';
          printUsage(argv);
          exit(EXIT_FAILURE);
        }
        break;
      case 'h': printUsage(argv); exit(EXIT_SUCCESS);
      case ':': printUsage(argv); exit(EXIT_FAILURE);
      case '?': printUsage(argv); exit(EXIT_FAILURE);
      default: printUsage(argv); exit(EXIT_FAILURE);
    }
  }

  if (!m_suppress_pascha) {
    options.target_outputs.push_back(e_target_output::pascha);
  }
  if (m_days_until) {
    options.target_outputs.push_back(e_target_output::daysUntil);
  }
  if (m_weeks_between) {
    options.target_outputs.push_back(e_target_output::weeksBetween);
  }
  if (m_meatfare) {
    options.target_outputs.push_back(e_target_output::meatfare);
  }
  if (m_cheesefare) {
    options.target_outputs.push_back(e_target_output::cheesefare);
  }
  if (m_ash_wednesday) {
    options.target_outputs.push_back(e_target_output::ashWednesday);
  }
  if (m_chronological) {
    options.target_outputs.push_back(e_target_output::pascha);
  }
  if (m_midfeast) {
    options.target_outputs.push_back(e_target_output::midfeastPentecost);
  }
  if (m_leavetaking) {
    options.target_outputs.push_back(e_target_output::leavetakingPascha);
  }
  if (m_ascension) {
    options.target_outputs.push_back(e_target_output::ascension);
  }
  if (m_pentecost) {
    options.target_outputs.push_back(e_target_output::pentecost);
  }

  options.year = m_year;
  return options;
} // parseArgs(int, char*[])

void CliView::printUsage(char* argv[]) const
{
  std::cout
      << "Usage: " << argv[0]
      << " [-j|-g] [-J|-R|-G] [-bsdDmcaMlApxXvV] [-s <SEP>] [-y <YEAR>]\n";
} // printUsage(char*[])

} // namespace pascha
