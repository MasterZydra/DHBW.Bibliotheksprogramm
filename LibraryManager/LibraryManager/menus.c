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
}
