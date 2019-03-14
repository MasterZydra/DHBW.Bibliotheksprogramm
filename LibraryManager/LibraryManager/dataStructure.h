//
//  dataStructure.h
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 26.02.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#ifndef dataStructure_h
#define dataStructure_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

typedef struct {
    char *isbn;
    char *title;
    char **author;
    int amount;
    char **borrowers;
    int sortOrder;
} bookData;

void freeBookData(bookData ***);

void printBookData(bookData **);

int countBooks(bookData **books);

char *bookDataToCSV(bookData **);

int bookCompare(const void *, const void *);

void sortBooks(bookData **books);

#endif /* dataStructure_h */
