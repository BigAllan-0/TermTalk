#pragma once

// LOads the banned words from a file (banned_words.txt, one word per line)
// Returns a 0 if loaded successfully, but a -1 if fails to load
int banned_init(const char *filename);


void banned_close(void);

// Returns a 1 if 'msg' contains banned words(s), otherwise will return a 0
int banned_contains(const char *msg);