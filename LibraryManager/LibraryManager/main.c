//
//  main.c
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 26.01.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#include "terminalUtils.h"
#include "menus.h"
#include "programlogic.h"
#include "fileUtils.h"
#include "searchUtils.h"
#include "dataStructure.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int bookCompare(const void *p1, const void *p2) {
    if (((bookData *)p1)->sortOrder < ((bookData *)p2)->sortOrder) return 1;
    if (((bookData *)p1)->sortOrder > ((bookData *)p2)->sortOrder) return -1;
    return 0;
}

void sortBooks(bookData **books) {
    qsort(books, countBooks(books), sizeof(bookData*), bookCompare);
}

int main(int argc, const char * argv[]) {
    bookData **data = calloc(1, sizeof(bookData**));
    readFile(&data, "./lib.bd", readNewLineEvent);
    
    sortBooks(data);
    
    
    
    
    printListMenu(data);
    
//        for (int curPos = 0; data[curPos] != NULL; curPos++)
//            printf("%s\n", data[curPos]->title);
    
    freeBookData(&data);
    return 0;
    
    
//    // Allocate memory for bookData array
//    bookData **data = calloc(1, sizeof(bookData**));
//    // Read content from file
//    readFile(&data, "./lib.bd", readNewLineEvent);
//    // Print content from data struct to console
//    printBookData(data);
//    // Test to write data
//    char *bookDataCSV = bookDataToCSV(data);
//    writeFile("./test.txt", bookDataCSV);
//    // Free allocated memory
//    freeBookData(&data);
//    return 0;
    
//    char a = getchar();
//    if (a == 10) printf("is 10\n");
//    if (a == '\n') printf("is /n\n");
      //  return 0;
    
    
    mainMenu();
    return 0;
    
    // Ideen:
    // Einstellungen
    //   - Mehrsprachigkeit
    //   - 
}
