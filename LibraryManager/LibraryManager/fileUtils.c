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
    FILE *file = fopen(fileName, "w");
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
    *books = (bookData **)reallocMemCalloc(*books, curPos + 2, sizeof(bookData*), curPos + 1);
    // Allocate space for one book
    (*books)[curPos] = malloc(sizeof(bookData));
    // Save data in struct
    while (sub) {
        switch (dc) {
            case dcISBN:
                (*books)[curPos]->isbn = allocMem(sub, (int)strlen(sub) + 1);
                break;
            case dcTitle:
                (*books)[curPos]->title = allocMem(sub, (int)strlen(sub) + 1);
                break;
            case dcAuthor:
                authors = allocMem(sub, (int)strlen(sub) + 1);
                break;
            case dcAmount:
                (*books)[curPos]->amount = (int) strtol(sub, (char **)NULL, 10);
                break;
            case dcBorrower:
                borrowers = allocMem(sub, (int)strlen(sub) + 1);
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
