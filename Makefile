COMPILER = gcc

COMPILER_FLAGS  = -Og -Wall

LIBRARY_FLAGS = -lraylib

BINARY = binary

SOURCE = main.c custom.c player.c collisions.c

all: $(SOURCE)
	$(COMPILER) $(COMPILER_FLAGS) -o $(BINARY) $(SOURCE) $(LIBRARY_FLAGS)