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
static int num_banned = 0; // Tracking number of banned words


static void to_lower_str(char *text) {
    int i = 0;

    while (text[i] != '\0') { // loop until end of string
        text[i] = tolower(text[i]); // convert character to lowercase
        i++; // move to next character
    }
}

static void strip_newline(char *s) {
    int len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
    }
}

int banned_init(const char *banned_text_filename) {

    num_banned = 0; 

    // Reading from text file
    FILE *banned_words_file = fopen(banned_text_filename, "r"); // pointer to the open file returned form fopen
    if (!banned_words_file) {
        perror("banned_init: fopen"); // double check if this is perror right
        return -1; 
    }


    char line_buffer[128]; // temporary buffer to store one line from text file

    while (fgets(line_buffer, sizeof(line_buffer), banned_words_file)) {
        
        strip_newline(line_buffer);

        if (line_buffer[0] == '\0') { // if already has /0 skip it, or empty line
            continue;
        }

        strncpy(banned_words[num_banned], line_buffer, MAX_BANNED_LEN);
        banned_words[num_banned][MAX_BANNED_LEN - 1] = '\0';

        // Lowercase for case-insensitive matching
        to_lower_str(banned_words[num_banned]);

        num_banned++; // increment count of number of banned words loaded
    }



    fclose(banned_words_file);

    printf("banned_init: loaded %d banned words from %s\n", num_banned, banned_text_filename);
    return 0;
}

void banned_close(void) {
    // no need to free memory so yeah
}

int banned_contains(const char *msg) {
    if (!msg) return 0;

    char lowercase_message[1024];
    strncpy(lowercase_message, msg, sizeof(lowercase_message)); // makes an all lower case copy of the message
    lowercase_message[sizeof(lowercase_message) - 1] = '\0';

    to_lower_str(lowercase_message);

    for (int i = 0; i < num_banned; i++) {
        if (strstr(lowercase_message, banned_words[i]) != NULL){
            return 1; // a banned word was found
        }
    }
    return 0;
}