//
//  terminalUtils.h
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 26.01.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#ifndef terminalUtils_h
#define terminalUtils_h

#include <stdio.h>
#include <stdarg.h>

int terminalInput(const char *, ...);

void clear_inputBuffer(void);

void clear_screen(void);

#endif /* terminalUtils_h */
