/**
 * faulta:      FIT VUT
 * priklad:     2)
 * datum:       9. 4. 2023
 * prekladac:   gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
*/

#include "opaque_structures.h"

bool htab_erase(htab_t * t, htab_key_t key) {

    //vypocet indexu do pole ukazatelu na seznamy
    size_t index = htab_hash_function(key) % (t->arr_size);
    //nastaveni hlavicky listu - ukazatele na prvni prvek listu
    struct htab_item *head = t->arr_ptr[index];

    //vraci false, pokud je seznam prazdny
    if (head == NULL) {
        return false;
    }

    //tmp - slouzi pro pruchod seznamem
    //prev - ukazuje na prvek predchazejici tmp
    struct htab_item *tmp = head;
    struct htab_item *prev = NULL;

    //hledani prvku se shodnym klicem - pruchod seznamem s indexem index
    while (tmp != NULL && strncmp(tmp->pair.key, key, strlen(key) + 1)) {
        prev = tmp;
        tmp = tmp->next;
    }

    //pokud hodnota odpovidajici klici v seznamu neni, vraci se false - nelze odstranit neexistujici hodnotu
    if (tmp == NULL) {
        return false;
    }

    //prvek s odpovidajicim klicem se odpoji ze seznamu
    //pokud klici odpovida prvni prvek seznamu, prelinkuje se ukazatel arr_ptr[index] na tmp->next
    if (tmp == head) {
        head = tmp->next;
        t->arr_ptr[index] = head;
    }
    else {
    //hledany prvek je jeden z prostredich nebo posledni prvek
        prev->next = tmp->next;
    }

    //odpojeny prvek se uvolni
    free((char *)tmp->pair.key);
    free(tmp);
    return true;
}
