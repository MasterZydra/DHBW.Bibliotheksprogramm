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
void getFileContent(char *fileName, void (*readNewLineEvent) (const char *)) {
    FILE *file;
    int datalen = 1000;
    char data[datalen];
    char *filecont;
    
    // Open file
    file = fopen(fileName, "r");
    
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
