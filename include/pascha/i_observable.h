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

#ifndef PASCHA_I_OBSERVABLE_H
#define PASCHA_I_OBSERVABLE_H

#include <string_view>

#include "date.h"
#include "i_observer.h"

namespace pascha
{

class IObservable
{
 public:
  virtual ~IObservable() = default;
  virtual void addObserver(IObserver&) = 0;
  virtual void removeObserver(IObserver&) = 0;
  // Used to nofify date outputs from the model.
  virtual void notify(const Date&) const = 0;
  // Used to notify number of week updates from the model.
  virtual void notify(Weeks) const = 0;
  // Used to notify number of day updates from the model.
  virtual void notify(Days) const = 0;
  // Used to notify string messages, such as errors.
  virtual void notify(std::string_view) const = 0;
}; // class IObservable

} // namespace pascha

#endif // !PASCHA_I_OBSERVABLE_H
