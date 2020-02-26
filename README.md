# Surge Synth Team Tuning Library

**WORK IN PROGRESS. PLEASE CHECK BACK IN A BIT**

In [Surge](https://surge-synthesizer.github.io), we added microtuning 
and spent a lot of time making sure our
SCL/KBM implementation was properly calibrated and available for C++
programs. We then added that same implementation to [dexed] through a copy.

But we realized we could make the functions available as standalone C++ header
only library and get three benefits.

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

## Building the comand line tools and test suite

Building the command line tools is really simple. 

1. Start a terminal
2. Type `make`

That's it! Now, for make to work, you need a unix-like environment on windows.
We followed exactly the VCV Rack dev setup and uses mysys, but really anything
which has a working g++ in your path will be fine.

The build ejects two assets. `alltests` which runs all the tests and `showmapping`

## Using the showmapping command

`showmapping` takes one or two arguments. It either takes an .scl file, in which
case it dumps the frequency table for that .scl file with midi note 60 being the
scale start tuned to 261hz, or it takes an .scl and .kbm file, in which case it
prints the entire internal tuning table for the combination.

## Bugs, Problems, etc

If you find bugs, please open a github issue and we will fix it right away!

If you have a non-bug problem, you can do the same or you can hop on the slack as
detailed at https://surge-synth-team.org/

If you would like to expand our test cases, we are always thrilled for you to do
so. Drop in a pull request.

If you choose to use the software in your synth, you can go right ahead of course.
That's the point of the MIT license! But if you want to let us know, again pop open
a github or drop in our slack. Always glad to hear from you.

Enjoy!
