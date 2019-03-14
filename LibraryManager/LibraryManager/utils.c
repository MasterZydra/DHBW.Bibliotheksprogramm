//
//  utils.c
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 14.03.19.
//  Copyright © 2019 David Hein & Fleix Hieser. All rights reserved.
//

#include "utils.h"

/**
 Read input with given format and empty keyboard buffer afterwards.
 Use it like scanf().
 
 @param format Format of input
 @param ... List of all pointers of variables to fill
 @return Number of read parameters
 */
int terminalInput(const char *format, ...) {
    int count = 0;
    va_list args;
    // Pass variable parameters
    va_start(args, format);
    // Do scanf
    count = vfscanf(stdin, format, args);
    va_end(args);
    // Clear input buffer after input processing
    clear_inputBuffer();
    return count;
}

/**
 Clearing input buffer
 */
void clear_inputBuffer()
{
    char c;
    while ( (c = getchar()) != '\n' && c != EOF);
}

/**
 Clear terminal window
 */
void clear_screen()
{
#ifdef WINDOWS
    system("cls");
#endif
#ifdef __APPLE__
    system ("clear");
#endif
}

/**
 Insert a string into CSV string
 
 @param src String to insert
 @param dst CSV string
 @param cursorPos Current cursor position
 */
void addStrAtPos(char* src, char* dst, int *cursorPos) {
    int len = (int)strlen(src);
    memcpy(&(dst[*cursorPos]), src, len);
    *cursorPos = *cursorPos + len;
}

/**
 Insert one character into CSV string
 
 @param src Character to insert
 @param dst CSV string
 @param cursorPos Current cursor position
 */
void addCharToPos(char src, char* dst, int *cursorPos) {
    dst[*cursorPos] = src;
    (*cursorPos)++;
}
