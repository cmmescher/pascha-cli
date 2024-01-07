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

#ifndef PASCHA_I_OBSERVER_H
#define PASCHA_I_OBSERVER_H

#include "date.h"

#include <string_view>

namespace pascha
{

class IObserver
{
 public:
  virtual ~IObserver() = default;
  // Used to receive date outputs (e.g. from the model).
  virtual void update(const Date&) = 0;
  // Used to receive number of week updates (e.g. from the model).
  virtual void update(Weeks) = 0;
  // Used to receive number of day updates (e.g. from the model).
  virtual void update(Days) = 0;
  // Used to receive string messages, such as errors.
  virtual void update(std::string_view) = 0;
}; // class IObserver

} // namespace pascha

#endif // !PASCHA_I_OBSERVER_H_20221215
