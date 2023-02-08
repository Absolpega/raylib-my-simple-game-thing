COMPILER = gcc

COMPILER_FLAGS  = -Og -Wall -DDEBUG

LIBRARY_FLAGS = -lraylib

BINARY = binary

SOURCE = main.c common.c player.c collisions.c

all: $(SOURCE)
	$(COMPILER) $(COMPILER_FLAGS) -o $(BINARY) $(SOURCE) $(LIBRARY_FLAGS)
