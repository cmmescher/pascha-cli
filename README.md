# Pascha CLI
Pascha CLI is a simple CLI program to calculate and display the date of Pascha
(Easter). It uses the same interface as the ["pascha" shell script](https://gitlab.com/cmmescher/pascha), but uses the C++ library "pascha-lib" from [Pascha GUI](https://gitlab.com/cmmescher/pascha-gui) for calculation.

## Installation

``` sh
git clone https://gitlab.com/cmmescher/pascha-cli
cd pascha-cli
cmake -S . -B build
cmake --build build
cmake --install build
```

For users of **Arch**-based distributions, Pascha CLI is available on the AUR as [pascha-cli-git](https://aur.archlinux.org/packages/pascha-cli-git) or [pascha-gui-bin](https://aur.archlinux.org/packages/pascha-cli-bin).

You can cross-compile for Windows on a GNU+Linux system using mingw and the following commands:
```sh
cmake -S . -B buildwin -DCMAKE_TOOLCHAIN_FILE=tc-mingw.cmake
cmake --build buildwin
```
## Uninstallation

From within the `pascha-cli` git directory run:

```sh
cmake --build build --target uninstall
```

## Usage

`pascha` prints out the date of Pascha (Easter). By default it prints the date
of Pascha for the current year, calculated and displayed using the Julian
calendar. It has no required arguments or options.

If the `-R` option is given then the date will be displayed using the Revised
Julian calendar (which is the same as the Gregorian until 28 February 2800)
instead, but still calculated using the Julian calendar. With `-g` the date will
be both calculated and displayed using the Gregorian calendar. The `-j` option
has the default behavior, using the Julian calendar both for display and
calculation.

`pascha` will calculate the date of Pascha using the calendar specified by `-j`
or `-g` which use the Julian or Gregorian calendars respectively. If both or
neither are given, then `pascha` will default to using the Julian calendar.

`pascha` will display the calculated date using the calendar specified by `-J`,
`-R`, or `-G` which use the Julian, Revised Julian, or Gregorian calendars
respectively. If more than one is given, then the Julian calendar will take
precedence, followed by the Revised Julian. If none is given, then `pascha` will
default to using the Julian calendar for display when the Julian calendar is
used for calculation and the Gregorian calendar for display when the Gregorian
calendar is used for calculation.

By default, `pascha` will print out only the month and the day, if no year is
specified. A year can be specified using `-y`. When specified the date of Pascha
will be calculated for the given year, otherwise the current year is used. When
a year is given with `-y` the year will be printed out as well, unless the `-s`
option is used. `pascha` can also use the Byzantine Calendar's Anno Mundi style
year if given the `-b` option. In this case `pascha` will also print the year by
default, even if `-y` is not used.

`pascha` can also print out certain other dates, relative to Pascha for a given
year. These are Meatfare (`-m`), Cheesefare (`-c`), Ash Wednesday (`-a`), the
Midfeast of Pentecost (`-M`), the Leavetaking of Pascha (`-l`), the Ascension of
our Lord (`-A`), and Pentecost (`-p`). By default these dates are printed out
after the date of Pascha, but printing the date of Pascha can be surpressed with
`-x`. The dates can also be printed in chronological order, rather than with
Pascha first, using `-X`.

`pascha` can print the number of days until Pascha (`-d`) and the number of weeks
between the Julian and Gregorian dates for Pascha (`-D`).

If given the `-v` or `-V` options, `pascha` will print out the name associated
with each date or calculation. The `-V` option is the same as `-v`, except it
uses the name "Easter" rather than "Pascha."

`pascha` can also use a custom separator for date output with the `-S`
option. By default `pascha` will use `-` as a separator.

Please see `man pascha` for more information.

## Compatibility

Pascha CLI has been tested on GNU+Linux, FreeBSD, OpenBSD, and Windows systems. It may work on MacOS or others, but it may not. If you do get it to run on
any of these, please let me know, so this can be updated.

## Version

- *v2.1*
    - Fixes bug in calculating the days until Pascha when no year is specified and Pascha has already passed in the current year.
    - Fixes bug where the Gregorian calendar is not used for output by default when no output calendar is specified and the Gregorian calculation method is used.

- *v2.0*
    - First released publicly on the O.S. Feast of the Nativity 7532 (2023) (January 7, 2024 N.S.).
    - Version begins with v2.0 to parallel the interface update in [pascha v2.0](https://gitlab.com/cmmescher/pascha).

## Author

Written by Christopher Michael Mescher originally in 2024.

## Copyright and License

Copyright © 2022, 2024 Christopher Michael Mescher.

License [GPLv3+](https://gnu.org/licenses/gpl.html).

## Project status

The project is mostly complete. No new features are planned, but bugs can be
reported to `echo \<pascha-mescher+faith\>|sed s/\+/./g\;s/\-/@/` and they will
be worked on.

## Changelog
