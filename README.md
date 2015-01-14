## Introduction ##

This repository contains a command-line, C++ implementation of the card
game Dominion, created by Donald X. Vaccarino. We (djmally & rrobertsdev)
created this as a final project for CIS 190: C++ at the University of
Pennsylvania; currently in the process of migrating to C++14.

## Prerequisites ##

Dominion depends on `cmake-2.6` and `clang 3.3.0` or later, as well as
`python-2.7.8` or later. It also requires the python package `requests`,
which can be installed via `pip`. It will not build on Windows, and likely will
not build on OSX either, though this has not been tested.

## Build Instructions ##

Simply type `make`. Assuming you have at least CMake 2.6 installed,
everything should go smoothly. No extra libraries need to be installed
or linked to build the main executable; `gtest` is required to build
`mainTest`.

## Execution ##

After building, the resulting binary named `dominion` will be placed into
the `bin` directory. Simply run `./bin/dominion` to start the game.

## Directory Structure ##

`src` contains all source code, as you might expect. `src/cpp` contains all C++
source files, and `src/python` contains all Python source files. `test` just
contains the automated test input, and can be ignored.

## Unit Testing ##

Unit tests are located in `src/cpp/mainTest.cpp` and can be built by
commenting/uncommenting a line in the CMakeLists.txt file. If you run
`make test`, all tests will automatically be run. If you execute the
binary yourself, you can run the tests interactively. However, this won't work
on ENIAC, as gtest isn't installed; if you get errors about failing to link
the shared library lgtest, make sure that CMake is building in release mode
(this should be the default).

