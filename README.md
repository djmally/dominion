## PREREQUISITES ##

Dominion depends on `cmake-2.6` and `clang 3.3.0` or later, as well as
`python-2.7.8` or later. It also requires the python package `requests`,
which can be installed via `pip`. It will not build on Windows, and likely will
not build on OSX either, thought this has not been tested.

## BUILD INSTRUCTIONS ##

Simply type `make`. Assuming you have at least CMake 2.6 installed,
everything should go smoothly. No extra libraries need to be installed
or linked to build the main executable; `gtest` is required to build
`mainTest`.

## EXECUTION ##

After building, the resulting binary named `dominion` will be placed into
the `bin` directory. Simply run `./bin/dominion` to start the game.

## HOW 2 USE ##

Once the game is running, you'll be presented with a list of choices.
It's all pretty self-explanatory, but running the demo game will demonstrate
our features the best.

As for grading, everything is fair game except for mainTest.cpp, which contains
our unit tests and isn't really relevant to the overall functionality of our
code. A lot of stuff happens on the back-end of our program that is not really
visible to the end-user, so it'd definitely be worthwhile to look through.
Specifically, RandUtils and JsonRPC are very important, as they're used in
our shuffling algorithms, but aren't visible at all when the game is played.
CardLookup and GameState are directly interacted with, but also contain a lot
of behind-the-scenes state manipulation that's worth looking at. The other files
in the project are also important to look at, but are in general shorter and
mechanically less interesting.

## DIRECTORY STRUCTURE ##

`src` contains all source code, as you might expect. `src/cpp` contains all C++
source files, and `src/python` contains all Python source files. `test` just
contains the automated test input, and can be ignored.

## DIVISION OF LABOR ##

David: Unit Testing, Game Logic, Random.org Calling
Richard: Input sanitization, Action/Victory Card Refactoring
Both: Overall design specifications

## UNIT TESTING ##

Unit tests are located in `src/cpp/mainTest.cpp` and can be built by
commenting/uncommenting a line in the CMakeLists.txt file. If you run
`make test`, all tests will automatically be run. If you execute the
binary yourself, you can run the tests interactively. However, this won't work
on ENIAC, as gtest isn't installed; if you get errors about failing to link
the shared library lgtest, make sure that CMake is building in release mode
(this should be the default).

