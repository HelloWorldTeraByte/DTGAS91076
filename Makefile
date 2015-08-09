CC = g++
CFLAGS =-c -Wall -std=c++11
EXEC = DTGAS91076

all: compile

compile: main.o
	$(CC) main.o -o $(EXEC)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
rebuild: clean all
clean:
	rm -f *.o 
	rm -f $(EXEC)
