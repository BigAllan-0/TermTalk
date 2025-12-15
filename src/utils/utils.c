/*
 * Defines useful functions common between both client and server
 */
#include "../banned/banned.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char *strip_user_input(char *input_buffer, int buffer_size) {
    printf("Please input your username: ");
    fgets(input_buffer, buffer_size, stdin);
    input_buffer[strcspn(input_buffer, "\n")] = '\0';
}

int send_and_receive(int connected_fd, struct pollfd fds[], char *username, int CLIENT) {
        
    char buffer[256] = { 0 };

        // Wait until either stdin or the socket has data
        poll(fds, 2, 30000);

        // If there is input from stdin, read it and send it to the server
        if (fds[0].revents & POLLIN) {
            char msg[192] = { 0 }; // initializing space for message
            char check_msg[192] = { 0 };
            if (fgets(msg, sizeof(msg), stdin) == NULL) {
                return 0;
            }

            snprintf(buffer, (sizeof(buffer) - 3), "%s: %s", username, msg);
            strcpy(check_msg, buffer);
            check_msg[strcspn(buffer, "\n")] = '\0'; // omg theres a reject function!!

            if (banned_contains(check_msg) && CLIENT) {
                char banned_msg[256];
                snprintf(banned_msg, sizeof(banned_msg), "%s said a bad word and has been disconnected\n", username);
                send(connected_fd, banned_msg, strlen(banned_msg), 0);

                close(connected_fd);  // close the connection
                printf("you said a no-no word. bye.\n");
                exit(0);  // quit the client
            }

            if (send(connected_fd, buffer, strlen(buffer), 0) <= 0) { // write to server socket
                printf("Cannot send to client; connection closed.\n");
                return 0;
            }
        }
        // If there is data from the server, read it and print it
        if (fds[1].revents & POLLIN) {
            // recv() == 0 means the server closed the connection
            if (recv(connected_fd, buffer, sizeof(buffer), 0) == 0) {
                return 0;
            }
            printf("%s", buffer);
        }
        return 1;
    }