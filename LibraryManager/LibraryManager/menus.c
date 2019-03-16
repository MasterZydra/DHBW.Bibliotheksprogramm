//
//  menus.c
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 28.01.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#include "menus.h"

/**
 Print main menu
 */
void printMainMenu() {
    clear_screen();
    TITLE();
    MAINMENU();
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
void printSearchMenuText(searchCol sc) {
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

/**
 Print list menu with search results

 @param listData Array of books which will be shown
 */
void printListMenu(bookData **listData)
{
    clear_screen();
    TITLE();
    LIST_HEADLINE();

    for (int i=0; (i < 9) && (listData[i] != NULL);i++) {
        // Trim length of title
        char title[28];
        int titleLen = (int)strlen(listData[i]->title);
        memcpy(&title, listData[i]->title, (titleLen > 27) ? 27 : titleLen);
        title[27] = '\0';
        // Print number and title
        printf(" %d | %-27s|", i+1, title);
        // Build string contains authors with max length of 29
        char *authors = malloc(31 * sizeof(char));
        for (int j = 0; (listData[i]->author)[j] != NULL; j++) {
            if (j == 0) {
                int len = (int)strlen((listData[i]->author)[j]) + 1;
                memcpy(authors, listData[i]->author[j], ((len < 29) ? len : 28) );
            }
            else {
                int len = (int)strlen(authors);
                // Check length before adding another author
                if (len > 27) break;
                // Add another author
                addCharToPos(',', authors, &len);
                addCharToPos(' ', authors, &len);
                memcpy(&authors[len], listData[i]->author[j], 30 - len);
            }
        }
        authors[30] = '\0';
        // Print rest of columns: authors, isbn, amount
        printf(" %-29s| %-13s | %3d |\n",
               authors,
               listData[i]->isbn,
               listData[i]->amount - countStrings(listData[i]->borrowers));
        free(authors);
    }
    printf("\n");
    
    BACK();
    MENU_FINISHLINE();
    LIST_MENU();
    MENU_INPUT();
}

/**
 Print data of one book

 @param selectedBook Pointer to bookData
 */
void printSelectedBookData(bookData *selectedBook)
{
    clear_screen();
    TITLE();
    // Title
    printf("Titel:             %s\n",selectedBook->title);
    // All authors
    printf("Autor:             %s",selectedBook->author[0]);
    for (int i = 1; selectedBook->author[i] != NULL; i++)
         printf(", %s",selectedBook->author[i]);
    printf("\n");
    // ISBN
    printf("ISBN:              %s\n",selectedBook->isbn);
    // Amount
    printf("Verf%cgbare B%ccher: %d\n", ue, ue, selectedBook->amount - countStrings(selectedBook->borrowers));
    // All borrowers
    printf("Ausleiher:         ");
    if (selectedBook->borrowers[0] != NULL)
        printf("%s", selectedBook->borrowers[0]);
    for (int i = 1; selectedBook->borrowers[i] != NULL; i++)
        printf(", %s", selectedBook->borrowers[i]);
    printf("\n\n");
    
    BACK();
    SELECTEDBOOK_MENU();
    MENU_FINISHLINE();
    MENU_INPUT();
}


/**
 
 */
void printRemoveBook() {
    clear_screen();
    TITLE();
    REMOVE_BOOK();
}

void printAddBook() {
    clear_screen();
    TITLE();
    ADD_BOOK();
}
