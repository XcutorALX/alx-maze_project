# Define compiler and compiler flags
CC = gcc
CFLAGS = -I./include $(shell sdl2-config --cflags)
LDFLAGS = -lm $(shell sdl2-config --libs)

# Define the target executable
TARGET = build/maze

# Define the source and object files
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=build/%.o)

# Rule to build the target
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

# Rule to build the object files
build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean the build directory
clean:
	rm -f build/*.o $(TARGET)

test:
	gcc -Iinclude Test/*.c -o test -lm -g
