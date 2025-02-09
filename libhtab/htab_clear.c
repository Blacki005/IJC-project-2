/**
 * faulta:      FIT VUT
 * priklad:     2)
 * datum:       9. 4. 2023
 * prekladac:   gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
*/

#include "opaque_structures.h"


void htab_clear(htab_t * t) {
    //pruchod vsemi seznamy:
    for (size_t i = 0; i < t->arr_size; i++) {


        struct htab_item *next = NULL;
        //pruchod vsemi prvky seznamu
        for (struct htab_item *tmp = t->arr_ptr[i]; tmp != NULL; tmp = next) {
            //pretypovani na char*, uvolneni a nulovani klice
            free((char *)tmp->pair.key);

            //ulozeni ukazatele na dalsi prvek
            next = tmp->next;

            //uvolneni prvku
            free(tmp);
        }
    }
}
