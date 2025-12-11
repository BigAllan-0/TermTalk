#include "banned.h"

#include <stdio.h>

/*
 * CHecks for any banned words sent from predetermined list in a text file
 */

int banned_init(const char *banned_text_filename) { //testing if can call file
    printf("banned_init called with filename: %s\n", banned_text_filename);
    return 0;
}

void banned_close(void) {
    // empty, will implement later once init is tested

}

int banned_contains(const char *msg) {

    (void)msg; // to avoid usused param warning
    return 0;
}