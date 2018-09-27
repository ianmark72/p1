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
#define BUF_SIZE 100

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
        char nextWord[BUF_SIZE];
	//Index of the next element in the file.
        int infoLine = 0;
	//First letter of a file output.
        char firstLetter;
        //Last letter of a file output.
        char lastLetter;

        //Concatenate filepath with pid and status file to get full filepath.
        strncat(filePath, pid, BUF_SIZE);
        strncat(filePath, "/statm", BUF_SIZE);

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
			strncat(result, nextWord, BUF_SIZE);
			strncat(result, " ", BUF_SIZE);
                        break;
		}

                //Set variable to chack if its a name with two words.
                firstLetter = nextWord[0];
                lastLetter = nextWord[strlen(nextWord) - 1];
                if(firstLetter == '(' && lastLetter != ')') {

                } else {
                        infoLine++;
                }
        }

        fclose(file);
}

