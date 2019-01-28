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
 Clearing input buffer
 */
void clear_keyboardBuffer()
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
