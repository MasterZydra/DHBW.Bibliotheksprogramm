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

#include <stdio.h>
#include <stdbool.h>

int main(int argc, const char * argv[]) {
    while (mainMenu() != 0) {};
    return 0;
}
