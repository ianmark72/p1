/***********************************************************************
* FILENAME: vHelper.c
*
* DESCRIPTION:
*       This file contains the vHelper function.
*
* AUTHORS: Matthew Derzay, CS Login: derzay
*          Ian Mark, CS Login: imark
*
***********************************************************************/

#include "vHelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 *  This function reteives the virtual memory usage of the process
 *  based on the pid given. Then concatenates the information onto
 *  the result string.
 */
void vHelper(char* pid, char* result) {
        //Create file object.
        FILE *file;
        //Start of the filepath.
        char filePath[] = "/proc/";
	//The next word in the file.
        char nextWord[100];
	//Index of the next element in the file.
        int infoLine = 0;

        //Concatenate filepath with pid and status file to get full filepath.
        strncat(filePath, pid, 20);
        strncat(filePath, "/statm", 30);

        //Open file, r means read only.
        file = fopen(filePath, "r");
        //Check if the file is open.
        if(file == NULL) {
                printf("File cannot be opened\n");
                exit(0);
        }

	//Read through the file.
        while(fscanf(file, "%s", nextWord) != EOF) {
                if(infoLine == 0) {
			//Concatenate the info onto the results string.
			strncat(result, nextWord, 100);
			strncat(result, " ", 100);
                        break;
		}

                infoLine++;
        }

        fclose(file);
}

