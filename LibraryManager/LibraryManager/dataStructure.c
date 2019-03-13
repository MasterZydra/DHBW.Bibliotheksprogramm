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
void freeSubBookData(char ***charPP) {
    for (int i=0; (*charPP)[i] != NULL; i++)
        free((*charPP)[i]);
    free(*charPP);
}

/**
 Free storage that is reserved for book data

 @param bds Pointer to array of book data
 */
void freeBookData(bookData ***bds) {
    for (int i = 0; (*bds)[i] != NULL; i++){
        freeSubBookData(&(*bds)[i]->author);
        freeSubBookData(&(*bds)[i]->borrowers);
        free((*bds)[i]->isbn);
        free((*bds)[i]->title);
        free((*bds)[i]);
    }
    free(*bds);
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
    for (bookData *bd = *books; bd != NULL; bd = books[curPos]) {
        printf("Book %i\n", curPos + 1);
        printf("  Titel: %s\n", bd->title);
        printf("  ISBN: %s\n", bd->isbn);
        printf("  Amount: %i\n", bd->amount);
        for(int i = 0; (bd->author)[i] != NULL; i++) {
            printf("  Author %i: %s\n", i+1, (bd->author)[i]);
        }
        for(int i = 0; (bd->borrowers)[i] != NULL; i++) {
            printf("  Borrower %i: %s\n", i+1, (bd->borrowers)[i]);
        }
        printf("  SortOrder: %i\n", bd->sortOrder);
        printf("\n");
        curPos++;
    }
}
