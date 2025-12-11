#include <stdio.h>
#include "banned.h"

int main(void) {
    banned_init("banned_words.txt");


    const char *tests[] = {
        "I live in Needham",
        "It fucking sucks",
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