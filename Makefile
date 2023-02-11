COMPILER = gcc

COMPILER_FLAGS  = -Og -Wall -DDEBUG

LIBRARY_FLAGS = -lraylib

BINARY = binary

SOURCE = main.c common.c player.c collisions.c timers.c

STATIC = false

all: $(SOURCE)
	$(COMPILER) $(COMPILER_FLAGS) -o $(BINARY) $(SOURCE) $(LIBRARY_FLAGS)

static: $(SOURCE)
	$(COMPILER) $(COMPILER_FLAGS) -static -o $(BINARY) $(SOURCE)
