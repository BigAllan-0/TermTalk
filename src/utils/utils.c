/*
 * Defines useful functions common between both client and server
 */
#include <stdio.h>
#include <string.h>

char *strip_user_input(char *input_buffer, int buffer_size) {
    printf("Please input your username: ");
    fgets(input_buffer, buffer_size, stdin);
    int size;
    size = strlen(input_buffer);
    input_buffer[size-1] = '\0';
}

void send_and_receive(pollfd fds) {
        char buffer[256] = { 0 };

        // Wait until either stdin or the socket has data
        poll(fds, 2, 30000);

        // If there is input from stdin, read it and send it to the server
        if (fds[0].revents & POLLIN) {
            char msg[192] = { 0 }; // initializing space for message
            if (fgets(msg, sizeof(msg), stdin) == NULL) {
                return 0;
            }
            snprintf(buffer, (sizeof(buffer) - 3), "%s: %s", username, msg);
            send(sockfd, buffer, strlen(buffer), 0);     // write to server socket
        }
        // If there is data from the server, read it and print it
        if (fds[1].revents & POLLIN) {
            // recv() == 0 means the server closed the connection
            if (recv(sockfd, buffer, sizeof(buffer), 0) == 0) {
                return 0;
            }

            printf("%s", buffer);
        }
    }

// int main() {
//     // request username:
//     char username[MAX_USERNAME_LENGTH];
//     strip_user_input(username);
//     for (int i = 0; i < strlen(username); i++){
//         printf("char %i: %c ", i, username[i]);
//     }
//     printf("The username you gave me was %s\n", username);
//   return 0;
// }