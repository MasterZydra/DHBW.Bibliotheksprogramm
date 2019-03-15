//
//  searchUtils.c
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 28.01.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#include "searchUtils.h"

/**
 Find a string in a string array

 @param stringArr String array
 @param search Searchtext
 @return Pointer to string or NULL
 */
char *findSubstring(char **stringArr, char *search) {
    char *result = NULL;
    for (int curPos = 0; stringArr[curPos] != NULL; curPos++)
        if (strcmp(stringArr[curPos], search) == 0)
            return stringArr[curPos];
    return result;
}

int determineSearchMatch(char *data, char *searchText) {
    // Return INT_MIN if text is identical
    if (strcmp(data, searchText) == 0) return INT_MIN;
    // Return a negative number if searchtext is in data string
    // Else return a positiv number
    int lDst = (double)levenshtein(data, searchText)/strlen(data)*100;
    if (strstr(data, searchText)) return INT_MIN + lDst;
    else return lDst;
}

bookData **searchBooks(searchCol sc, bookData **allBooks, char *searchText) {
    bookData **result = calloc(1, sizeof(bookData**));
    int resCnt = 0;
    int searchMatch;
    
    
    for (int curPos = 0; allBooks[curPos] != NULL; curPos++) {
        allBooks[curPos]->sortOrder = INT_MAX;
        printf("Val: %i\n", allBooks[curPos]->sortOrder);
        printf("new book\n");
        switch (sc) {
            case scAll:
                searchMatch = determineSearchMatch(allBooks[curPos]->isbn, searchText);
                if (searchMatch < allBooks[curPos]->sortOrder) allBooks[curPos]->sortOrder = searchMatch;
                if (allBooks[curPos]->sortOrder == INT_MIN) break;
                searchMatch = determineSearchMatch(allBooks[curPos]->title, searchText);
                if (searchMatch < allBooks[curPos]->sortOrder) allBooks[curPos]->sortOrder = searchMatch;
                if (allBooks[curPos]->sortOrder == INT_MIN) break;
                for(int i = 0; (allBooks[curPos]->author)[i] != NULL; i++) {
                    searchMatch = determineSearchMatch((allBooks[curPos]->author)[i], searchText);
                    if (searchMatch < allBooks[curPos]->sortOrder)
                        allBooks[curPos]->sortOrder =  searchMatch;
                    if (allBooks[curPos]->sortOrder == INT_MIN) break;
                }
                break;
            case scISBN:
                allBooks[curPos]->sortOrder = determineSearchMatch(allBooks[curPos]->isbn, searchText);
                break;
            case scTitle:
                allBooks[curPos]->sortOrder = determineSearchMatch(allBooks[curPos]->title, searchText);
                break;
            case scAuthor:
                for(int i = 0; (allBooks[curPos]->author)[i] != NULL; i++) {
                    searchMatch = determineSearchMatch((allBooks[curPos]->author)[i], searchText);
                    if (searchMatch < allBooks[curPos]->sortOrder)
                        allBooks[curPos]->sortOrder =  searchMatch;
                    if (allBooks[curPos]->sortOrder == INT_MIN) break;
                }
                break;
            default:
                perror("Search criteria is not implemented!");
                break;
        }
        // Only add results with certain match
        if (allBooks[curPos]->sortOrder < 81) {
            result[resCnt] = allBooks[curPos];
            resCnt++;
            result = reallocMemCalloc(result, resCnt + 1, sizeof(bookData *), resCnt);
        }
        else {
            printf("No match: %s\n", allBooks[curPos]->title);
        }
    }
    return result;
}


/**
 Process the Levenshtein distance. It is a string metric for measuring
 the difference between two sequences.
 
 This phonetic algorithm returns the number of changes necessary to
 transform one string into the other.

 @param s1 first sequence
 @param s2 second sequence
 @return differences between the given sequences
 */
int levenshtein(const char *s1, const char *s2) {
    unsigned int x, y;
    // Get lenght of strings for size of matrix
    unsigned int lenS1 = (unsigned) strlen(s1);
    unsigned int lenS2 = (unsigned) strlen(s2);
    // Matrix counts the necessary operations
    unsigned int matrix[lenS2 + 1][lenS1 + 1];
    // Init first cell
    matrix[0][0] = 0;
    // Fill first col from 0 to n
    for (x = 1; x <= lenS2; x++)
        matrix[x][0] = matrix[x-1][0] + 1;
    // Fill first row from 0 to n
    for (y = 1; y <= lenS1; y++)
        matrix[0][y] = matrix[0][y-1] + 1;
    // Go throw all cells and get the minimal operations necessary
    for (x = 1; x <= lenS2; x++)
        for (y = 1; y <= lenS1; y++)
            matrix[x][y] = MIN3(// Insert operation (cell above)
                                matrix[x-1][y] + 1,
                                // Delete operation (cell to the left)
                                matrix[x][y-1] + 1,
                                // Substitution operation (diagonal left above)
                                matrix[x-1][y-1] + (s1[y-1] == s2[x-1] ? 0 : 1));
    // Return the minimal changes
    return(matrix[lenS2][lenS1]);
}
