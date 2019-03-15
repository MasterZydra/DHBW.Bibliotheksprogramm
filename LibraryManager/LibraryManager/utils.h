//
//  utils.h
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 14.03.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

// Functions for managing the terminal
int terminalInput(const char *, ...);

void clear_inputBuffer(void);

void clear_screen(void);

// Functions for strings
void addStrAtPos(char*, char*, int *);

void addCharToPos(char, char*, int *);

int countStrings(char **);

void strToLower(char *, char *);

// Functions for memory handling
char *allocMem(const char *, int);

void freeSubBookData(char ***);

void getSubList(char ***, char *);

void *reallocMemCalloc(void *, int, int, int);

void removeSubstring(char ***, char *);

void addSubstring(char ***, char *);

#endif /* utils_h */
