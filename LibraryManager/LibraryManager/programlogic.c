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

int searchMenuText(bool manageMode, searchCol sc) {
    char input[100];
    printSearchMenuText(sc);
    terminalInput("%s", &input);
    if (strcmp(input, "0") == 0) return 1;
    // search ...

    return 0;
}

/**
 List Menu Logic,
 after printing the incoming listData you can select a book from the List for further editing.

 @param listData
 */

int searchListMenu(**listData) {
    char input = ' ';
    bool manageMode = false;

    while (true) {
        printListMenu(&listData);

        terminalInput("%c", &input);

        switch (input) {
            case '0': return 0;
            case '1': selectedBookMenu(&listData[0]);
            case '2': selectedBookMenu(&listData[1]);
            case '3': selectedBookMenu(&listData[2]);
            case '4': selectedBookMenu(&listData[3]);
            case '5': selectedBookMenu(&listData[4]);
            case '6': selectedBookMenu(&listData[5]);
            case '7': selectedBookMenu(&listData[6]);
            case '8': selectedBookMenu(&listData[7]);
            case '9': selectedBookMenu(&listData[8]);

            default:
                break;
        }
    }
    return 0;
}


int selectedBookMenu(bookData *selectedBook) {
    char input = ' ';
    bool manageMode = false;

    while (true) {
        printSelectedBookData(selectedBook);

        terminalInput("%c", &input);

        switch (input) {
            case '0': return 0;


            default:
                break;
        }
    }
    return 0;
}
