//
//  terminalUtils.c
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 26.01.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#include "terminalUtils.h"

#include <stdlib.h>

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
