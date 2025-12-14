#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>

int main() {

    if (banned_init("banned/banned_words.txt") == -1) { // loading the banned words from file
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
        AF_INET,
        htons(9999),
        0
    };

    // Connect to the server listening on port 9999.
    // The OS automatically assigns a temporary (ephemeral) client port.
    connect(sockfd, (struct sockaddr *)&address, sizeof(address));

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

    for (;;) {
        char buffer[256] = { 0 };

        // Wait until either stdin or the socket has data
        poll(fds, 2, 30000);

        // If there is input from stdin, read it and send it to the server
        if (fds[0].revents & POLLIN) {
            read(0, buffer, 255);             // read from keyboard
            send(sockfd, buffer, 255, 0);     // write to server socket
        }
        // If there is data from the server, read it and print it
        else if (fds[1].revents & POLLIN) {
            // recv() == 0 means the server closed the connection
            if (recv(sockfd, buffer, 255, 0) == 0) {
                return 0;
            }

            printf("%s\n", buffer);
        }
    }

    return 0;
}
