#include "banned.h"

#include <stdio.h>
#include <string.h>

#define MAX_BANNED_WORDS 64
#define MAX_BANNED_LEN 32

/*
 * CHecks for any banned words sent from predetermined list in a text file
 */

static char banned_words[MAX_BANNED_WORDS][MAX_BANNED_LEN]; // global (only within banned.c) storage for banned words
static int num_banned = 0; // check example

int banned_init(const char *banned_text_filename) {
    (void)banned_text_filename; // skip over for time being

    num_banned = 0; // hard coding banned words to test the storage

    strncpy(banned_words[num_banned++], "burgerS", MAX_BANNED_LEN);
    strncpy(banned_words[num_banned++], "fucking", MAX_BANNED_LEN); 



    printf("banned_init: loaded %d hard-coded banned words\n", num_banned);
    return 0;
}

void banned_close(void) {
    // empty, will implement later once init is tested

}

int banned_contains(const char *msg) {
    if (!msg) return 0;

    for (int i = 0; i < num_banned; i++) {
        if (strstr(msg, banned_words[i]) != NULL){
            return 1;
        }
    }
    return 0;
}