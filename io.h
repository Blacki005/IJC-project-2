/**
 * faulta:      FIT VUT
 * priklad:     2)
 * datum:       9. 4. 2023
 * prekladac:   gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
*/

#ifndef IO_H__
#define IO_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @public
 * @brief Funkce cte slovo ze souboru f a uklada ho do pole s. Maximalni delka slova je omezena parametrem max.
 * @details Slovo je sekvence jakychkoli znaku oddelena ws na obou stranach. Pokud je slovo delsi nez max, precte se prvnich max-1 znaku, prida se ukoncujici znak '\0' a zbytek slova se preskoci.
 * @param [in] *s Ukazatel na pole charu o minimalni velikosti max.
 * @param [in] max Maximalni delka jednoho slova.
 * @param [in] *f Soubor, ze ktereho se slova ctou.
 * @return Pocet nactenych znaku.
 * @retval EOF Pri cteni bylo dosazeno konce souboru.
*/
int read_word(char *s, int max, FILE *f);

#endif //IO_H__
