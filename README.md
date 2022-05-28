# About

The knight is a very unique chess piece, and this interactive program seeks to visualize the knight's patterns— where they are placed most often, and the respective win rates from those positions. Hover over a square on the interactive chess board to see data about the knight's placement on it.

All data is taken from the 121,332 games played on lichess.org during January 2013 as found on their open database (https://database.lichess.org/).

# Installation

## Windows
If `make` is not installed for windows yet, Install `chocolatey` package manager and run `choco install make` to install `make` for Windows

To manually compile and run, run `make` on the directory that contains the `Makefile`. To clear the `.class` files, run `make clean`.

Upon release there will be a `.exe` that can be downloaded, instead.

## Other Systems
I have not tested any of this code on MacOS/Linux, however it should work since this is written in Java. If the `Makefile` doesn't work like above, manually compile using `javac`.
