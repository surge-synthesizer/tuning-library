# YOU DO NOT NEED TO USE THIS MAKEFILE TO USE THIS LIBRARY
#
# Tunings is a header-only library. This Makefile is just used
# to build tests and the standalone utilities
#

all:	build/alltests build/showmapping

build/alltests:	tests/alltests.cpp include/Tunings.h include/TuningsImpl.h build
	clang++ -Wall -Werror -std=c++14 -Iinclude -Ilibs/catch2 tests/alltests.cpp -o build/alltests

build/showmapping: commands/showmapping.cpp include/Tunings.h include/TuningsImpl.h build
	clang++ -Wall -Werror -std=c++14 -Iinclude -Ilibs/catch2 commands/showmapping.cpp -o build/showmapping

build:
	mkdir build

clean:
	rm -rf build


