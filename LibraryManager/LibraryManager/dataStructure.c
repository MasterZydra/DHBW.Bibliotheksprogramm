//
//  dataStructure.c
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 26.02.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#include "dataStructure.h"

void freeBorrowers(char **borrowers) {
    for (int i=0; borrowers[i] != NULL; i++)
        free(borrowers[i]);
    free(borrowers);
}

void freeBookData(bookData *bd) {
    free(bd->isbn);
    free(bd->title);
    free(bd->author);
    free(bd->borrowers);
    free(bd);
}

char *allocMem(const char *data, int len) {
    char *retData = malloc(len + 1);
    memcpy(retData, data, (len + 1) * sizeof(char));
    return retData;
}
