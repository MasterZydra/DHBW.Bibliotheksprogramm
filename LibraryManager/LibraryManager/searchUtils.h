//
//  searchUtils.h
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 28.01.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#ifndef searchUtils_h
#define searchUtils_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "dataStructure.h"
#include "utils.h"

typedef enum {
    scAll, scISBN, scTitle, scAuthor, scBorrower
} searchCol;

// Get minimum of 3 values
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

char *findSubstring(char **, char *);

int determineSearchMatch(char *, char *);

bookData **searchBooks(searchCol, bookData **, char *);

int levenshtein(const char *, const char *);

#endif /* searchUtils_h */
