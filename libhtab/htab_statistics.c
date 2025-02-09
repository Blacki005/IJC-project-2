/**
 * faulta:      FIT VUT
 * priklad:     2)
 * datum:       9. 4. 2023
 * prekladac:   gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
*/

#include "opaque_structures.h"
#include <stdio.h>
#include <limits.h>

void htab_statistics(const htab_t * t) {
    double avg = 0;
    unsigned min = UINT_MAX, max = 0;

    if(t->arr_size == 0) {
        fprintf(stderr, "Error: Table is empty!");
        return;
    }

    //pruchod vsemi seznamy v hash tabulce
    for (size_t i = 0; i < t->arr_size; i++) {
        
        //pruchod seznamem arr_size[i] a vypocet jeho delky
        unsigned size = 0;
        for (struct htab_item *tmp = t->arr_ptr[i]; tmp != NULL; tmp = tmp->next) {
            size++;
        }

        //vypocet minima a maxima, pricteni delky k avg
        if (size > max) {
            max = size;
        }
        if (size < min) {
            min = size;
        }
        avg += size;

    }

    //deleni souctu delek seznamu poctem seznamu
    avg = avg / t->arr_size;
    fprintf(stderr, "min:\t%u\nmax:\t%u\navg:\t%lf\n", min, max, avg);
}
