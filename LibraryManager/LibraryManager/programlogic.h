//
//  programlogic.h
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 28.01.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#ifndef programlogic_h
#define programlogic_h

#include <stdio.h>
#include <stdbool.h>

#include "terminalUtils.h"
#include "searchUtils.h"
#include "dataStructure.h"

int mainMenu(void);

void searchMenu(bool);

int searchMenuText(bool, searchCol);

int searchListMenu(bookData **);

int selectedBookMenu(bookData *);

#endif /* programlogic_h */
