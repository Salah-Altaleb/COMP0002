# Makefile for Stage1 project

# Variables
CC = gcc
CFLAGS = -Wall -Wextra
TARGET = main
SOURCES = main.c maze.c robot.c graphics.c

# Default target (what runs when you type just 'make')
all: $(TARGET)

# Compile the program
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

# Run the program with the Java visualizer
run: $(TARGET)
	.\$(TARGET).exe | java -jar drawapp-4.5.jar

# Clean up compiled files -> currently doesnt work
clean:
		rm -f $(TARGET).exe
