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






void getSubList(char **dataList, const char *dataLine) {
    char delimiter[] = ";";
    char *sub;
    char curDataLine[strlen(dataLine)];
    
    strcpy(curDataLine, dataLine);
    
    // Init and create first section
    sub = strtok(curDataLine, delimiter);
    int cnt = 0;
    while (sub) {
        if (cnt == 0) {
            dataList = malloc(sizeof(char**));
        }
        else {
            dataList = realloc(dataList, sizeof(char**) * (cnt + 1));
        }
        dataList[cnt] = allocMem(sub, (int)strlen(sub));
        
        printf("Sub-Item: %s\n",dataList[cnt]);
        // Create next section
        sub = strtok(NULL, delimiter);
        cnt++;
    }
}

void readNewLineEvent(bookData **books, const char *line) {
    char delimiter[] = "|";
    char *sub;
    char curLine[strlen(line)];
    
    dataCol dc = dcISBN;
    
    strcpy(curLine, line);
    // Init and create first section
    sub = strtok(curLine, delimiter);
    if (books[0] == NULL) books[0] = malloc(sizeof(bookData));
    while (sub) {
        switch (dc) {
            case dcISBN:
                books[0]->isbn = allocMem(sub, (int)strlen(sub));
                printf("\nISBN: %s\n", books[0]->isbn);
                break;
            case dcTitle:
                books[0]->title = allocMem(sub, (int)strlen(sub));
                printf("Title: %s\n", books[0]->title);
                break;
            case dcAuthor:
                getSubList(books[0]->author, sub);
                break;
            case dcAmount:
                books[0]->amount = (int) strtol(sub, (char **)NULL, 10);
                printf("Amount: %d\n", books[0]->amount);
                break;
            case dcBorrower:
                getSubList(books[0]->borrowers, sub);
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
    bookData **data = calloc(1, sizeof(bookData**));
//    writeFile("./lib.bbd", "abch?\nHallo wie geht es dir?");
    readFile(data, "./lib.bd", readNewLineEvent);
    return 0;
    
    freeBookData(data);
    
    //freeBookData(data);
//    printf("\n");
//    return 0;
    
//    char a = getchar();
//    if (a == 10) printf("is 10\n");
//    if (a == '\n') printf("is /n\n");
      //  return 0;
    
    
   // mainMenu();
    return 0;
    
    // Ideen:
    // Einstellungen
    //   - Mehrsprachigkeit
    //   - 
}
