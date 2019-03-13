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
#include "terminalUtils.h"
#include "fileUtils.h"

void printMainMenu(bool);

void printSearchMenu(void);

void printSearchMenuText(searchCol);

void printListMenu(bookData **);

void printSelectedBookData(bookData *);


#define TITLE() {\
printf("~~~~~~~~~~~~~~~~~~~~~\n");\
printf(" Bibliotheksprogramm\n");\
printf("~~~~~~~~~~~~~~~~~~~~~\n");\
}

#define BACK() {\
    printf(" 0 Zurück\n");\
}

#define MAINMENU() {\
    printf(" 0 Beenden\n");\
    printf(" 1 Buch suchen\n");\
    printf(" 2 Buch zurückgeben\n");\
    printf("~~~~~~~~~~~~~~~~~~~~~\n");\
    printf(" Verwaltung:\n");\
    printf(" -----------\n");\
}

#define MAINMENU_MANMODE() {\
    printf(" 3 Abmelden\n");\
    printf(" 4 Buch hinzufügen\n");\
}

#define MAINMENU_NOMANMODE() {\
    printf(" 3 Anmelden\n");\
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
    printf(" i | Titel                      | Author                       | ISBN          | Anz |\n");\
    printf("---+----------------------------+------------------------------+---------------+-----+\n");\
}

#define LIST_MENU() {\
    printf("Buch auswählen über den Index i.\n");\
    printf("Bitte passendes i eingeben.\n");\
}

#define SELECTEDBOOK_MENU() {\
    printf("1 Ausleihen\n");\
    printf("2 Zurück geben\n");\
}

#endif /* menus_h */
