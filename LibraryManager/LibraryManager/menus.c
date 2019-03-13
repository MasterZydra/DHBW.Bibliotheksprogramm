//
//  menus.c
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 28.01.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#include "menus.h"
#include "terminalUtils.h"
#include "dataStructure.h"
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

 @param listData whole available sorted Booklist
 */

void printListMenu(bookData **listData)
{
    clear_screen();
    TITLE();
    LIST_HEADLINE();

    for (int i=0;i<=9&&listData[i]!=NULL;i++)
    {
        printf("%d|",i+1);
        printf("%-25s|",listData[i]->title);

        printf("%-10s",listData[i]->author[0]);
        for (int j=1;j <=listData[i]->author[sizeof(listData[i]->author)/sizeof(char*)-1]&&j<=3;j++)
        {
            printf(", %-10s",listData[i]->author[j]);
        }
        printf("|");
        printf("%s|",listData[i]->isbn);
        printf("%-10d|",listData[i]->amount);
    }
    BACK();
    MENU_FINISHLINE();
    LIST_MENU();
}

void printSelectedBookData (bookData *selectedBook)
{
    clear_screen();
    TITLE();


    printf("Titel:             %s\n",selectedBook->title);
    printf("Author:            %s",selectedBook->author[0]);

    for (int i=1;i<=(sizeof(selectedBook->author)/sizeof(char*))-1;i++)
         {
             printf(", %s",selectedBook->author[i]);
         }
    printf("\n");

    printf("ISBN:              %s\n",selectedBook->isbn);
    printf("Verfügbare Bücher: %d\n",selectedBook->amount);
    printf("Ausleiher:         %s",selectedBook->borrowers[0]);

    for (int j=1;j<=sizeof(selectedBook->borrowers)/sizeof(char*)-1;j++)
         {
             printf(", %s",selectedBook->borrowers[j]);
         }
    printf("\n");
    BACK();
    MENU_FINISHLINE();
}


