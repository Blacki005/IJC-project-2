#include "htab.h"
#include "opaque_structures.h"

void htab_free(htab_t * t) {
    for (size_t i = 0; i < t->arr_size; i++) {
        free(t->arr_ptr[i]);
    }
    free (t);
    return;
}