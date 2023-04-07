/*print last 10 lines from given file
 *
 *
 *
 *
 *
 *
 *
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define log printf
#define MAX_LINE_LENGTH 4095 //max line length in bytes

struct circ_buff {
	unsigned start; //idx of first inserted
	unsigned end; //idx of last inserted
	unsigned long long length;
	char **buffer; //pole radku o delce max lngth
};

struct circ_buff *cb_create(unsigned long long length) {
	//log("entering cb_create, length is %llu", length);

	//creates circular buffer structure, nulls end and start pointers and dynamically allocs field for lines
	struct circ_buff *cb = calloc(1, sizeof(struct circ_buff));
	if (cb == NULL) {
		return NULL;
	}

	cb->end = 0;
	cb->start = 0;
	cb->length = length;
	cb->buffer = calloc(length, sizeof(char*));
	if (cb->buffer == NULL) {
		return NULL;
	}
	for (unsigned long long i = 0; i < length; i++) {
		cb->buffer[i] = calloc(1 ,MAX_LINE_LENGTH);
		if (cb->buffer[i] == NULL) {
			return NULL;
		}
	}

	return cb;
}

void cb_put(struct circ_buff *cb, char *line) {
	//put on last position in cb
	memcpy(cb->buffer[cb->end], line, strlen(line) + 1);
	cb->end++;
	cb->end %= cb->length;
	cb->start = cb->end;
}

char *cb_get(struct circ_buff *cb) {
	//get last stored element from buffer (FIFO) and return it
	char *item = cb->buffer[cb->start];
	cb->start++;
	cb->start %= cb->length;
	return item;
}

void cb_free(struct circ_buff *cb) {
	//free buffer
	for (unsigned long long i = 0; i < cb->length; i++) {
		free(cb->buffer[i]);
	}
	free(cb->buffer);
	free(cb);
}

//reads from file lines_cnt lines and stores to circular buffer cb, returns pointer to created cb
//caller MUST free dynamically allocated buffer by calling cb_free()
//function assumes that file is pointer to valid file, caller is responsible
struct circ_buff *read(FILE *file, unsigned long long lines_cnt) {

	//initialize buffer of size cnt
	struct circ_buff *cb = cb_create(lines_cnt);
	if (cb == NULL) {
		fprintf(stderr, "Error: cb_create() has failed!\n");
		return NULL;
	}

	
	//allocates buffer to store line
	char *buffer = calloc(1, MAX_LINE_LENGTH);
	if (buffer == NULL) {
		return NULL;
	}

	while (fgets(buffer, MAX_LINE_LENGTH - 1, file)) {

		if (strlen(buffer) == MAX_LINE_LENGTH && buffer[MAX_LINE_LENGTH] != '\0') {

			//line is longer than MAX_LINE_LENGTH - add terminating char and ignore rest
			buffer[MAX_LINE_LENGTH] = '\0';

			log("log: buffer is too long!\n");
		}

		//stores read line in cb, if cb is full, overwrites oldest
		cb_put(cb, buffer);
	}

	free(buffer);

	return cb;
}

int main(int argc,char *argv[]) {
	//check number of args
	if (argc > 4) {
		fprintf(stderr, "Wrong arg count: %d\n", (argc - 1));
		return 1;
	}

	struct circ_buff *cb = NULL;
	unsigned long long n = 10;


	//je-li zadan prepinac -n, tiskne n poslednich radku
	if (argc > 1 && strncmp(argv[1], "-n", 3) == 0) {

		//konverze parametru -n na unsigned int a kontrola validity
		n = strtoul(argv[2], NULL, 10);
		if (errno == ERANGE) {
			fprintf(stderr, "Number of lines is too large, strtoul() has failed!\n");
			return 1;
		}
		if (n == 0) {
			fprintf(stderr, "Error: Invalid parameter of -n option, expected unsigned integer value!\n");
			return 1;
		}
		
		if(argc < 4) {
			//neni specifikovan soubor, cte se n radku ze stdin:
			cb = read(stdin, n);
			if (cb == NULL) {
				fprintf(stderr, "Error: Allocating memory in read() has failed.\n");
				return 1;
			}
		}
		else {
			//cte se n radku ze specifikovaneho souboru
			FILE *file = fopen(argv[3] ,"r");
			if(file == NULL) {
				fprintf(stderr, "Error: Unable to open file \"%s\"\n", argv[3]);
				return 1;
			}

			cb = read(file, n);
			if (cb == NULL) {
				fprintf(stderr, "Error: Allocating memory in read() has failed.\n");
				return 1;
			}

			if (fclose(file) == EOF) {
				fprintf(stderr, "Warning: File \"%s\" was not closed successfully!\n", argv[3]);
			}
			
		}
	}
	//neni zadan prepinac -n, cte se 10 radku
	else {
		if (argc == 1) {
			//neni specifikovan soubor, cte se ze stdin
			cb = read(stdin, n);
		}
		else if (argc == 2) {
			//je specifikovany soubor
			FILE *file = fopen(argv[1] ,"r");
			if(file == NULL) {
				fprintf(stderr, "Error: Unable to open file \"%s\"\n", argv[1]);
				return 1;
			}

			cb = read(file, n);
			if (cb == NULL) {
				fprintf(stderr, "Error: Allocating memory in read() has failed.\n");
				return 1;
			}

			if (fclose(file) == EOF) {
				fprintf(stderr, "Warning: File \"%s\" was not closed successfully!\n", argv[1]);
			}

		}
		else {
			//wrong arg
			fprintf(stderr, "Too many arguments!\n");
			return 1;
		}
	}

	for (unsigned i = 0; i < n; i++) {
		printf("%s",cb_get(cb));
		if (cb->end == cb->start) {
			break;
		}
	}

	cb_free(cb);

	return 0;
}