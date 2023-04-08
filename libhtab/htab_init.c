#include "htab.h"
#include "opaque_structures.h"

/**
 * vytvori a a inicializuje tabulku s poctem prvku pole (.arr_size) = n
 * vraci NULL pokud nemuze alokovat pamet, uzivatel za to prebira zodpovednost
*/
htab_t *htab_init(const size_t n) {
    struct htab_t *htab = calloc(1, sizeof(struct htab_t));
    if (htab == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        htab->arr_ptr[i] = calloc(1, sizeof(struct htab_item));
        if (htab->arr_ptr[i] == NULL) {
            return NULL;
        }
    }

    htab->arr_size = n;
    htab->size = 0;
    return htab;
};