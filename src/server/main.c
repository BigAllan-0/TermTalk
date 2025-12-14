<<<<<<< HEAD
#include "../banned/banned.h"

=======
#include "../utils/utils.h"
>>>>>>> 7ef5d2b2be8e890f1e719047c857a53d86853567
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <string.h>

const int MAX_USERNAME_LENGTH = 64;

int main() {
<<<<<<< HEAD

    if (banned_init("banned/banned_words.txt") == -1) { // loading the banned words from file
    printf("Could not load banned words.\n");
    return 1;
    }
=======
    char username[MAX_USERNAME_LENGTH];
    #ifndef ASK_USERNAME
        #define ASK_USERNAME
        strip_user_input(username, MAX_USERNAME_LENGTH);
    #endif
>>>>>>> 7ef5d2b2be8e890f1e719047c857a53d86853567

    // Creates a TCP socket (AF_INET = IPv4, SOCK_STREAM = TCP)
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Fill in the server address:
    // AF_INET       -> using IPv4
    // htons(9999)   -> convert port 9999 from host byte order to network byte order
    // 0             -> IP address 0.0.0.0 (INADDR_ANY) when used with bind()
    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_port = htons(9999),
        .sin_addr.s_addr = htonl(INADDR_ANY)
    };

    // Bind this socket to port 9999 on all local interfaces (0.0.0.0:9999)
    bind(sockfd, (struct sockaddr *)&address, sizeof(address));

    // Start listening for incoming TCP connection requests on port 9999
    listen(sockfd, 10);

    // Accept one incoming connection.
    // sockfd stays as the listening socket; clientfd is the connected socket.
    int clientfd = accept(sockfd, NULL, NULL);

    // stdin is file descriptor 0
    // Set up poll() to watch:
    // - fds[0]: stdin (keyboard input)
    // - fds[1]: clientfd (data from the connected client)
    struct pollfd fds[2] = {
        {
            0,        // fd: stdin
            POLLIN,   // events: wait for data to read
            0
        },
        {
            clientfd, // fd: connected client socket
            POLLIN,   // events: wait for data to read
            0
        }
    };

    for (;;) {
        fflush(stdout);
        char buffer[256] = { 0 };

        // Wait until either stdin or the client socket has data
        poll(fds, 2, 30000);

        // If there is input from stdin, read it and send it to the client
        if (fds[0].revents & POLLIN) {
            char msg[192] = { 0 };
            if (fgets(msg, sizeof(msg), stdin) == NULL) {
                return 0;
            }
            snprintf(buffer, (sizeof(buffer) - 3), "%s: %s", username, msg);
            send(clientfd, buffer, strlen(buffer), 0);       // write to client socket
        }
        // If there is data from the client, read it and print it
        if (fds[1].revents & POLLIN) {
            // recv() == 0 means the client closed the connection
            if (recv(clientfd, buffer, sizeof(buffer), 0) == 0) {
                return 0;
            }
            
            printf("%s", buffer);
        }
    }

    return 0;
}
