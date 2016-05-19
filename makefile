# Makefile HW3 600.120 Spring 2015
# JHED: amehndi1
# Name: Anuj Mehndiratta
# Date: March 9, 2016

# Lines starting with # are comments

# Some variable definitions to save typing later on
CC2 = gcc
CONSERVATIVE_FLAGS = -std=c99 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

# Links the test_hw3methods executable
test_hw3methods: test_hw3methods.o hw3methods.o
	$(CC2) -o test_hw3methods test_hw3methods.o hw3methods.o

# Links the hw3 executable
hw3: hw3.o hw3methods.o
	$(CC2) -o hw3 hw3.o hw3methods.o

# Compiles hw3methods.c into an object file
hw3methods.o: hw3methods.c hw3methods.h
	$(CC2) $(CFLAGS) -c hw3methods.c

# Compiles test_hw3methods.c into an object file
test_hw3methods.o: test_hw3methods.c hw3methods.h
	$(CC2) $(CFLAGS) -c test_hw3methods.c

# Compiles hw3.c into an object file
hw3.o: hw3.c hw3methods.c hw3methods.h
	$(CC2) $(CFLAGS) -c hw3.c

# 'make clean' will remove intermediate & executable files
clean:
	rm -f *.o test_hw3 hw3 *.gcov
