CC = g++
CFLAGS =-c -Wall -std=c++11

all: compile

compile: main.o
	$(CC) main.o -o DTGAS91076

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm *.o $(EXEC)
