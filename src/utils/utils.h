/*
 * Exposes common functions for use in client and server
 */

 
 /*
  * Requests user input with fgets and places it into the
  * input buffer after removing the newline character.
  */
char *strip_user_input(char *input_buffer, int buffer_size);