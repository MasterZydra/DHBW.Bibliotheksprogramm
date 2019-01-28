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
    bool manageMode = true;
    printMainMenu(manageMode);
    
    getchar();
    
    return 0;
}
