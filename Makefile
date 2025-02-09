# faulta:      FIT VUT
# priklad:     1), 2)
# datum:       9. 4. 2023
# prekladac:   gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra
PROGS = tail wordcount wordcount-dynamic

all: $(PROGS)
	$(info Done!)

run: $(PROGS)
	$(info All programs have been generated!)

clean:
	@rm *.o
	$(info Object files removed!)

#########################################
#Ukol c. 1:
#########################################

tail: tail.o
	@gcc $(CFLAGS) $^ -o $@ $(LDFLAGS)

tail.o: tail.c
	$(info Building tail...)
	$(info Tip: The Archery skill improves the use of bows and arrows. The greater the skill, the more deadly the shot.)
	@gcc $(CFLAGS) -c $^ -o $@

#########################################
#Ukol c. 2:
#########################################

wordcount: wordcount.o io.o libhtab.a
	$(info Building wordcount...)
	$(info Tip: The cow is one of Skyrim's most common domestic animals. It provides the native Nords with meat, milk, and furs.)
	@gcc -o $@ -static $^ -L. -lhtab

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(info Building wordcount-dynamic...)
	$(info Tip: The Warrior Stone ability lets you learn combat skills more quickly.)
	@gcc -Wl,-rpath,./ -o $@ $^ -L. -lhtab

wordcount.o: wordcount.c
	@gcc $(CFLAGS) -c $^ -o $@

#io file:
io.o: io.c
	@gcc $(CFLAGS) -c $^ -o $@

#staticka a dynamicka varianta knihovny libhtab
libhtab.a: htab_free.o htab_init.o htab_lookup_add.o htab_find.o htab_erase.o htab_hash_function.o htab_clear.o htab_statistics.o htab_for_each.o htab_bucket_count.o htab_size.o
	$(info Building libhtab.a...)
	$(info Tip: Whiterun's central location in Skyrim has made it a trading hub of the entire province.)
	@ar -crs libhtab.a $^


libhtab.so: htab_free.c htab_init.c htab_lookup_add.c htab_find.c htab_erase.c htab_hash_function.c htab_clear.c htab_statistics.c htab_for_each.c htab_bucket_count.c htab_size.c
	$(info Building libhtab.so...)
	$(info You can learn up to three words for a Shout. Each word adds to the power of the Shout.)
	@cc -c -fPIC $^
	@cc -shared -fPIC $^ -o $@

#inicializace a uvolneni hash tabulky
htab_free.o: htab_free.c
	@gcc $(CFLAGS) -c $^ -o $@

htab_init.o: htab_init.c
	@gcc $(CFLAGS) -c $^ -o $@


#pridavani, vyhledani a odstraneni prvku z hash tabulky podle klice, statistiky
htab_lookup_add.o: htab_lookup_add.c
	@gcc $(CFLAGS) -c $^ -o $@

htab_size.o: htab_size.c
	@gcc $(CFLAGS) -c $^ -o $@

htab_find.o: htab_find.c
	@gcc $(CFLAGS) -c $^ -o $@

htab_erase.o: htab_erase.c
	@gcc $(CFLAGS) -c $^ -o $@

htab_hash_function.o: htab_hash_function.c
	@gcc $(CFLAGS) -c $^ -o $@

htab_clear.o: htab_clear.c
	@gcc $(CFLAGS) -c $^ -o $@

htab_statistics.o: htab_statistics.c
	@gcc $(CFLAGS) -c $^ -o $@

htab_for_each.o: htab_for_each.c
	@gcc $(CFLAGS) -c $^ -o $@

htab_bucket_count.o: htab_bucket_count.c
	@gcc $(<CFLAGS) -c $^ -o $@
