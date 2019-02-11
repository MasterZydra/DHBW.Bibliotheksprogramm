//
//  menus.c
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 28.01.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#include "menus.h"
#include "terminalUtils.h"

#include <stdlib.h>

/**
 Print main menu

 @param manageMode User is logged in
 */
void printMainMenu(bool manageMode) {
    clear_screen();
    TITLE();
    MAINMENU();
    if (manageMode) {
        MAINMENU_MANMODE();
    }
    else {
        MAINMENU_NOMANMODE();
    }
    MENU_FINISHLINE();
    MENU_INPUT();
}

/**
 Print search menu
 */
void printSearchMenu() {
    clear_screen();
    TITLE();
    BACK();
    SEARCHMENU();
    MENU_FINISHLINE();
    MENU_INPUT();
}

/**
 Print search menu input of search text

 @param sc columns which will be searched in.
 */
void printSearchMenuText(enum searchCol sc) {
    clear_screen();
    TITLE();
    BACK();

    switch (sc) {
        case scAll:
            SEARCHMENU_TEXT("Suchtext");
            break;
            
        case scISBN:
            SEARCHMENU_TEXT("ISBN");
            break;
            
        case scTitle:
            SEARCHMENU_TEXT("Titel");
            break;
            
        case scAuthor:
            SEARCHMENU_TEXT("Autor");
            break;
        
        case scBorrower:
            SEARCHMENU_TEXT("Ausleiher");
            break;
            
        default:
            perror("Search criteria is not implemented!");
            break;
    }
}
