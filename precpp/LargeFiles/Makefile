CC = gcc
CFLAGS = -Wall -Wextra -g

app: main.o mathutils.o
	$(CC) main.o mathutils.o -o app

main.o: main.c mathutils.h
	$(CC) $(CFLAGS) -c main.c 

mathutils.o: mathutils.c mathutils.h
	$(CC) $(CFLAGS) -c mathutils.c

clean:
	rm -f *.o app

