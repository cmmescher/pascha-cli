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

#include "pascha/calendar_conversion.h"

#include <stdexcept>

// Helper functions for conversion
namespace
{
using namespace pascha;

// Overflow constants
// These are only valid when CalcInt = std::int64_t
constexpr CalcInt kGregorianMaxYear{25252734927761841};
constexpr CalcInt kJulianMaxYear{25252216391110347};
constexpr CalcInt kRevJulianMaxYear{25252754133231976};
constexpr CalcInt kRevJulianMaxJdn{2305837553489651559};

// To prevent invalid dates with Byzantine Calendar
constexpr CalcInt kGregorianMinYear{-5508};
constexpr CalcInt kJulianMinYear{-5508};
constexpr CalcInt kRevJulianMinYear{-5508};

// The following functions calculate the Julian Day Number (JDN) from a given
// calendar date. This is used as a fixed point to convert between calendars.

// gregorianToJdn is in the pascha namespace below.

CalcInt julianToJdn(const Date& date)
{
  if (date.year > kJulianMaxYear || date.year < kJulianMinYear) {
    throw std::overflow_error("Julian year out of range");
  }

  CalcInt y = date.year;
  CalcInt m = date.month;
  CalcInt jdn{};

  // Calculate the number of 4 year cycles
  CalcInt cycles{};
  if (y < 0) {
    cycles = y / 4 - 1;
    if (y % 4 == 0) { ++cycles; }
    y = (4 - (-1 * y % 4)) % 4;
  } else {
    cycles = y / 4;
    y = y % 4;
  }

  // Treat months prior to leap day as if they were in the previous year
  if (m < 3) {
    m += 12;
    --y;
  }

  // Add contribution from number of leap years
  if (y < 0 && y % 4 != 0) {
    jdn = 365 * y + (y / 4 - 1);
  } else {
    jdn = 365 * y + (y / 4);
  }

  // Add contribution from number of months and current day in month
  jdn = jdn + 153 * (m + 1) / 5 + date.day - 123;

  // Add base contribution for days prior to 1/1/1
  // and the total number of unaccounted cycles
  jdn = jdn + 1721118 + 1461 * cycles;

  return jdn;
} // julianToJdn

CalcInt revJulianToJdn(const Date& date)
{
  if (date.year > kRevJulianMaxYear || date.year < kRevJulianMinYear) {
    throw std::overflow_error("Revised Julian year out of range");
  }

  CalcInt y = date.year;
  CalcInt m = date.month;
  CalcInt jdn{};

  // Treat months prior to leap day as if they were in the previous year
  if (m < 3) {
    m += 12;
    --y;
  }

  // Add contribution from number of leap years
  if (y < 0 && y % 4 != 0) {
    jdn = 365 * y + (y / 4 - 1);
  } else {
    jdn = 365 * y + (y / 4);
  }

  // Skip leap years divisible by 100
  CalcInt jdn1{y / 100};
  if (y < 0 && y % 100 != 0) { --jdn1; }

  // Retain leap year when 200 remainder after dividing by 900
  CalcInt jdn2i{y + 300};
  CalcInt jdn2{jdn2i / 900};
  if (jdn2i < 0 && jdn2i % 900 != 0) { --jdn2; }

  // Retain leap year when 600 remainder after dividing by 900
  CalcInt jdn3i{y + 700};
  CalcInt jdn3{jdn3i / 900};
  if (jdn3i < 0 && jdn3i % 900 != 0) { --jdn3; }

  // Add contribution from previous skipped and retained leap years
  jdn = jdn - jdn1 + jdn2 + jdn3;

  // Add contribution from number of months and current day in month
  CalcInt jdn4i{153 * (m + 1)};
  CalcInt jdn4{jdn4i / 5};
  if (jdn4i < 0 && jdn4i % 5 != 0) { --jdn4; }
  jdn = jdn + jdn4 + date.day - 123;

  // Add base contribution for days prior to 1/1/1
  jdn = jdn + 1721120;

  return jdn;
} // revJulianToJdn

// The following functions calculate the calendar date from a given Julian Day
// Number (JDN). They store it in the given Date reference

void jdnToGregorian(CalcInt jdn, Date& date)
{
  CalcInt year{};
  CalcInt month{};
  CalcInt day{};

  // Remove contribution prior to 1/1/1
  day = jdn - 1721120;

  // Calculate the number of cycles of 400 years
  // and remove their contribution
  CalcInt cycles{};
  if (day < 0) {
    cycles = day / 146097 - 1;
    if (day % 146097 == 0) { ++cycles; }
    day = (146097 - (-1 * day % 146097)) % 146097;
  } else {
    cycles = day / 146097;
    day = day % 146097;
  }

  // Adjusting removal of cycles due to rounding
  CalcInt a{(4 * day + 3) / 146097};
  day = day + a - a / 4;

  // Calculating number of years contained in current day value
  // and removing their contribution from day
  year = (4 * day + 3) / 1461;
  day = day - 1461 * year / 4;

  // Calculating number of months contained in current day value
  // and removing their contribution from day
  month = (5 * day + 2) / 153;
  day = day - (153 * month + 2) / 5;
  ++day;

  // Adjusting month and year values to have year start in january
  // rather than divided pre- and post-leap day
  month += 3;
  if (month > 12) {
    month -= 12;
    ++year;
  }

  // Adding contribution of 400 year cycles to the year
  year = year + 400 * cycles;

  // Setting output
  date.year = year;
  date.month = month;
  date.day = day;
} // jdnToGregorian

void jdnToJulian(CalcInt jdn, Date& date)
{
  CalcInt year{};
  CalcInt month{};
  CalcInt day{};

  // Remove contribution prior to 1/1/1
  day = jdn - 1721118;

  // Calculate the number of cycles of 4 years
  // and remove their contribution
  CalcInt cycles{};
  if (day < 0) {
    cycles = day / 1461 - 1;
    if (day % 1461 == 0) { ++cycles; }
    day = (1461 - (-1 * day % 1461)) % 1461;
  } else {
    cycles = day / 1461;
    day = day % 1461;
  }

  // Calculating number of years contained in current day value
  // and removing their contribution from day
  year = (4 * day + 3) / 1461;
  day = day - 1461 * year / 4;

  // Calculating number of months contained in current day value
  // and removing their contribution from day
  month = (5 * day + 2) / 153;
  day = day - (153 * month + 2) / 5;
  ++day;

  // Adjusting month and year values to have year start in january
  // rather than divided pre- and post-leap day
  month += 3;
  if (month > 12) {
    month -= 12;
    ++year;
  }

  // Adding contribution of 4 year cycles to the year
  year = year + 4 * cycles;

  // Setting output
  date.year = year;
  date.month = month;
  date.day = day;
} // jdnToJulian

void jdnToRevJulian(CalcInt jdn, Date& date)
{
  if (jdn > kRevJulianMaxJdn) {
    throw std::overflow_error("JDN out of range to convert to Revised Julian");
  }

  CalcInt year{};
  CalcInt month{};
  CalcInt day{};

  // Remove contribution prior to 1/1/1
  day = jdn - 1721120;

  // Adjustments based on Revised Julian skipped leap years
  // Base number of leap days
  CalcInt ai{9 * day + 2};
  CalcInt a{ai / 328718};
  if (ai < 0 && ai % 328718 != 0) { --a; }

  // Account for including years with remainder of 200 after division by 900
  CalcInt a2{(a + 3) / 9};
  if (a < -3 && a % 9 != -3) { --a2; }

  // Account for including years with remainder of 600 after division by 900
  CalcInt a3{(a + 7) / 9};
  if (a < -7 && a % 9 != -7) { --a3; }
  day = day + a - a2 - a3;

  // Calculating number of years contained in current day value
  // and removing their contribution from day
  CalcInt yeari{4 * day + 3};
  year = yeari / 1461;
  if (yeari < 0 && yeari % 1461 != 0) { --year; }
  CalcInt y{1461 * year / 4};
  if (year < 0 && 1461 * year % 4 != 0) { --y; }
  day = day - y;

  // Calculating number of months contained in current day value
  // and removing their contribution from day
  CalcInt monthi{5 * day + 2};
  month = monthi / 153;
  if (monthi < 0 && monthi % 153 != 0) { --month; }
  CalcInt day2i{153 * month + 2};
  CalcInt day2{day2i / 5};
  if (day2i < 0 && day2i % 5 != 0) { --day2; }
  day = day - day2 + 1;

  // Adjusting month and year values to have year start in january
  // rather than divided pre- and post-leap day
  month += 3;
  if (month > 12) {
    month -= 12;
    ++year;
  }

  // Setting output
  date.year = year;
  date.month = month;
  date.day = day;
} // jdnToRevJulian

} // anonymous namespace

namespace pascha
{

// Calculate the Julian Day Number (JDN) from a given calendar date. This is
// used as a fixed point to convert between calendars.
CalcInt gregorianToJdn(const Date& date)
{
  if (date.year > kGregorianMaxYear || date.year < kGregorianMinYear) {
    throw std::overflow_error("Gregorian year out of range");
  }

  CalcInt y = date.year;
  CalcInt m = date.month;
  CalcInt jdn{};

  // Calculate the number of 400 year cycles
  CalcInt cycles{};
  if (y < 0) {
    cycles = y / 400 - 1;
    if (y % 400 == 0) { ++cycles; }
    y = (400 - (-1 * y % 400)) % 400;
  } else {
    cycles = y / 400;
    y = y % 400;
  }

  // Treat months prior to leap day as if they were in the previous year
  if (m < 3) {
    m += 12;
    --y;
  }

  // Add contribution from number of leap years
  if (y < 0 && y % 4 != 0) {
    jdn = 365 * y + (y / 4 - 1);
  } else {
    jdn = 365 * y + (y / 4);
  }

  // Add contribution from number of months and current day in month
  jdn = jdn + 153 * (m + 1) / 5 + date.day - 123;

  // Adjustments for leap year differences between Julian and Gregorian
  // calendars (leap years skipped when divisible by 100 but not by 400)
  // Adjustments when year is negative (casues off by one problem with modulo
  // for leap year checks)
  if (y < 0) {
    if (y % 100 != 0) {
      if (y % 400 != 0) {
        jdn = jdn - (y / 100 - 1) + (y / 400 - 1);
      } else {
        jdn = jdn - (y / 100 - 1) + (y / 400);
      }
    } else {
      if (y % 400 != 0) {
        jdn = jdn - (y / 100) + (y / 400 - 1);
      } else {
        jdn = jdn - (y / 100) + (y / 400);
      }
    }
  } else {
    jdn = jdn - y / 100 + y / 400;
  }

  // Add base contribution for days prior to 1/1/1
  // and the total number of unaccounted cycles
  jdn = jdn + 1721120 + 146097 * cycles;

  return jdn;

} // gregorianToJdn

Date gregorianToJulian(const Date& date)
{
  Date julian_date{};
  std::int64_t jdn = gregorianToJdn(date);
  jdnToJulian(jdn, julian_date);
  return julian_date;
} // gregorianToJulian

Date julianToGregorian(const Date& date)
{
  Date gregorian_date{};
  std::int64_t jdn = julianToJdn(date);
  jdnToGregorian(jdn, gregorian_date);
  return gregorian_date;
} // julianToGregorian

Date gregorianToRevJulian(const Date& date)
{
  Date rev_julian_date{};
  std::int64_t jdn = gregorianToJdn(date);
  jdnToRevJulian(jdn, rev_julian_date);
  return rev_julian_date;
} // gregorianToRevJulian

Date revJulianToGregorian(const Date& date)
{
  Date gregorian_date{};
  std::int64_t jdn = revJulianToJdn(date);
  jdnToGregorian(jdn, gregorian_date);
  return gregorian_date;
} // revJulianToGregorian

} // namespace pascha
