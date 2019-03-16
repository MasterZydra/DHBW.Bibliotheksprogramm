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
#include <stdbool.h>
#include <math.h>

#define AE (unsigned char)142
#define ae (unsigned char)132
#define OE (unsigned char)153
#define oe (unsigned char)148
#define UE (unsigned char)154
#define ue (unsigned char)129
#define ss (unsigned char)225

// Functions for managing the terminal
char *getLine(void);

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

// Other functions
bool isbnValidation(char *);

#endif /* utils_h */
