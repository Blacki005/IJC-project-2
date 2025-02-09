/**
 * @mainpage Dokumentace ke skrytym (opaque) strukturam je sice pritomna ke studijnim ucelum, ale v pripade seriozni implementace by tyto udaje pochopitelne byly uzivateli skryte - tabulkou lze manipulovat pouze pres metody knihovny.
*/
/**
 * faulta:      FIT VUT
 * priklad:     2)
 * datum:       9. 4. 2023
 * prekladac:   gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
*/

#ifndef OPAQUE_STRUCTS_
#define OPAQUE_STRUCTS_

#include "htab.h"
#include <stdlib.h>

/**
 * @name Skryte struktury knihovny
 * @{
 * @public
 * @brief Struktura hash tabulky.
*/
struct htab {
    //nepredpoklada se vetsi velikost nez 4294967295
    size_t size;                ///< Pocet zaznamu (dvojic) v tabulce.
    size_t arr_size;            ///< Pocet linearne vazanych seznamu.
    struct htab_item **arr_ptr; ///< Ukazatel na dynamicky alokovane pole ukazatelu na seznamy itemu.
};

/**
 * @public
 * @brief Struktura pro polozku seznamu.
*/
struct htab_item {
    struct htab_item *next;     ///< Ukazatel na dalsi prvek.
    struct htab_pair pair;      ///< Struktura pro dvojici [klic, hodnota].
};

/**
 * @}
*/

#endif //OPAQUE_STRUCTS_

