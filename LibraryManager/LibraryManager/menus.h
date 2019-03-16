//
//  menus.h
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 28.01.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#ifndef menus_h
#define menus_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "searchUtils.h"
#include "dataStructure.h"
#include "utils.h"
#include "fileUtils.h"

void printMainMenu(void);

void printSearchMenu(void);

void printSearchMenuText(searchCol);

void printListMenu(bookData **);

void printSelectedBookData(bookData *);

void printRemoveBook(void);

void printAddBook(void);

#define TITLE() {\
printf("~~~~~~~~~~~~~~~~~~~~~\n");\
printf(" Bibliotheksprogramm\n");\
printf("~~~~~~~~~~~~~~~~~~~~~\n");\
}

#define BACK() {\
    printf(" 0 Zur%cck\n", ue);\
}

#define MAINMENU() {\
    printf(" 0 Beenden\n");\
    printf(" 1 Buch suchen\n");\
    printf("~~~~~~~~~~~~~~~~~~~~~\n");\
    printf(" Verwaltung:\n");\
    printf(" -----------\n");\
    printf(" 2 Buch hinzuf%cgen\n", ue);\
    printf(" 3 Buch entfernen\n");\
}

#define SEARCHMENU() {\
    printf("\n");\
    printf(" Suche nach Kategorie:\n");\
    printf(" 1 Alle\n");\
    printf(" 2 ISBN\n");\
    printf(" 3 Titel\n");\
    printf(" 4 Autor\n");\
}

#define SEARCHMENU_TEXT(a) {\
    printf("\n");\
    printf(" Bitte %s eingeben: ", (a));\
}

#define MENU_FINISHLINE() {\
    printf("~~~~~~~~~~~~~~~~~~~~~\n");\
}

#define MENU_INPUT() {\
    printf("Auswahl: ");\
}

#define LIST_HEADLINE() {\
    printf(" i | Titel                      | Autor                        | ISBN          | Anz |\n");\
    printf("---+----------------------------+------------------------------+---------------+-----+\n");\
}

#define LIST_MENU() {\
    printf("Buch ausw%chlen %cber den Index i.\n", ae, ue);\
    printf("Bitte passendes i eingeben.\n");\
}

#define SELECTEDBOOK_MENU() {\
    printf(" 1 Ausleihen\n");\
    printf(" 2 Zur%cckgeben\n", ue);\
}

#define REMOVE_BOOK() {\
    printf("\n");\
    printf("Buch entfernen\n");\
    printf("--------------\n");\
}

#define ADD_BOOK() {\
    printf("\n");\
    printf("Buch hinzuf%cgen\n", ue);\
    printf("--------------\n");\
}

#endif /* menus_h */
