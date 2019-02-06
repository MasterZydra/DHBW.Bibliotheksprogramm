//
//  searchUtils.c
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 28.01.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#include "searchUtils.h"

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
