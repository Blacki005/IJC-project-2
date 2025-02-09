/**
 * faulta:      FIT VUT
 * priklad:     2)
 * datum:       9. 4. 2023
 * prekladac:   gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
*/

#include "htab.h"
#include "opaque_structures.h"

size_t htab_size(const htab_t * t) {
    return t->size;
}
