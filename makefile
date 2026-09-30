# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -g

# Output binary
TARGET  = inverted_search

# Every .c file in the folder, and the matching .o files
SRCS    = $(wildcard *.c)
OBJS    = $(SRCS:.c=.o)

# Link all object files into the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each .c file; rebuild if main.h changes
%.o: %.c main.h
	$(CC) $(CFLAGS) -c $< -o $@

# Remove build output
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean