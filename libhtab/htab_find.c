/**
 * faulta:      FIT VUT
 * priklad:     2)
 * datum:       9. 4. 2023
 * prekladac:   gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
*/

#include "opaque_structures.h"

htab_pair_t * htab_find(const htab_t * t, htab_key_t key) {
    //vypocet indexu do pole ukazatelu na seznamy arr_ptr
    size_t index = htab_hash_function(key) % (t->arr_size);
    //nastaveni ukazatele tmp na hlavicku seznamu s indexem index
    struct htab_item *tmp = t->arr_ptr[index];

    //pruchod seznamem dokud se nedojde na konec, nebo se nenarazi na polozku s odpovidajicim klicem
    while(tmp != NULL && strncmp(tmp->pair.key, key, strlen(key) + 1)) {
        tmp = tmp->next;
    }

    //pokud po pruchodu seznamem ukazuje tmp na jeho konec, polozka v seznamu nebyla nalezena
    if (tmp == NULL) {
        return NULL;
    }

    return &(tmp->pair);
}
