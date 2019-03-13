//
//  fileUtils.c
//  LibraryManager
//
//  Created by David Hein on 28.01.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#include "fileUtils.h"

/**
 Read file and trigger event for each line.

 @param fileName Name of file
 @param readNewLineEvent Function which processes line
 */
void readFile(bookData ***books, char *fileName, void (*readNewLineEvent) (bookData ***, const char *)) {
    int datalen = 300;
    char data[datalen];
    char *filecont;
    // Open file
    FILE *file = fopen(fileName, "r");
    // Error message if no file opened
    if(file == NULL) {
        perror("File");
        return;
    }
    // Read each line and trigger readNewLine event
    for(; (filecont = fgets(data, datalen,file)) ;) {
        filecont[strlen(filecont) - 1] = 0;
        readNewLineEvent(books, filecont);
    }
    // Finally close file
    fclose(file);
}

/**
 Write given data to file

 @param fileName Name of file
 @param data Data to write into file
 */
void writeFile(char *fileName, const char *data) {
    char buffer[strlen(data) + 1];
    // Open file
    FILE *file = fopen(fileName, "wb");
    // Error message if no file opened
    if(file == NULL) {
        perror("File");
        return;
    }
    // Copy data to buffer
    strcpy(buffer, data);
    buffer[strlen(data) + 1] = 0;
    // Write data to file
    fwrite(buffer, sizeof(buffer), 1, file);
    // Finally close file
    fclose(file);
}

/**
 Gets one data line from file and saves it content into the
 data structure.

 @param books Pointer of Pointer of book array
 @param line Pointer of line
 */
void readNewLineEvent(bookData ***books, const char *line) {
    // Check if line is not empty
    if (strlen(line) == 0) return;
    
    char *authors = 0;
    char *borrowers = 0;
    int curPos = 0;
    dataCol dc = dcISBN;
    // Create copy of line
    char curLine[strlen(line)];
    strcpy(curLine, line);
    // Init and create first section
    char delimiter[] = "|";
    char *sub = strtok(curLine, delimiter);
    // Find last filled book struct
    for (curPos = 0; (*books)[curPos] != NULL; curPos++);
    // Increase size of book array
    bookData **oldPointer = *books;
    *books = (bookData **)calloc(curPos + 2, sizeof(bookData*));
    memcpy(*books, oldPointer, sizeof(bookData*) * (curPos + 1));
    free(oldPointer);
    // Allocate space for one book
    (*books)[curPos] = malloc(sizeof(bookData));
    // Save data in struct
    while (sub) {
        switch (dc) {
            case dcISBN:
                (*books)[curPos]->isbn = allocMem(sub, (int)strlen(sub));
                break;
            case dcTitle:
                (*books)[curPos]->title = allocMem(sub, (int)strlen(sub));
                break;
            case dcAuthor:
                authors = allocMem(sub, (int)strlen(sub));
                break;
            case dcAmount:
                (*books)[curPos]->amount = (int) strtol(sub, (char **)NULL, 10);
                break;
            case dcBorrower:
                borrowers = allocMem(sub, (int)strlen(sub));
                break;
            default:
                printf("Error: Column will not be processed: '%s'\n", sub);
                break;
        }
        // Create next section
        sub = strtok(NULL, delimiter);
        dc++;
    }
    // Process authors and save in struct
    if (authors != NULL) {
        getSubList(&(*books)[curPos]->author, authors);
        free(authors);
    }
    // Process borrowers and save in struct
    if (borrowers != NULL) {
        getSubList(&(*books)[curPos]->borrowers, borrowers);
        free(borrowers);
    }
    (*books)[curPos]->sortOrder = curPos + 1;
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
 Saves content in struct into CSV

 @param books Pointer to BookData array
 @return Pointer to Memory with CSV string
 */
char *bookDataToCSV(bookData **books) {
    char* csv = malloc(sizeof(char) * 999);
    int cursorPos = 0;
    for (int curPos = 0; books[curPos] != NULL; curPos++) {
        // ISBN
        addStrAtPos(books[curPos]->isbn, csv, &cursorPos);
        addCharToPos('|', csv, &cursorPos);
        // Title
        addStrAtPos(books[curPos]->title, csv, &cursorPos);
        addCharToPos('|', csv, &cursorPos);
        // Author
        for (int i = 0; (books[curPos]->author)[i] != NULL; i++) {
            addStrAtPos((books[curPos]->author)[i], csv, &cursorPos);
            addCharToPos(';', csv, &cursorPos);
        }
        addCharToPos('|', csv, &cursorPos);
        // Amount - Convert int to char*
        char *amount = malloc(sizeof(char) * 5);
        sprintf(amount, "%d", books[curPos]->amount);
        addStrAtPos(amount, csv, &cursorPos);
        free(amount);
        addCharToPos('|', csv, &cursorPos);
        // Borrower
        for (int i = 0; (books[curPos]->borrowers)[i] != NULL; i++) {
            addStrAtPos((books[curPos]->borrowers)[i], csv, &cursorPos);
            addCharToPos(';', csv, &cursorPos);
        }
        // Linebreak
        addCharToPos('\n', csv, &cursorPos);
    }
    addCharToPos('\0', csv, &cursorPos);
    return csv;
}
