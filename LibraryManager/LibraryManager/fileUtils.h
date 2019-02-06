//
//  fileUtils.h
//  LibraryManager
//
//  Created by David Hein on 28.01.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#ifndef fileUtils_h
#define fileUtils_h

#include <stdio.h>
#include <string.h>

void getFileContent(char *fileName, void (*readNewLineEvent) (const char *));

#endif /* fileUtils_h */
