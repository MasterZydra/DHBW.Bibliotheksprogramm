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


void printTree(bookData **books) {
    clear_screen();
    int curPos = 0;
    int i;
    for (bookData *bd = *books; bd != NULL; bd = books[curPos]) {
        printf("Book %i\n", curPos + 1);
        printf("  Titel: %s\n", bd->title);
        printf("  ISBN: %s\n", bd->isbn);
        printf("  Amount: %i\n", bd->amount);
        i = 0;
        for(char *c = *(bd->author); c != NULL && c != 0; c = bd->author[i]) {
            printf("  Author %i: %s\n", i+1, c);
            i++;
        }
        i = 0;
        for(char *c = *(bd->borrowers); c != NULL && c != 0; c = bd->borrowers[i]) {
            printf("  Borrower %i: %s\n", i+1, c);
            i++;
        }
        printf("\n");
        curPos++;
    }
}

int main(int argc, const char * argv[]) {
    bookData **data = calloc(1, sizeof(bookData**));
    readFile(&data, "./lib.bd", readNewLineEvent);
    printTree(data);
    return 0;
//    writeFile("./lib.bbd", "abch?\nHallo wie geht es dir?");
//    freeBookData(data);
    
    //freeBookData(data);
//    printf("\n");
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
