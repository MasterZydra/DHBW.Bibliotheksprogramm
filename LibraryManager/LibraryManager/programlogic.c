//
//  programlogic.c
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 28.01.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#include "programlogic.h"

/**
 Logic and output for main menu
 */
void mainMenu(bookData ***books) {
    char input = ' ';

    while (true) {
        printMainMenu();

        terminalInput("%c", &input);

        switch (input) {
            case '0': return;
            case '1':
                // Search book
                searchMenu(books);
                break;
            case '2':
                // Add a book to list
                menuAddBook(books);
                break;
            case '3':
                // Remove a book from list
                menuRemoveBook(books);
            default:
                break;
        }
    }
    return;
}

/**
 Menu for searching books

 @param books Pointer to book array
 */
void searchMenu(bookData ***books) {
    char input = ' ';
    while (true) {
        printSearchMenu();

        terminalInput("%c", &input);

        switch (input) {
            case '0': return;
            case '1':
                // Search in all
                if (searchMenuText(books, scAll) == 0)
                    return;
                break;
            case '2':
                // Search in ISBN
                if (searchMenuText(books, scISBN) == 0)
                    return;
                break;
            case '3':
                // Search in Title
                if (searchMenuText(books, scTitle) == 0)
                    return;
                break;
            case '4':
                // Search in Author
                if (searchMenuText(books, scAuthor) == 0)
                    return;
                break;

            default:
                break;
        }
    }
}

/**
 Menu for input of search text

 @param sc Columns in which will be searched in
 @return 0 = Ok, 1 = Break
 */
int searchMenuText(bookData ***books, searchCol sc) {
    char *input = (char *)calloc(100, sizeof(char));

    printSearchMenuText(sc);

    input = getLine();
    //terminalInput("%s", input);

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
        if (input >= '1' && input <= '9') {
            int pos = input - '1';
            // Continue loop if input is greater then amount of books
            if ((pos + 1) > countBooks(listData)) continue;
            selectedBookMenu(listData[pos]);
        }
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

/**
 Menu to add a new book to the list

 @param books Pointer to book array
 */
void menuAddBook(bookData ***books) {
    char input[200];
    char *inputLine = NULL;
    // Get ISBN
    printf("\n");
    printf("Bitte ISBN eingeben: (Abbruch mit '0')\n");
    terminalInput("%s", &input);
    // User abort
    if (strcmp(input, "0") == 0) {
        return;
    }
    // Check if user book is already in list
    bookData *book = NULL;
    bookData **results = searchBooks(scISBN, *books, input);
    // Search perfect match
    for (int i=0; results[i] != NULL; i++)
        if (results[i]->sortOrder == INT_MIN)
            book = results[i];
    // If match, add one copy
    if (book != NULL) {
        book->amount = book->amount + 1;
        return;
    }
    // Else add a new book
    addBook(books);
    book = (*books)[countBooks(*books) - 1];
    // Fill book data with details
    book->amount = 1;
    book->sortOrder = 0;
    // Save isbn
    book->isbn = allocMem(input, (int)strlen(input) + 1);
    // Save title
    while (inputLine == NULL || strcmp(inputLine, "") == 0) {
        printf("\n");
        printf("Bitte Titel eingeben:\n");
        inputLine = getLine();
        book->title = allocMem(inputLine, (int)strlen(inputLine) + 1);
    }
    free(inputLine);
    inputLine = NULL;
    // Save authors
    while (inputLine == NULL || strcmp(inputLine, "") == 0) {
        printf("\n");
        printf("Bitte Autoren eingeben: (Mehrere durch ';' abtrennen\n");
        inputLine = getLine();
    }
    getSubList(&book->author, inputLine);
    free(inputLine);
    inputLine = NULL;
    // Add empty list of borrowers
    getSubList(&book->borrowers, "");
}

/**
 Menu to remove

 @param books Pointer to book array
 */
void menuRemoveBook(bookData ***books) {
    char input[200];
    // Get ISBN
    printf("\n");
    printf("Bitte ISBN eingeben: (Abbruch mit '0')\n");
    terminalInput("%s", &input);
    // User abort
    if (strcmp(input, "0") == 0) {
        return;
    }
    // Check if user book is already in list
    bookData *book = NULL;
    bookData **results = searchBooks(scISBN, *books, input);
    // Search perfect match
    for (int i=0; results[i] != NULL; i++)
        if (results[i]->sortOrder == INT_MIN)
            book = results[i];
    // If match, add one copy
    if (book == NULL) {
        printf("\n");
        printf("(i) Info:\n");
        printf("---------\n");
        printf("Kein Buch mit ISBN '%s' gefunden.\n\n", input);
        printf("Mit Enter fortfahren");
        getchar();
        return;
    }

    if (book->amount == countStrings(book->borrowers)) {
        printf("\n");
        printf("(i) Info:\n");
        printf("---------\n");
        printf("Buch kann nicht entfernt werden, da alle B%ccher verliehen sind.\n\n",ue);
        printf("Mit Enter fortfahren");
        getchar();
        return;
    }

    if (book->amount > 1) {
        book->amount = book->amount - 1;
    }
    else {
        removeBook(books, book);
    }
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
    char *name = NULL;
    printf("Bitte Name des Ausleihers eingeben: (Abbruch mit '0')\n");
    name = getLine();

    //terminalInput("%s", &name);
    if (strcmp(name, "0") == 0) return;
    addSubstring(&selectedBook->borrowers, name);
}

/**
 Return a book

 @param selectedBook Book to return
 */
void returnBook(bookData *selectedBook) {
    char *name = NULL;//[100];
    printf("\n");
    printf("Bitte Name des Ausleihers eingeben: (Abbruch mit '0')\n");
    name = getLine();
    //terminalInput("%s", &name);
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
