CC :=gcc

CFLAGS := -c -Wall


all:runn

runn:final
	./final

final:pro1.o jsmn.o
	$(CC) pro1.o jsmn.o -o final

pro1.o:pro1.cpp
	$(CC) $(CFLAGS) pro1.cpp


jsmn.o:jsmn.c 
	$(CC) $(CFLAGS) jsmn.c

clean:
	rm -rf *o final

cls:
	clear