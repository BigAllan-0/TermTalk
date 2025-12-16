#include "../banned/banned.h"
#include "../utils/utils.h"

#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <string.h>

const int MAX_USERNAME_LENGTH = 64;

int main() {

    if (banned_init("../banned/banned_words.txt") == -1) { // loading the banned words from file
        printf("Could not load banned words.\n");
        return 1;
    }

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

    // prevent reuse of the socket and address so i can re-run server quickly
    int reuse = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1) {
        error("Socket reuse failed");
    };

    // Bind this socket to port 9999 on all local interfaces (0.0.0.0:9999)
    if (bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return 1;
    }

    // Start listening for incoming TCP connection requests on port 9999
    if (listen(sockfd, 10) == -1) { // listen queue length is 10
        perror("listen failed");
        return 1;
    }

    char username[MAX_USERNAME_LENGTH];
    strip_user_input(username, MAX_USERNAME_LENGTH);

    

    while (1) {
        // Accept one incoming connection.
        // sockfd stays as the listening socket; clientfd is the connected socket.
        printf("Waiting for a new client to join. Any messages you send now will be relayed to the next client\n");
        int clientfd = accept(sockfd, NULL, NULL);
        printf("New client connected!\n");

        // stdin is file descriptor
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

        while (1) {
            fflush(stdout);
            if (!send_and_receive(clientfd, fds, username, 0)) {
                break;
            }
        }
    }

    return 0;
}
