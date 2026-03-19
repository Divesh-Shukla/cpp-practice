CC = gcc
CFLAGS = -Wall -Wextra -g
CFLAGS_RELEASE = -Wall -Wextra -O2
CFLAGS_DEBUG = -Wall -Wextra -O0

app: main.o mathutils.o
	$(CC) main.o mathutils.o -o app

main.o: main.c mathutils.h
	$(CC) $(CFLAGS) -c main.c 

mathutils.o: mathutils.c mathutils.h
	$(CC) $(CFLAGS) -c mathutils.c

clean:
	rm -f *.o app

debug: 
	$(CC) $(CFLAGS_DEBUG) -c main.c -o main.o
	$(CC) $(CFLAGS_DEBUG) -c mathutils.c -o mathutils.o
	$(CC) main.o mathutils.o -o app

release: 
	$(CC) $(CFLAGS_RELEASE) -c main.c -o main.o 
	$(CC) $(CFLAGS_RELEASE) -c mathutils.c -o mathutils.o 
	$(CC) main.o mathutils.o -o app

.PHONY: clean release debug
# When we type make clean in the terminal, the first thing the make commanad does is look for file name clean.
#If the file name exists it things that the target already exist and does nothing. Therefore we >PHONY to tell make
#that these targets are just commands and they are not a file.
