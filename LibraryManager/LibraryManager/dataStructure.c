//
//  dataStructure.c
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 26.02.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#include "dataStructure.h"

void freeSubBookData(char **charPP) {
    for (int i=0; charPP[i] != NULL; i++)
        free(charPP[i]);
    free(charPP);
}

void freeBookData(bookData **bds) {
    for (bookData *bd = bds[0]; bd != NULL; bd++) {
        freeSubBookData(bd->author);
        freeSubBookData(bd->borrowers);
        free(bd->isbn);
        free(bd->title);
        free(bd);
    }
}

char *allocMem(const char *data, int len) {
    char *retData = malloc(len + 1);
    memcpy(retData, data, (len + 1) * sizeof(char));
    return retData;
}
