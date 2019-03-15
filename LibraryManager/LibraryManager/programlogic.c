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
void mainMenu(bookData ***books) {
    char input = ' ';
    bool manageMode = true;

    while (true) {
        printMainMenu(manageMode);

        terminalInput("%c", &input);

        switch (input) {
            case '0': return;
            case '1':
                // Search book
                searchMenu(books, manageMode);
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
void searchMenu(bookData ***books, bool manageMode) {
    char input = ' ';
    while (true) {
        printSearchMenu();

        terminalInput("%c", &input);

        switch (input) {
            case '0': return;
            case '1':
                // Search in all
                if (searchMenuText(books, manageMode, scAll) == 0)
                    return;
                break;
            case '2':
                // Search in ISBN
                if (searchMenuText(books, manageMode, scISBN) == 0)
                    return;
                break;
            case '3':
                // Search in Title
                if (searchMenuText(books, manageMode, scTitle) == 0)
                    return;
                break;
            case '4':
                // Search in Author
                if (searchMenuText(books, manageMode, scAuthor) == 0)
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
int searchMenuText(bookData ***books, bool manageMode, searchCol sc) {
    char *input = (char *)calloc(100, sizeof(char));
    
    printSearchMenuText(sc);
    terminalInput("%s", input);

    if (strcmp(input, "0") == 0) {
        free(input);
        return 1;
    }
    // Search matches
    bookData **results = searchBooks(sc, *books, input);
    free(input);
    // Sort books by sortOrder
    sortBooks(results);
    // Execute list menu which shows results
    listMenu(results);
    free(results);
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
            case '1':
                // Borrow book
                borrowBook(selectedBook);
                break;
            case '2':
                // Return book
                returnBook(selectedBook);
                break;
            default:
                break;
        }
    }
    return 0;
}

void addBook(bookData ***books) {
    // Increase size of book array
    int cnt = countBooks(*books);
    *books = (bookData **)reallocMemCalloc(*books, cnt + 2, sizeof(bookData*), cnt);
    // Allocate space for one book
    (*books)[cnt] = malloc(sizeof(bookData));
    
    (*books)[cnt]->isbn = allocMem("12345678", strlen("12345678") + 1);
    (*books)[cnt]->title = allocMem("test book", strlen("test book") + 1);
    (*books)[cnt]->sortOrder = -1;
    (*books)[cnt]->amount = 99;
    char *author = allocMem("TestAuthor;", strlen("TestAuthor;") + 1);
    char *borrower = allocMem("", strlen("") + 1);
    getSubList(&(*books)[cnt]->author, author);
    free(author);
    getSubList(&(*books)[cnt]->borrowers, borrower);
    free(borrower);
}

/**
 Borrow a book
 
 @param selectedBook Book to borrow
 */
void borrowBook(bookData *selectedBook) {
    printf("\n");
    // Check if all books are lent
    if (selectedBook->amount == countStrings(selectedBook->borrowers)) {
        printf("(i) Info:\n");
        printf("---------\n");
        printf(" Alle %d Exemplare sind ausgeliehen.\n\n", selectedBook->amount);
        printf("Mit Enter fortfahren");
        getchar();
        return;
    }
    // Get name and add to bookData
    char name[100];
    printf("Bitte Name des Ausleihers eingeben: (Abbruch mit '0')\n");
    terminalInput("%s", &name);
    if (strcmp(name, "0") == 0) return;
    addSubstring(&selectedBook->borrowers, name);
}

/**
 Return a book

 @param selectedBook Book to return
 */
void returnBook(bookData *selectedBook) {
    char name[100];
    printf("\n");
    printf("Bitte Name des Ausleihers eingeben: (Abbruch mit '0')\n");
    terminalInput("%s", &name);
    if (strcmp(name, "0") == 0) return;
    
    char *borrower = findSubstring(selectedBook->borrowers, name);
    if (borrower != NULL) {
        removeSubstring(&selectedBook->borrowers, borrower);
    }
    else {
        printf("\n");
        printf("(i) Info:\n");
        printf("---------\n");
        printf("Kein Ausleiher '%s' gefunden.\n\n", name);
        printf("Mit Enter fortfahren");
        getchar();
    }
}
