#include "banned.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define MAX_BANNED_WORDS 64
#define MAX_BANNED_LEN 32

/*
 * CHecks for any banned words sent from predetermined list in a text file
 */


// global (only within banned.c) storage for banned words
static char banned_words[MAX_BANNED_WORDS][MAX_BANNED_LEN]; // 2D array of banned words (word)(word_length)
static int num_banned = 0; // tracking number of banned words


static void to_lower_str(char *text) { //goes thru each character of string and turns them into lower case
    while (*text) {
        *text = (char)tolower((unsigned char)*text);
        text++;
    }
}



int banned_init(const char *banned_text_filename) {
    (void)banned_text_filename; // skip over for time being

    num_banned = 0; // hard coding banned words to test the storage

    strncpy(banned_words[num_banned], "fucking", MAX_BANNED_LEN);
    banned_words[num_banned][MAX_BANNED_LEN - 1] = '\0';
    to_lower_str(banned_words[num_banned]);
    num_banned++; // increments by 1

    strncpy(banned_words[num_banned], "needham", MAX_BANNED_LEN);
    banned_words[num_banned][MAX_BANNED_LEN - 1] = '\0';
    to_lower_str(banned_words[num_banned]);
    num_banned++; // increments by 1

    // strncpy(banned_words[num_banned++], "Needham", MAX_BANNED_LEN); //oh baby those hips don't lie doot doot
    // strncpy(banned_words[num_banned++], "fucking", MAX_BANNED_LEN); 
    // strncpy(banned_words[num_banned++], "sucks", MAX_BANNED_LEN); 


    printf("banned_init: loaded %d hard-coded banned words\n", num_banned);
    return 0;
}

void banned_close(void) {
    // empty, will implement later once init is tested

}

int banned_contains(const char *msg) {
    if (!msg) return 0;

    char lowercase_message[1024];
    strncpy(lowercase_message, msg, sizeof(lowercase_message)); // makes an all lower case copy of the message
    lowercase_message[sizeof(lowercase_message) - 1] = '\0';

    to_lower_str(lowercase_message);

    for (int i = 0; i < num_banned; i++) {
        if (strstr(lowercase_message, banned_words[i]) != NULL){
            return 1;
        }
    }
    return 0;
}