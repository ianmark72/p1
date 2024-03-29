/***********************************************************************
* FILENAME: cHelper.c
*
* DESCRIPTION:
*       This file contains the sHelper function.
*
* AUTHORS: Matthew Derzay, CS Login: derzay
*          Ian Mark, CS Login: imark
*
***********************************************************************/
#include "cHelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#define BUF_SIZE_BIG 1024
/**
 *  This function reteives the state of the process based on the pid 
 *  given. Then concatenates the information onto the result string.
 */

void cHelper(char* pid, char* result) {
        //Create file object.
        FILE *file;
        //Start of the filepath.
        char filePath[] = "/proc/";
	char finalOutput[BUF_SIZE_BIG];

        //Concatenate filepath with pid and status file to get full filepath.
        strncat(filePath, pid, BUF_SIZE_BIG);
        strncat(filePath, "/cmdline", BUF_SIZE_BIG);

        //Open file, r means read only.
        file = fopen(filePath, "r");
        //Check if the file is open.
        if(file == NULL) {
                printf("File cannot be opened\n");
                exit(0);
        }
	//clear finalOutput's memory
	strcpy(finalOutput, "");
	strncat(finalOutput, "[", BUF_SIZE_BIG);
	//go through cmdline char by char
	 do {
		char c;
		//if end of file break out of loop
                if(( c = fgetc(file) ) == EOF ) { break; }
		// if null character
                if ( c == '0' ) { /* add space to results */ 
			       strncat(finalOutput, " ", BUF_SIZE_BIG);
		}
		// otherwise add to finalOutput
		else { /* add char to results */
			char tmp[2];
		       	tmp[0]	= c;
			tmp[1] = '\0';
			strncat(finalOutput, tmp , BUF_SIZE_BIG);       
		}

} while(1);
strncat(finalOutput, "]", BUF_SIZE_BIG);

// add to the results string 
	strncat(result, finalOutput, BUF_SIZE_BIG);

        fclose(file);
}

