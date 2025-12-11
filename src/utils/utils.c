/*
 * Defines useful functions common between both client and server
 */
#include <stdio.h>
#include <string.h>

/*
 * Defines useful functions common between both client and server
 */
const int MAX_USERNAME_LENGTH = 64;

char * strip_user_input(char *input_buffer) {
    fgets(input_buffer, MAX_USERNAME_LENGTH, stdin);
    int size;
    size = strlen(input_buffer);
    input_buffer[size-1] = '\0';
}

int main() {
    // request username:
    char username[MAX_USERNAME_LENGTH];
    strip_user_input(username);
    // fgets(username, MAX_USERNAME_LENGTH, stdin);
    // char username[4] = {'y', 'e', 's', '\0'};
    // request_username(&username); 
    for (int i = 0; i < strlen(username); i++){
        printf("char %i: %c ", i, username[i]);
    }
    printf("The username you gave me was %s\n", username);
  return 0;
}