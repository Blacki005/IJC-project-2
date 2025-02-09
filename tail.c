/**
 * faulta:      FIT VUT
 * priklad:     1)
 * datum:       8. 4. 2023
 * prekladac:   gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/**
 * @public
 * @brief Velikost cisla n pri ktere hrozi ukonceni programu jadrem operacniho systemu (Dle testovani na mem stroji, muze se lisit. Proto je tato skutecnost oznamena jen varovanim).
*/
#define MAX_LINES_CNT 1000000

/**
 * @public
 * @brief Maximalni delka radku v souboru.
*/
#define MAX_LINE_LENGTH 4095

/**
 * @public
 * @brief Struktura slouzici pro ulozeni poslednich n nactenych radku.
*/
struct circ_buff {
	unsigned start;///< Index nejstarsiho vlozeneho prvku.
	unsigned end; ///< (index nejnovejsiho vlozeneho prvku + 1) % velikost bufferu
	unsigned long long length; ///< Delka bufferu.
	char **buffer; ///< Pole "length" radku o maximalnidelce MAX_LINE_LENGTH.
};

/**
 * @public
 * @name Funkce pro praci s kruhovym bufferem
 * @{
*/

/**
 * @public
 * @brief Vytvori kruhovy buffer, alokuje pamet pro strukturu i radky uvnitr bufferu. Vraci ukazatel na vytvoreny buffer nebo NULL v pripade selhani.
 * @param [in] length Pocet radku v bufferu.
*/
struct circ_buff *cb_create(unsigned long length) {

	//alokace pameti pro strukturu circ_buff a inicializace start a end fci calloc()
	struct circ_buff *cb = calloc(1, sizeof(struct circ_buff));
	if (cb == NULL) {
		return NULL;
	}

	//alokace pameti pro pole ukazatelu na prvni pismena radku ulozenych v bufferu
	cb->length = length;
	cb->buffer = calloc(length, sizeof(char*));
	if (cb->buffer == NULL) {
		return NULL;
	}
	//alokace pameti pro radky v bufferu
	for (unsigned long i = 0; i < length; i++) {
		cb->buffer[i] = calloc(1 ,MAX_LINE_LENGTH);
		if (cb->buffer[i] == NULL) {
			return NULL;
		}
	}
	return cb;
}


/**
 * @public
 * @brief Vlozi string na index end (za naposledy vlozny prvek) v bufferu. Pokud je naplnena velikost bufferu, prepisuje nejstarsi polozku. Posune ukazatel na misto za naposledy vlozeny prvek.
 * @param [in] *cb Kruhovy buffer.
 * @param [in] *line Radek k vlozeni.
*/
void cb_put(struct circ_buff *cb, char *line) {
	memcpy(cb->buffer[cb->end], line, strlen(line) + 1);
	cb->end++;
	cb->end %= cb->length;
	cb->start = cb->end;
}


/**
 * @public
 * @brief Vrati nejstarsi string v bufferu, posune index nejstarsiho prvku.
 * @param [in] *cb Ukazatel na kruhovy buffer.
 * @return Ukazatel na prvni znak nejstarsiho radku.
*/
char *cb_get(struct circ_buff *cb) {
	char *item = cb->buffer[cb->start];
	cb->start++;
	cb->start %= cb->length;
	return item;
}

/**
 * @public
 * @brief Uvolni vsechny dynamicky alokovane zdroje pro kruhovy buffer (Tj. vsechny stringy ktere jsou v nem ulozeny a strukturu).
 * @param [in] *cb Ukazatel na kruhovy buffer.
*/
void cb_free(struct circ_buff *cb) {
	//free buffer
	for (unsigned long i = 0; i < cb->length; i++) {
		free(cb->buffer[i]);
	}
	free(cb->buffer);
	free(cb);
}

/**
 * @}
*/

/**
 * @public
 * @brief Cte ze souboru radky a uklada je do kruhoveho bufferu. Funkce vytvori kruhovy buffer a alokuje mu pamet.
 * @details Delka radku je omezena limitem MAX_LINE_LENGTH. Cte se maximalne prvnich MAX_LINE_LENGTH - 1 znaku, zbytek se preskakuje.
 * @param [in] *file Ukazatel na otevreny a validni (zodpovida uzivatel) soubor, ze ktereho se maji radky cist.
 * @param [in] lines_cnt Velikost kruhoveho bufferu.
 * @return Ukazatel na dynamicky alokovany kruhovy buffer naplneny poslednimi "lines_cnt" radky souboru.
 * @retval NULL Chyba alokace pameti.
*/
struct circ_buff *read(FILE *file, unsigned long lines_cnt) {

	//inicializace kruhoveho bufferu
	struct circ_buff *cb = cb_create(lines_cnt);
	if (cb == NULL) {
		fprintf(stderr, "Error: cb_create() has failed!\n");
		return NULL;
	}

	//alokace stringu pro ulozeni jednoho radku souboru a zaroven jeho nulovani (calloc)
 	char *buffer = calloc(1, MAX_LINE_LENGTH);
	if (buffer == NULL) {
		return NULL;
	}

	//cteni radku a jejich ukladani do kruhoveho bufferu
	int warned = 0;
	while (fgets(buffer, MAX_LINE_LENGTH, file)) {

		//pokud je radek delsi nez limit, orizne se a na jeho konec se vlozi znak '\n'. '\0' je vkladano automaticky funkci fgets.
		if (strlen(buffer) == (MAX_LINE_LENGTH - 1)) {
			buffer[MAX_LINE_LENGTH - 1] = '\n';

			//v pripade prvniho prekroceni mezi se hlasi chyba na stderr
			if (!warned) {
				fprintf(stderr, "Warning: Maximum line length has been exceeded!\n");
				warned = 1;
			}

			//preskoceni zbytku radku
			char c;
			while((c = fgetc(file)) != '\n');			
		}

		//ulozeni radku do kruhoveho bufferu
		cb_put(cb, buffer);
	}

	free(buffer);

	return cb;
}

/**
 * @private
*/
int main(int argc,char *argv[]) {
	//kontrola poctu argumentu
	if (argc > 4) {
		fprintf(stderr, "Error: Invalid arg count: %d\n", (argc - 1));
		return 1;
	}

	//definice ukazatele na kruhovy buffer a inicializace delky radku na implicitni hodnotu 10
	struct circ_buff *cb = NULL;
	long n = 10;


	//je-li zadan prepinac -n, tiskne n poslednich radku
	if (argc > 1 && strncmp(argv[1], "-n", 3) == 0) {

		if(argc == 2) {
			fprintf(stderr, "Error: Invalid arguments!\n");
			return 1;
		}

		//konverze parametru -n na unsigned int a kontrola validity
		n = strtol(argv[2], NULL, 10);
		if (errno == ERANGE) {
			fprintf(stderr, "Error: Number of lines is too large, strtol() has failed!\n");
			return 1;
		}
		if (n <= 0) {
			fprintf(stderr, "Error: Unsigned non-zero value expected!\n");
			return 1;
		}
		if (n == 0) {
			fprintf(stderr, "Error: Invalid parameter of -n option, expected unsigned integer value!\n");
			return 1;
		}
		if (n > MAX_LINES_CNT) {
			fprintf(stderr, "Warning: requesting excessive amount of resources can lead to kernel killing the process!\n");
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
			//je-li specifikovan soubor, cte se z nej n radku
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
	//neni zadan prepinac -n, cte se implicitne 10 radku
	else {
		if (argc == 1) {
			//neni specifikovan soubor, cte se ze stdin
			cb = read(stdin, n);
		}
		else if (argc == 2) {
			//je specifikovany soubor, cte se ze souboru
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
			fprintf(stderr, "Error: Too many arguments!\n");
			return 1;
		}
	}

	//tisk obsahu kruhoveho bufferu od nejstarsiho po nejnovejsi (FIFO)
	for (unsigned i = 0; i < n; i++) {
		printf("%s", cb_get(cb));
		if (cb->end == cb->start) {
			break;
		}
	}

	cb_free(cb);
	return 0;
}
