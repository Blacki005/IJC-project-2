/**
 * faulta:      FIT VUT
 * priklad:     2)
 * datum:       9. 4. 2023
 * prekladac:   gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
*/

#include "io.h"


int read_word(char *s, int max, FILE *f) {
    char c;
    int chars_read = 0;

    //cteni dokud neni dosazeno konce souboru | je naplnen buffer | je dosazeno konce slova
    while((c = getc(f)) != EOF) {
        if (isspace(c)) {
            if (chars_read == 0) {
                //preskoceni bilych znaku
                continue;
            }

            //pridani koncoveho bytu a vraceni prectenych znaku
            s[chars_read] = '\0';
            return chars_read;

        }
        else if (chars_read < max - 1) {
            //pridani znaku na konec bufferu
            s[chars_read] = c;
            chars_read++;
        }

    }

    return EOF;
}
