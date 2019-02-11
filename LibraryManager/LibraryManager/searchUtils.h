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

enum searchCol { scAll, scISBN, scTitle, scAuthor, scBorrower };
typedef enum searchCol searchCol_t;

// Get minimum of 3 values
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

int levenshtein(const char *, const char *);

#endif /* searchUtils_h */
