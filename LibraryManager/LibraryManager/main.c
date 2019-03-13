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

int main(int argc, const char * argv[]) {
    bookData **data = calloc(1, sizeof(bookData**));
    readFile(&data, "./lib.bd", readNewLineEvent);
    printBookData(data);
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
