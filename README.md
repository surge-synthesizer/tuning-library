# Surge Synth Team Tuning Library

In [Surge](https://surge-synthesizer.github.io), we added microtuning 
and spent a lot of time making sure our
SCL/KBM implementation was properly callibrated and available for C++
programs. We then added that same implmentation to [dexed] through a copy.

But we realized we could make the functions available as standalone C++ header
only library and get three benefits

1. Share more code between Surge and our Dexed fork
2. Make the code available to other soft synths where we or others may add microtuning
3. Have a set of standalone comand line utilities and well documented tests 

So we took the code and re-factored it here under an MIT license.

Although Surge and Dexed are GPL3, the copyright holders and authors of the original
Surge microtuning implementation (and only that implementation) were happy to relicense.

## Using the library in your C++ project

The C++ library is a standalone header only C++-11 library. There are a variety of ways
to use it in your project but our approach is generally:

1. Make this github repo a submodule of your project
2. Add the "include/" directory to your compiler include path
3. `#include "Tunings.h"`

The code is organized such that Tunings.h is the API and TuningsImpl.h is the header with more 
involved implementation bodies. Tunings.h includes TuningsImpl.h automatically.

## Using the command line tools

## Building the comand line tools and test suite


