#include <stdio.h>
#include "banned.h"

int main(void) {

    if (banned_init("banned_words.txt") != 0) {
        printf("Failed to load banned_words.txt\n");
        return 1;
    }

    const char *tests[] = {
        "I live hate in Needham",
        "I hate poop sandwiches",
        "It doesn't FUCKING suck",
        NULL // end
    };

    for (int i = 0; tests[i] != NULL; i++) {
        printf("\"%s\" -> %d\n", tests[i], banned_contains(tests[i]));
    }
    // const char *safe = "this sentence is safe";
    // const char *bad = "this sentence is not fucking safe";
    
    // printf("safe example - %d\n", banned_contains(safe));
    // printf("bad example - %d\n", banned_contains(bad));

    banned_close();
    return 0;
}