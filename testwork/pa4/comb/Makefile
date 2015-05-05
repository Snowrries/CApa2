CC=gcc
CCFLAGS = -Wall -g -Werror
OBJECTS = comb.o

all: $(OBJECTS)
	$(CC) $(CCFLAGS) comb.o -o comb

comb.o: 
	$(CC) $(CCFLAGS) -c comb.c

clean: 
	rm -f *.o
	rm comb
	
