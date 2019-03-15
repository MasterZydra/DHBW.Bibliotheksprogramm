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

// Manage structure
void removeBook(bookData ***, bookData *);

void freeBookDatas(bookData ***);

void freeBookData(bookData **);

// Help functions
void sortBooks(bookData **books);

int countBooks(bookData **books);

int bookCompare(const void *, const void *);

char *bookDataToCSV(bookData **);

#endif /* dataStructure_h */
