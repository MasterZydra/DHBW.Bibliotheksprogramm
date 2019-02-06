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

void printMainMenu(bool);

#define TITLE() {\
printf("~~~~~~~~~~~~~~~~~~~~~\n");\
printf(" Bibliotheksprogramm\n");\
printf("~~~~~~~~~~~~~~~~~~~~~\n");\
}

#define MAINMENU() {\
    printf(" 0 Beenden\n");\
    printf(" 1 Buch suchen\n");\
    printf(" 2 Buch ausleihen\n");\
    printf(" 3 Buch zurückgeben\n");\
    printf("~~~~~~~~~~~~~~~~~~~~~\n");\
    printf(" Verwaltung:\n");\
    printf(" -----------\n");\
}

#define MAINMENU_MANMODE() {\
    printf(" 4 Abmelden\n");\
    printf(" 5 Buch hinzufügen\n");\
    printf(" 6 Buch entfernen\n");\
}

#define MAINMENU_NOMANMODE() {\
    printf(" 4 Anmelden\n");\
}

#define MENU_FINISHLINE() {\
    printf("~~~~~~~~~~~~~~~~~~~~~\n");\
}

#endif /* menus_h */
