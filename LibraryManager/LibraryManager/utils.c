//
//  utils.c
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 14.03.19.
//  Copyright © 2019 David Hein & Fleix Hieser. All rights reserved.
//

#include "utils.h"

/**
 Read input with given format and empty keyboard buffer afterwards.
 Use it like scanf().
 
 @param format Format of input
 @param ... List of all pointers of variables to fill
 @return Number of read parameters
 */
int terminalInput(const char *format, ...) {
    int count = 0;
    va_list args;
    // Pass variable parameters
    va_start(args, format);
    // Do scanf
    count = vfscanf(stdin, format, args);
    va_end(args);
    // Clear input buffer after input processing
    clear_inputBuffer();
    return count;
}

/**
 Clearing input buffer
 */
void clear_inputBuffer()
{
    char c;
    while ( (c = getchar()) != '\n' && c != EOF);
}

/**
 Clear terminal window
 */
void clear_screen()
{
#ifdef WINDOWS
    system("cls");
#endif
#ifdef __APPLE__
    system ("clear");
#endif
}

/**
 Insert a string into CSV string
 
 @param src String to insert
 @param dst CSV string
 @param cursorPos Current cursor position
 */
void addStrAtPos(char* src, char* dst, int *cursorPos) {
    int len = (int)strlen(src);
    memcpy(&(dst[*cursorPos]), src, len);
    *cursorPos = *cursorPos + len;
}

/**
 Insert one character into CSV string
 
 @param src Character to insert
 @param dst CSV string
 @param cursorPos Current cursor position
 */
void addCharToPos(char src, char* dst, int *cursorPos) {
    dst[*cursorPos] = src;
    (*cursorPos)++;
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
 Free Char Pointer Pointer
 
 @param charPP Storage to free
 */
void freeSubBookData(char ***charPP) {
    for (int i=0; (*charPP)[i] != NULL; i++)
        free((*charPP)[i]);
    free(*charPP);
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
    // Return null if there is no data in line
    if (!sub) {
        *dataList = calloc(1, sizeof(char**));
        return;
    }
    while (sub) {
        if (cnt == 0) {
            *dataList = calloc(2, sizeof(char**));
        }
        else {
            // Allocate new memory area and copy content into it
            *dataList = (char **)reallocMemCalloc(*dataList, cnt + 2, sizeof(char**), cnt + 1);
        }
        (*dataList)[cnt] = allocMem(sub, (int)strlen(sub));
        // Create next section
        sub = strtok(NULL, delimiter);
        cnt++;
    }
}

/**
 Allocate memory of given size, copy data from old memory
 area into it and free old memory area.

 @param oldPointer Pointer to old data
 @param num Number of new elements
 @param sizeOfDataType Size of one element
 @param oldNum Number of old elements
 @return Pointer to new memory area
 */
void *reallocMemCalloc(void *oldPointer, int num, int sizeOfDataType, int oldNum) {
    void *newPointer = calloc(num, sizeOfDataType);
    memcpy(newPointer, oldPointer, sizeOfDataType * oldNum);
    free(oldPointer);
    return newPointer;
}

