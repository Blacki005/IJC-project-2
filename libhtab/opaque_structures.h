#ifndef OPAQUE_STRUCTS_
#define OPAQUE_STRUCTS_

#include "htab.h"

typedef struct htab_t {
    //nepredpoklada se vetsi velikost nez 4294967295
    size_t size;
    size_t arr_size;
    struct htab_item **arr_ptr; //ukazatel na dynamicky alokovane pole ukazatelu na seznamy itemu
} htab_t;

typedef struct htab_item {
    struct htab_item *next;
    struct htab_pair;
} htab_item;

#endif //OPAQUE_STRUCTS_

