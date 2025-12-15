#include "../banned/banned.h"
#include "../utils/utils.h"
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <string.h>

const int MAX_USERNAME_LENGTH = 64; // -2 for length of string

int main() {

    if (banned_init("../banned/banned_words.txt") == -1) { // loading the banned words from file
        printf("Could not load banned words.\n");
        return 1;
    }

    // Create a TCP socket (AF_INET = IPv4, SOCK_STREAM = TCP)
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Fill in the server address:
    // AF_INET       -> using IPv4
    // htons(9999)   -> convert server port 9999 to network byte order
    // 0             -> IP address 0.0.0.0 (not ideal for a real client;
    //                  usually you'd use 127.0.0.1 or a real server IP)
    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_port = htons(9999),
        .sin_addr.s_addr = inet_addr("127.0.0.1")
    };

    // Connect to the server listening on port 9999.
    // The OS automatically assigns a temporary (ephemeral) client port.
    printf("Connecting to server...\n");
    if (connect(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("connect");
        return 1;
    }

    char username[MAX_USERNAME_LENGTH];
    strip_user_input(username, MAX_USERNAME_LENGTH);
    // stdin is file descriptor 0
    // Set up poll() to watch:
    // - fds[0]: stdin (keyboard input)
    // - fds[1]: sockfd (data from the server)
    struct pollfd fds[2] = {
        {
            0,        // fd: stdin
            POLLIN,   // events: wait for data to read
            0
        },
        {
            sockfd,   // fd: connected socket to the server
            POLLIN,   // events: wait for data to read
            0
        }
    };

    while (1) {
        fflush(stdout);
        send_and_receive(sockfd, fds, username);
    }

    return 0;
}
