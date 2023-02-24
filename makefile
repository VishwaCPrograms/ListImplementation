# Author: Vishwa Venkateshwaran

all: list

list: list.c main.c list.h
	gcc list.c main.c -o list

cleanO:
	rm -rf *.o

clean:
	rm -rf list *.o
