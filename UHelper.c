/***********************************************************************
* FILENAME: UHelper.c
*
* DESCRIPTION:
*       This file contains the UHelper function.
*
* AUTHORS: Matthew Derzay, CS Login: derzay
*          Ian Mark, CS Login: imark
*
***********************************************************************/

#include "UHelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 *  This function reteives the utime of the process based on the pid
 *  given. Then concatenates the information onto the result string.
 */
void UHelper(char* pid, char* result) {
        //Create file object.
        FILE *file;
        //Start of the filepath.
        char filePath[] = "/proc/";
	//The next word in the file.
        char nextWord[200];
	//Index of the element in the file;
        int infoLine = 0;

        //Concatenate filepath with pid and status file to get full filepath.
        strncat(filePath, pid, 20);
        strncat(filePath, "/stat", 30);

        //Open file, r means read only.
        file = fopen(filePath, "r");
        //Check if the file is open.
        if(file == NULL) {
                printf("File cannot be opened\n");
                exit(0);
        }

	//Read through the file until desired information.
        while(fscanf(file, "%s", nextWord) != EOF) {
                if(infoLine == 13) {
			//Concatenate information onto the result;
			strncat(result, nextWord, 100);
			strncat(result, " ", 100);
                        break;
                }

                infoLine++;
        }

        fclose(file);
}

