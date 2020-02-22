# YOU DO NOT NEED TO USE THIS MAKEFILE TO USE THIS LIBRARY
#
# Tunings is a header-only library. This Makefile is just used
# to build tests and the standalone utilities
#

build/alltests:	tests/alltests.cpp include/Tunings.h include/TuningsImpl.h build
	clang++ -Wall -Werror -std=c++14 -Iinclude -Ilibs/catch2 tests/alltests.cpp -o build/alltests

build:
	mkdir build

clean:
	rm -rf build


