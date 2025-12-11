#include <stdio.h>
#include "banned.h"

int main(void) {
    banned_init("banned_words.txt");

    const char *safe = "this sentence is safe";
    const char *bad = "this sentence is not fucking safe";
    
    printf("safe example - %d\n", banned_contains(safe));
    printf("bad example - %d\n", banned_contains(bad));

    banned_close();
    return 0;
}