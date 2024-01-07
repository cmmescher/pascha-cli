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

#ifndef PASCHA_I_CONTROLLER_H
#define PASCHA_I_CONTROLLER_H

#include "calculation_options.h"
#include "i_calculator_model.h"
#include "i_view.h"

namespace pascha
{

class IController
{
 public:
  virtual ~IController() = default;
  // Calculate the output using the model with the given options.
  virtual void calculate(const CalculationOptions& options) const = 0;
  // Add a view to the controller.
  virtual void addView(IView&) = 0;
  // Remove a view from the controller.
  virtual void removeView(IView&) = 0;
  // Start the view.
  virtual void start() = 0;
}; // class IController

} // namespace pascha

#endif // !PASCHA_I_CONTROLLER_H
