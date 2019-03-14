//
//  programlogic.c
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 28.01.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#include "programlogic.h"
#include "menus.h"

/**
 Logic and output for main menu
 */
void mainMenu() {
    char input = ' ';
    bool manageMode = false;

    while (true) {
        printMainMenu(manageMode);

        terminalInput("%c", &input);

        switch (input) {
            case '0': return;
            case '1':
                // Search book
                searchMenu(manageMode);
                break;

            default:
                break;
        }
    }
    return;
}

/**
 Menu for searching books

 @param manageMode User is logged in
 */
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

/**
 Menu for input of search text

 @param manageMode User is logged in
 @param sc Columns in which will be searched in
 @return 0 = Ok, 1 = Break
 */
int searchMenuText(bool manageMode, searchCol sc) {
    char input[100];
    printSearchMenuText(sc);
    terminalInput("%s", &input);
    if (strcmp(input, "0") == 0) return 1;
    // search ...

    return 0;
}

/**
 List books and let user select one and show more details

 @param listData BookData array
 @return 0 = Ok
 */
int listMenu(bookData **listData) {
    char input = ' ';

    while (true) {
        printListMenu(listData);

        terminalInput("%c", &input);

        if (input == '0') return 0;
        if (input >= '1' && input <= '9') selectedBookMenu(listData[input - '1']);
    }
    return 0;
}

/**
 Show details of one book

 @param selectedBook BookData array
 @return 0 = Ok
 */
int selectedBookMenu(bookData *selectedBook) {
    char input = ' ';

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
