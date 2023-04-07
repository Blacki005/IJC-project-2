CFLAGS = -g -O0 -std=c11 -pedantic -Wall -Wextra -fsanitize=address
LDFLAGS = -static-libasan

all: tail

run: tail
	./tail

clean:
	rm *.o

tail: tail.o
	gcc $(CFLAGS) $(LDFLAGS) tail.o -o tail

tail.o: tail.c
	gcc $(CFLAGS) -c tail.c -o tail.o
