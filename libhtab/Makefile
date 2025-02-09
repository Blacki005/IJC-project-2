CFLAGS = -g -O0 -std=c11 -pedantic -Wall -Wextra
LDFLAGS = 


all: libhtab.a libhtab.so
	
clean:
	rm *.o
	clear
	
libhtab.a: htab_free.o htab_init.o htab_lookup_add.o htab_find.o htab_erase.o htab_hash_function.o htab_clear.o htab_statistics.o htab_for_each.o htab_bucket_count.o htab_size.o
	ar -crs libhtab.a htab_hash_function.o htab_init.o htab_size.o htab_bucket_count.o htab_find.o htab_lookup_add.o htab_erase.o htab_for_each.o htab_clear.o htab_free.o htab_statistics.o


libhtab.so: htab_free.c htab_init.c htab_lookup_add.c htab_find.c htab_erase.c htab_hash_function.c htab_clear.c htab_statistics.c htab_for_each.c htab_bucket_count.c htab_size.c
	cc -c -fpic htab_free.c htab_init.c htab_lookup_add.c htab_find.c htab_erase.c htab_hash_function.c htab_clear.c htab_statistics.c htab_for_each.c htab_bucket_count.c htab_size.c
	cc -shared -fpic htab_free.o htab_init.o htab_lookup_add.o htab_find.o htab_erase.o htab_hash_function.o htab_clear.o htab_statistics.o htab_for_each.o htab_bucket_count.o htab_size.o -o libhtab.so


#initializing and freeing hash table
htab_free.o: htab_free.c
	gcc $(CFLAGS) -c htab_free.c -o htab_free.o

htab_init.o: htab_init.c
	gcc $(CFLAGS) -c htab_init.c -o htab_init.o


#adding, finding and erasing elements
htab_lookup_add.o: htab_lookup_add.c
	gcc $(CFLAGS) -c htab_lookup_add.c -o htab_lookup_add.o

htab_size.o: htab_size.c
	gcc $(CFLAGS) -c htab_size.c -o htab_size.o

htab_find.o: htab_find.c
	gcc $(CFLAGS) -c htab_find.c -o htab_find.o

htab_erase.o: htab_erase.c
	gcc $(CFLAGS) -c htab_erase.c -o htab_erase.o

htab_hash_function.o: htab_hash_function.c
	gcc $(CFLAGS) -c htab_hash_function.c -o htab_hash_function.o

htab_clear.o: htab_clear.c
	gcc $(CFLAGS) -c htab_clear.c -o htab_clear.o

htab_statistics.o: htab_statistics.c
	gcc $(CFLAGS) -c htab_statistics.c -o htab_statistics.o

htab_for_each.o: htab_for_each.c
	gcc $(CFLAGS) -c htab_for_each.c -o htab_for_each.o

htab_bucket_count.o: htab_bucket_count.c
	gcc $(<CFLAGS) -c htab_bucket_count.c -o htab_bucket_count.o
