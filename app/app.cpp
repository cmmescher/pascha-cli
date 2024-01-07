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

#include "app.h"

#include "cli_controller.h"
#include "pascha/pascha_calculator_model.h"

namespace pascha
{

App::App(int argc, char* argv[])
    : m_model{std::make_unique<PaschaCalculatorModel>()},
      m_controller{std::make_unique<CliController>(*m_model)},
      m_view{*m_controller, *m_model, argc, argv}
{
}

int App::Run()
{
  m_view.createView();
  return EXIT_SUCCESS;
} // App::OnInit()

} // namespace pascha

int main(int argc, char* argv[])
{
  pascha::App app{argc, argv};
  return app.Run();
} // main()
