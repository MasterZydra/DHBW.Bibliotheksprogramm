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
void readFile(char *fileName, void (*readNewLineEvent) (const char *)) {
    int datalen = 100;
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
        readNewLineEvent(filecont);
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
