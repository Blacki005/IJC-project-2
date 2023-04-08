CFLAGS = -g -O0 -std=c11 -pedantic -Wall -Wextra -fsanitize=address
LDFLAGS = -static-libasan

all: tail wordcount

run: tail
	./tail

clean:
	rm *.o

tail: tail.o
	gcc $(CFLAGS) $(LDFLAGS) tail.o -o tail

wordcount: ./libhtab/htab_init.o
	gcc $(CFLAGS) $(LDFLAGS) htab-init.o -o wordcount

htab-init.o: ./libhtab/htab_init.c
	gcc $(CFLAGS) -c htab_init.c -o htab_init.o

tail.o: tail.c
	gcc $(CFLAGS) -c tail.c -o tail.o
