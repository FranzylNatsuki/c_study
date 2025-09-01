# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Output program name
TARGET = program2

# Object files
OBJS = main.o datastructs.o

# Default rule (first target)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile .c into .o
main.o: main.c datastructs.h structure.h
	$(CC) $(CFLAGS) -c main.c

datastructs.o: datastructs.c datastructs.h structure.h
	$(CC) $(CFLAGS) -c datastructs.c

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)
