CFLAGS=-g -02 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local
//check this next line later to ex28 page
SOURCES=$(wildcard src/ ** / *.c src/ *.c)
OBJECTS=$(patsubst %,c, %.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))