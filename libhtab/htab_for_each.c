/**
 * faulta:      FIT VUT
 * priklad:     2)
 * datum:       9. 4. 2023
 * prekladac:   gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
*/

#include "opaque_structures.h"

void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)) {
    //pruchod vsemi seznamy
    for (size_t i = 0; i < t->arr_size; i++) {
        //pruchod listem kazdeho seznamu:
        for (struct htab_item *tmp = t->arr_ptr[i]; tmp != NULL; tmp = tmp->next) {
            //volani fce f na tmp->pair, tmp se nemeni
            f(&(tmp->pair));
        }
    }
}
