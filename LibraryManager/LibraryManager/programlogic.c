//
//  programlogic.c
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 28.01.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#include "programlogic.h"
#include "menus.h"



int mainMenu() {
    char input = ' ';
    bool manageMode = false;
    
    while (true) {
        printMainMenu(manageMode);
        
        terminalInput("%c", &input);
        
        switch (input) {
            case '0': return 0;
            case '1':
                // Search book
                searchMenu(manageMode);
                break;
                
            default:
                break;
        }
    }
    return 0;
}

void searchMenu(bool manageMode) {
    char input = ' ';
    while (true) {
        printSearchMenu();
        
        terminalInput("%c", &input);
        
        switch (input) {
            case '0': return;
            case '1':
                // Search in all
                if (searchMenuText(manageMode, scAll) == 0)
                    return;
                break;
            case '2':
                // Search in ISBN
                if (searchMenuText(manageMode, scISBN) == 0)
                    return;
                break;
            case '3':
                // Search in Title
                if (searchMenuText(manageMode, scTitle) == 0)
                    return;
                break;
            case '4':
                // Search in Author
                if (searchMenuText(manageMode, scAuthor) == 0)
                    return;
                break;

            default:
                break;
        }
    }
}

int searchMenuText(bool manageMode, searchCol_t sc) {
    char input[100];
    printSearchMenuText(sc);
    terminalInput("%s", &input);
    if (strcmp(input, "0") == 0) return 1;
    // search ...
    
    return 0;
}
