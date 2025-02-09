/**
 * autor:       Dr. Ing. Petr Peringer
 * faulta:      FIT VUT
 * priklad:     2)
 * datum:       21. 3. 2023
 * prekladac:   gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
 * licence:     Public domain
*/

// následující řádky zabrání násobnému vložení:
#ifndef HTAB_H__
#define HTAB_H__

#include <string.h>     // size_t
#include <stdbool.h>    // bool

/**
 * @public
 * @brief Struktura hash tabulky.
*/
struct htab;    // neúplná deklarace struktury - uživatel nevidí obsah
typedef struct htab htab_t;     // typedef podle zadání

/**
 * @public
 * @brief Datovy typ pro klic v hash tabulce (slovo).
*/
typedef const char * htab_key_t;        // typ klíče
/**
 * @public
 * @brief Datovy typ pro hodnotu v hash tabulce (pocet vyskytu slova).
*/
typedef int htab_value_t;               // typ hodnoty

/**
 * @public
 * @brief Datovy typ pro dvojici [klic, hodnota] v hash tabulce.
*/
typedef struct htab_pair {
    htab_key_t    key;          ///< klíč
    htab_value_t  value;        ///< asociovaná hodnota
} htab_pair_t;                  ///< typedef podle zadání

/**
 * @public
 * @brief Rozptylovaci (hash) funkce (stejna pro vsechny hodnoty v programu)
 * @param [in] str Klic podle ktereho funkce vypocita index.
 * @return Cislo typu size_t. Cislo % arr_size = index do tabulky.
*/
size_t htab_hash_function(htab_key_t str);

/**
 * @public
 * @name Funkce pro praci s tabulkou.
 * @{
*/
/**
 * @public
 * @brief Konstruktor tabulky.
 * @param [in] n Velikost tabulky - kolik linearne vazanych seznamu se ma vytvorit.
 * @return Ukazatel na vytvorenou, dynamicky alokovanou tabulku.
 * @retval NULL Chyba alokace pameti.
*/
htab_t *htab_init(const size_t n);
/**
 * @public
 * @brief Fce pro vypocet poctu zaznamu [klic, hodnota] v tabulce.
 * @param [in] *t Ukazatel na hash tabulku.
 * @return Pocet zaznamu v tabulce.
*/
size_t htab_size(const htab_t * t);
/**
 * @public
 * @brief Fce pro vypoet poctu linearne vazanych seznamu v hash tabulce.
 * @param [in] *t Ukazatel na hash tabulku.
 * @return Pocet seznamu v tabulce = arr_size.
*/
size_t htab_bucket_count(const htab_t * t);
/**
 * @public
 * @brief Fce nalezne v tabulce dvojici podle klice.
 * @param [in] *t Ukazatel na hash tabulku.
 * @param [in] key Klic do hash tabulky.
 * @return Ukazatel na dvojici [klic, hodnota] odpovidajici klici.
 * @retval NULL Dvojice nebyla nalezena.
 */
htab_pair_t * htab_find(const htab_t * t, htab_key_t key);
/**
 * @public
 * @brief Fce zkusi vyhledat klic v tabulce. Pokud je pritomny, inkrementuje k nemu spadajici hodnotu. Pokud v tabulce neni, prida ho.
 * @param [in] *t Ukazatel na hash tabulku.
 * @param [in] key Klic do hash tabulky.
 * @return Ukazatel na dvojici [klic, hodnota] odpovidajici klici.
 * @retval NULL Chyba alokace pameti.
 */
htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key);
/**
 * @public
 * @brief Vymazani odpovidajici dvojice [klic, hodnota] z tabulky.
 * @param [in] *t Ukazatel na hash tabulku.
 * @param [in] key Klic do hash tabulky.
 * @retval true Dvojice byla uspesne odstranena.
 * @retval false Klic v tabulce nebyl nalezen.
*/
bool htab_erase(htab_t * t, htab_key_t key);    // ruší zadaný záznam
/**
 * @public
 * @brief Projde vsechny dvojice v tabulce a na kazdou z nich zavola funkci f.
 * @details Funkce f nesmi menit klic ani pridavat nebo ubirat dvojice z tabulky.
 * @param [in] *t Ukazatel na hash tabulku.
 * @param [in] *f Ukazatel na funkci s ukazatelem na dvojici [klic, hodnota] a vracejici void.
*/
void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data));
/**
 * @public
 * @brief Zrusi vsechny zaznamy v tabulce a uvolni alokovanou pamet.
 * @param [in] *t Ukazatel na hash tabulku.
*/
void htab_clear(htab_t * t);    // ruší všechny záznamy
/**
 * @public
 * @brief Destruktor tabulky - rusi celou tabulku a vsechny jeji zaznamy, uvolnuje pamet.
 * @details Pro vymazani zaznamu vyuziva funkci htab_clear().
 * @param [in] *t Ukazatel na hash tabulku.
*/
void htab_free(htab_t * t);
/**
 * @public
 * @brief Vytiskne do stderr min, max a avg delku seznamu v hash tabulce.
 * @param [in] *t Ukazatel na hash tabulku.
*/
void htab_statistics(const htab_t * t);
/**
 * @}
*/

#endif // HTAB_H__
