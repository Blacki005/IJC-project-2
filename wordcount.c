/**
 * faulta:      FIT VUT
 * priklad:     2)
 * datum:       9. 4. 2023
 * prekladac:   gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
 * Poznamka:    Komentare zdrojovych kodu knihovny jsou kompatibilni s programem "doxygen". Je nutne pouzit jiste konfigurace, aby se dokumentace generovala korektne - pro zaslani konfiguracniho souboru me kontaktujte mailem na "blacki005 AT protonmail.com".
*/

#include "io.h"
#include "htab.h"
#include <limits.h>

/// @brief Implementacni limit - maximalni povolena delka slova.
#define MAX_WORD_LENGTH 255
/// @brief Dle testu (na konci souboru) se tato varianta projevila jako nejrychlejsi.
#define HTAB_SIZE 100000


/**
 * @public
 * @brief Funkce tisknouci dvojici hash tabulky ve formatu [klic, hodnota].
 * @param [in] *pair Ukazatel na strukturu dvojice [klic, hodnota].
*/
void print(htab_pair_t *pair) {
    printf("%s\t%d\n", pair->key, pair->value);
    return;
}

int main() {
    //alokace pameti pro buffer na ukladani nactenych slov
    char *buffer = calloc(MAX_WORD_LENGTH, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Error: unable to allocate memory!");
        return 1;
    }

    //inicializace hash tabulky o velikosti 100'000 - tato varianta se ukazala jako nejrychlejsi - viz testy na konci souboru
    htab_t *t = htab_init(HTAB_SIZE);
    if (t == NULL) {
        fprintf(stderr, "Error allocating memory in htab_init()!\n");
        return 1;
    }

    //cteni slov po EOF, a pridavani do tabulky (inkrementace jejich vyskytu = hodnoty v hash tabulce)
    int ret = 0;
    while (true) {
        ret = read_word(buffer, MAX_WORD_LENGTH, stdin);
        if (ret == EOF) {
            break;
        }
        //pokud se slovo v tabulce jeste neni a prekrocilo limit, vytiskne se varovani
        if ((htab_find(t, buffer) == NULL) && (ret == (MAX_WORD_LENGTH - 1))) {
            fprintf(stderr, "Warning: Word is too long!\n");
        }

        if (htab_lookup_add(t, buffer) == NULL) {
            fprintf(stderr, "Error allocating memory in htab_lookup_add()!\n");
            return 1;
        };
    }

    //volani fce print na kazdou dvojici [slovo,vyskyt] hash tabulky
    htab_for_each(t, print);

    htab_statistics(t);

    htab_free(t);
    free(buffer);
   return 0;
}

//======================================================
/**
 * STATISTIKY DOBY BEHU PROGRAMU
 * testovany soubor: "/usr/share/dict/words" - 104334 slov
 * konfigurace:
 *      CPU: AMD Ryzen 5 4600H
 *      RAM: 8GB
 *      OS: Ubuntu 22.04.2 LTS
 *      Kernel: Linux 5.19.0-38-generic
 *      stack size: 8192 KB (default)
 *      prekladac: gcc 11.3.0
 *      optimalizace: -O0
 * 
 * arr_size = 1'000'000'000:
 *      real    0m3,822s
 *      user	0m3,030s
 *      sys	    0m0,792s
 * 
 * arr_size = 100'000'000:
 *      real    0m0,835s
 *      user	0m0,380s
 *      sys	    0m0,321s
 * 
 * arr_size = 10'000'000:
 *      real    0m0,443s
 *      user	0m0,094s
 *      sys	    0m0,185s
 * 
 * arr_size = 1'000'000:
 *      real    0m0,400s
 *      user	0m0,067s
 *      sys	    0m0,188s
 * 
 * arr_size = 100'000:      <-nejlepsi vykonnost
 *      real    0m0,389s
 *      user	0m0,089s
 *      sys	    0m0,179s
 * 
 * arr_size = 10'000:       <-porovnatelny vykon s 10x mensi velikosti - dobra alternativa
 *      real	0m0,404s
 *      user	0m0,098s
 *      sys	    0m0,115s
 * 
 * arr_size = 1'000:
 *      real	0m0,605s
 *      user	0m0,289s
 *      sys	    0m0,143s
 * 
 * arr_size = 100:
 *      real	0m1,822s
 *      user	0m1,513s
 *      sys	    0m0,136s
 * 
 * arr_size = 10:
 *      real	0m14,366s
 *      user	0m14,059s
 *      sys	    0m0,160s
 * 
 * arr_size = 1:
 *      real	0m29,903s
 *      user	0m29,582s
 *      sys	    0m0,144s
*/
//======================================================
