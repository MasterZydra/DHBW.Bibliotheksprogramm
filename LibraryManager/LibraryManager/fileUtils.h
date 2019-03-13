//
//  fileUtils.h
//  LibraryManager
//
//  Created by David Hein on 28.01.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#ifndef fileUtils_h
#define fileUtils_h

#include <stdio.h>
#include <string.h>

#include "dataStructure.h"

typedef enum {
    dcISBN, dcTitle, dcAuthor, dcAmount, dcBorrower
} dataCol;

void readFile(bookData ***, char *, void (*readNewLineEvent) (bookData ***, const char *));

void writeFile(char *, const char *);

void readNewLineEvent(bookData ***, const char *);

#endif /* fileUtils_h */
