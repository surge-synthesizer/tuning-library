# YOU DO NOT NEED TO USE THIS MAKEFILE TO USE THIS LIBRARY
#
# Tunings is a header-only library. This Makefile is just used
# to build tests and the standalone utilities
#

ifeq ($(OS),Windows_NT)
	CC = g++
	CCFLAGS = -Wall -Werror -std=c++14 -Iinclude -Ilibs/catch2
	BLD = build/windows
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CC = g++
		CCFLAGS = -Wall -Werror -std=c++14 -Iinclude -Ilibs/catch2
		BLD = build/linux
	endif
	ifeq ($(UNAME_S),Darwin)
		CC = clang++
		CCFLAGS = -Wall -Werror -std=c++14 -Iinclude -Ilibs/catch2
		BLD = build/macos
	endif
endif

TUNING=include/Tunings.h include/TuningsImpl.h

all:	$(BLD)/alltests $(BLD)/showmapping

runtests:	all
	$(BLD)/alltests

$(BLD)/alltests:	tests/alltests.cpp $(TUNING) $(BLD)
	$(CC) $(CCFLAGS) $< -o $@

$(BLD)/alltests_cov:	tests/alltests.cpp $(TUNING) $(BLD)
	$(CC) $(CCFLAGS) --coverage $< -o $@

$(BLD)/showmapping: commands/showmapping.cpp $(TUNING) $(BLD)
	$(CC) $(CCFLAGS) $< -o $@

$(BLD):
	mkdir -p $(BLD)

clean:
	rm -rf build

coverage:	$(BLD)/alltests_cov
	$(BLD)/alltests_cov
	mkdir -p $(BLD)/coverage
	mv alltests* $(BLD)/coverage
	cd $(BLD)/coverage && gcov alltests.gcna
