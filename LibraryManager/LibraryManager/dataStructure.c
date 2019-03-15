//
//  dataStructure.c
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 26.02.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#include "dataStructure.h"

/**
 Remove one book from the book array

 @param books Pointer to book array
 @param delete Pointer to book which will be removed
 */
void removeBook(bookData ***books, bookData *delete) {
    // Allocate memory for new bookData array
    bookData **newBooks = calloc(countBooks(*books), sizeof(bookData *));
    // Iterate books and save pointer to new array
    // Except for the book to delete
    int cnt = 0;
    for (int curPos = 0; (*books)[curPos] != NULL; curPos++) {
        if ((*books)[curPos] == delete)
            freeBookData(&(*books)[curPos]);
        else {
            newBooks[cnt] = (*books)[curPos];
            cnt++;
        }
    }
    // Free old memory area and return address
    free(*books);
    *books = newBooks;
}

/**
 Free storage that is reserved for all book data
 
 @param bds Pointer to array of book data
 */
void freeBookDatas(bookData ***bds) {
    for (int i = 0; (*bds)[i] != NULL; i++){
        freeBookData(&(*bds)[i]);
    }
    free(*bds);
}

/**
 Free storage that is reserved for one book
 
 @param bd Pointer to array of book data
 */
void freeBookData(bookData **bd) {
    freeSubBookData(&bd[0]->author);
    freeSubBookData(&bd[0]->borrowers);
    free(bd[0]->isbn);
    free(bd[0]->title);
    free(bd[0]);
}

/**
 Sort bookData array
 
 @param books Pointer to bookData array
 */
void sortBooks(bookData **books) {
    qsort(&(books[0]), countBooks(books), sizeof(bookData*), bookCompare);
}

/**
 Counts the number of books in the bookData array
 
 @param books Book array
 @return number of books
 */
int countBooks(bookData **books) {
    int cnt = 0;
    for (cnt = 0; books[cnt] != NULL; cnt++);
    return cnt;
}

/**
 Compare two books by sortOrder
 
 @param p1 Pointer to book
 @param p2 Pointer to book
 @return 1, -1 or 0
 */
int bookCompare(const void *p1, const void *p2) {
    if (((bookData *)p1)->sortOrder < ((bookData *)p2)->sortOrder) return 1;
    if (((bookData *)p1)->sortOrder > ((bookData *)p2)->sortOrder) return -1;
    return 0;
}

/**
 Saves content in struct into CSV
 
 @param books Pointer to BookData array
 @return Pointer to Memory with CSV string
 */
char *bookDataToCSV(bookData **books) {
    char* csv = malloc(sizeof(char) * 999);
    int cursorPos = 0;
    for (int curPos = 0; books[curPos] != NULL; curPos++) {
        // ISBN
        addStrAtPos(books[curPos]->isbn, csv, &cursorPos);
        addCharToPos('|', csv, &cursorPos);
        // Title
        addStrAtPos(books[curPos]->title, csv, &cursorPos);
        addCharToPos('|', csv, &cursorPos);
        // Author
        for (int i = 0; (books[curPos]->author)[i] != NULL; i++) {
            addStrAtPos((books[curPos]->author)[i], csv, &cursorPos);
            addCharToPos(';', csv, &cursorPos);
        }
        addCharToPos('|', csv, &cursorPos);
        // Amount - Convert int to char*
        char *amount = malloc(sizeof(char) * 5);
        sprintf(amount, "%d", books[curPos]->amount);
        addStrAtPos(amount, csv, &cursorPos);
        free(amount);
        addCharToPos('|', csv, &cursorPos);
        // Borrower
        for (int i = 0; (books[curPos]->borrowers)[i] != NULL; i++) {
            addStrAtPos((books[curPos]->borrowers)[i], csv, &cursorPos);
            addCharToPos(';', csv, &cursorPos);
        }
        // Linebreak
        addCharToPos('\n', csv, &cursorPos);
    }
    addCharToPos('\0', csv, &cursorPos);
    return csv;
}
