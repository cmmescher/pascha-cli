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

#ifndef PASCHA_TARGET_DATES_H
#define PASCHA_TARGET_DATES_H

#include "target_date.h"

namespace pascha
{

class Meatfare : public TargetDate
{
 public:
  Meatfare(std::shared_ptr<ICalculationMethod> calculation_method)
    : TargetDate{calculation_method, -56} {}
  ~Meatfare() = default;
}; // class Meatfare

class Cheesefare : public TargetDate
{
 public:
  Cheesefare(std::shared_ptr<ICalculationMethod> calculation_method)
    : TargetDate{calculation_method, -49} {}
  ~Cheesefare() = default;
}; // class Cheesefare

class AshWednesday : public TargetDate
{
 public:
  AshWednesday(std::shared_ptr<ICalculationMethod> calculation_method)
    : TargetDate{calculation_method, -46} {}
  ~AshWednesday() = default;
}; // class AshWednesday

class MidfeastPentecost : public TargetDate
{
 public:
  MidfeastPentecost(std::shared_ptr<ICalculationMethod> calculation_method)
    : TargetDate{calculation_method, 24} {}
  ~MidfeastPentecost() = default;
}; // class MidfeastPentecost

class LeavetakingPascha : public TargetDate
{
 public:
  LeavetakingPascha(std::shared_ptr<ICalculationMethod> calculation_method)
    : TargetDate{calculation_method, 38} {}
  ~LeavetakingPascha() = default;
}; // class LeavetakingPascha

class Ascension : public TargetDate
{
 public:
  Ascension(std::shared_ptr<ICalculationMethod> calculation_method)
    : TargetDate{calculation_method, 39} {}
  ~Ascension() = default;
}; // class Ascension

class Pentecost : public TargetDate
{
 public:
  Pentecost(std::shared_ptr<ICalculationMethod> calculation_method)
    : TargetDate{calculation_method, 49} {}
  ~Pentecost() = default;
}; // class Pentecost

} // namespace pascha

#endif // !PASCHA_TARGET_DATES_H
