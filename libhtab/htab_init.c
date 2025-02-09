/**
 * faulta:      FIT VUT
 * priklad:     2)
 * datum:       9. 4. 2023
 * prekladac:   gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
*/

#include "opaque_structures.h"

htab_t *htab_init(const size_t n) {
    //pokud je hodnota nulova, neni co alokovat, v me implementaci se jedna se o chybu a program je ukoncen s chybovou hlaskou
    if (n == 0) {
        return NULL;
    }

    //alokace pameti pro strukturu htab
    htab_t *t = calloc(1, sizeof(htab_t));
    if (t == NULL) {
        return NULL;
    }

    //alokace pameti pro pole ukazatelu na linearne vazane seznamy
    t->arr_ptr = calloc(n, sizeof(struct htab_item *));
    if (t->arr_ptr == NULL) {
        return NULL;
    }

    //inicializace arr_size, size je callocem nastaveny na 0
    t->arr_size = n;
    return t;
}
