#include "opaque_structures.h"


/**
 * faulta:      FIT VUT
 * priklad:     2)
 * datum:       9. 4. 2023
 * prekladac:   gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
*/

htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key) {
    //vypocet indexu do arr_ptr hashovaci fci
    size_t index = htab_hash_function(key) % (t->arr_size);

    //nastaveni na tmp na hlavicku seznamu s indexem index
    struct htab_item *tmp = t->arr_ptr[index];

    //pruchod seznamem dokud se nedojde na konec, nebo neni nalezena hledana hodnota
    while(tmp != NULL && strncmp(tmp->pair.key, key, strlen(key) + 1)) {
        tmp = tmp->next;
    }

    //pokud je hledana hodnota nalezena, inkrementuje se jeji hodnota - prida se vyskyt slova
    if (tmp != NULL) {
        tmp->pair.value++;
    }

    //pokud hodnota v seznamu neni (tmp ukazuje za konec seznamu), vlozi se na zacatek seznamu
    if (tmp == NULL) {
        //alokace pameti pro novou polozku a jeji klic (string)
        tmp = calloc(1, sizeof(struct htab_item));
        if (tmp == NULL) {
            return NULL;
        }
        tmp->pair.key = calloc(1, strlen(key) + 1);
        if (tmp->pair.key == NULL) {
            return NULL;
        }

        //kopirovani klice do zaznamu pomoci memcpy (bezpecny strcpy)
        memcpy((char *)tmp->pair.key, key, strlen(key) + 1);
        tmp->pair.value = 1;

        //newItem->next = list->head; list->head = newItem
        tmp->next = t->arr_ptr[htab_hash_function(key) % (t->arr_size)];
        t->arr_ptr[htab_hash_function(key) % (t->arr_size)] = tmp;
    }

    return &(tmp->pair);
}

