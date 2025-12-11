#include <stdio.h>
#include "banned.h"

int main(void) {
    if (banned_init("banned_words.txt") != 0) {
        printf("did not load banned words list");
        return 1;
    }

    const char *test = "this is a test sentence iwth swear words yay";
    int result = banned_contains(test);

    printf("banned_contains(\"%s\") = %d\n", test, result);

    banned_close();
    return 0;
}