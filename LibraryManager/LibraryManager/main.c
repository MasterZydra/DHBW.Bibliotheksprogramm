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

#include <stdio.h>
#include <stdbool.h>
#include <string.h>



enum dataCol { dcISBN, dcTitle, dcAuthor, dcBorrower };


void getBorrower(const char *borrowers) {
    char delimiter[] = ";";
    char *sub;
    char curBorrower[strlen(borrowers)];
    
    strcpy(curBorrower, borrowers);
    
    // Init and create first section
    sub = strtok(curBorrower, delimiter);
    
    while (sub) {
        printf("Borrower: %s\n", sub);
        // Create next section
        sub = strtok(NULL, delimiter);
    }
}

void readNewLineEvent(const char *line) {
    char delimiter[] = "|";
    char *sub;
    char curLine[strlen(line)];
    
    enum dataCol dc = dcISBN;
    
    strcpy(curLine, line);
    
    // Init and create first section
    sub = strtok(curLine, delimiter);
    
    while (sub) {
        switch (dc) {
            case dcISBN:
                printf("\nISBN: %s\n", sub);
                break;
            case dcTitle:
                printf("Title: %s\n", sub);
                break;
            case dcAuthor:
                printf("Author: %s\n", sub);
                break;
            case dcBorrower:
                getBorrower(sub);
                break;
            default:
                printf("Other: %s\n", sub);
                break;
        }
        
        // Create next section
        sub = strtok(NULL, delimiter);
        dc++;
    }
}

int main(int argc, const char * argv[]) {
    

    
    getFileContent("./lib.bd", readNewLineEvent);
    printf("\n");
//    char* line = "";
//    FILE *data = fopen("lib.db", "rt");
////    fseek(data, 0, SEEK_SET);
//
//
//    while (!feof(data)) {
//        printf("Res: %s\n", fgets(line, 100000, data));
//        printf("Text: %s\n", line);
//    }
    
    
    return 0;
    
//    char a = getchar();
//    if (a == 10) printf("is 10\n");
//    if (a == '\n') printf("is /n\n");
//    printf("%d\n", a);
//    int test, test2;
//    printf("number:");
//    terminalInput("%d %d", &test, &test2);
//    printf("Input: %d %d\n", test, test2);
    
  //  return 0;
//    while (mainMenu() != 0) {};
//    return 0;
    
    // Ideen:
    // Einstellungen
    //   - Mehrsprachigkeit
    //   - 
}
