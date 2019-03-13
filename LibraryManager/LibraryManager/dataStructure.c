//
//  dataStructure.c
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 26.02.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#include "dataStructure.h"

/**
 Free Char Pointer Pointer

 @param charPP Storage to free
 */
void freeSubBookData(char **charPP) {
    for (int i=0; charPP[i] != NULL; i++)
        free(charPP[i]);
    free(charPP);
}

/**
 Free storage that is reserved for book data

 @param bds Pointer to array of book data
 */
void freeBookData(bookData **bds) {
    for (bookData *bd = bds[0]; bd != NULL; bd++) {
        freeSubBookData(bd->author);
        freeSubBookData(bd->borrowers);
        free(bd->isbn);
        free(bd->title);
        free(bd);
    }
}

/**
 Allocate memory and fill it with content

 @param data Pointer to text
 @param len Length of text
 @return Pointer to memory area
 */
char *allocMem(const char *data, int len) {
    char *retData = malloc(len + 1);
    memcpy(retData, data, (len + 1) * sizeof(char));
    return retData;
}

/**
 Split text on delimiter and save data in pointer array

 @param dataList Pointer to pointer array
 @param dataLine Text to split
 */
void getSubList(char ***dataList, char *dataLine) {
    char delimiter[] = ";";
    int cnt = 0;
    char *sub;
    // Init and create first section
    sub = strtok(dataLine, delimiter);
    while (sub) {
        if (cnt == 0) {
            *dataList = calloc(2, sizeof(char**));
        }
        else {
            // Allocate new memory area and copy content into it
            char **old = *dataList;
            *dataList = calloc(cnt + 2, sizeof(char**));
            memcpy(*dataList, old, sizeof(char**) * (cnt + 1));
            free(old);
        }
        (*dataList)[cnt] = allocMem(sub, (int)strlen(sub));
        // Create next section
        sub = strtok(NULL, delimiter);
        cnt++;
    }
}

/**
 Print data in bookData pointer pointer

 @param books BookData pointer pointer
 */
void printBookData(bookData **books) {
    clear_screen();
    int curPos = 0;
    int i;
    for (bookData *bd = *books; bd != NULL; bd = books[curPos]) {
        printf("Book %i\n", curPos + 1);
        printf("  Titel: %s\n", bd->title);
        printf("  ISBN: %s\n", bd->isbn);
        printf("  Amount: %i\n", bd->amount);
        i = 0;
        for(char *c = *(bd->author); c != NULL && c != 0; c = bd->author[i]) {
            printf("  Author %i: %s\n", i+1, c);
            i++;
        }
        i = 0;
        for(char *c = *(bd->borrowers); c != NULL && c != 0; c = bd->borrowers[i]) {
            printf("  Borrower %i: %s\n", i+1, c);
            i++;
        }
        printf("  SortOrder: %i\n", bd->sortOrder);
        printf("\n");
        curPos++;
    }
}
