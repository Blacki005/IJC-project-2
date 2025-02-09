/**
 * faulta:      FIT VUT
 * priklad:     2)
 * datum:       9. 4. 2023
 * prekladac:   gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
*/

#include "opaque_structures.h"

void htab_free(htab_t * t) {
    //vymazani a uvolneni vsech zaznamu
    htab_clear(t);
    //uvolneni pole ukazatelu na seznamy
    free(t->arr_ptr);
    //uvolneni struktury hash tabulky
    free (t);
    return;
}
