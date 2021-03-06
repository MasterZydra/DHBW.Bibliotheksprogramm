//
//  main.c
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 26.01.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#include "utils.h"
#include "menus.h"
#include "programlogic.h"
#include "fileUtils.h"
#include "searchUtils.h"
#include "dataStructure.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    // Allocate memory for bookData array
    bookData **data = calloc(1, sizeof(bookData**));
    // Read content from file
    readFile(&data, "./lib.txt", readNewLineEvent);
    // Execute logic for main menu
    mainMenu(&data);
    // Test to write data
    char *bookDataCSV = bookDataToCSV(data);
    writeFile("./lib.txt", bookDataCSV);
    // Free allocated memory
    free(bookDataCSV);
    freeBookDatas(&data);
    return 0;
}
