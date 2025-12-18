/*
 * Exposes common functions for use in client and server
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
#include <stdio.h>
 
 /*
  * Requests user input with fgets and places it into the
  * input buffer after removing the newline character.
  */
char *strip_user_input(char *input_buffer, int buffer_size);

int send_and_receive(int connected_fd, struct pollfd fds[], char *username, int CLIENT, FILE *chat_log);