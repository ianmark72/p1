#include "cHelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#define BUF_SIZE_BIG 1024
#define BUF_SIZE_SMALL 256

void cHelper(char* pid, char* result) {
        //Create file object.
        FILE *file;
        //Start of the filepath.
        char filePath[] = "/proc/";
	char finalOutput[BUF_SIZE_BIG];

        //Concatenate filepath with pid and status file to get full filepath.
        strncat(filePath, pid, BUF_SIZE_SMALL);
        strncat(filePath, "/cmdline", BUF_SIZE_SMALL);

        //Open file, r means read only.
        file = fopen(filePath, "r");
        //Check if the file is open.
        if(file == NULL) {
                printf("File cannot be opened\n");
                exit(0);
        }
	strncat(finalOutput, "[", BUF_SIZE_BIG);
	 do {
		 char c;
                if(( c = fgetc(file) ) == EOF ) { break; }
                if ( c == '0' ) { /* add space to results */ 
			       strncat(finalOutput, " ", BUF_SIZE_BIG);
		}
		else { /* add char to results */
			char tmp[2];
		       	tmp[0]	= c;
			tmp[1] = '\0';
			strncat(finalOutput, tmp , BUF_SIZE_BIG);       
		}

} while(1);
strncat(finalOutput, "]", BUF_SIZE_BIG);
       // while(fscanf(file, "%s", nextWord) != EOF) {
	//	strncat(finalOutput, "[", 200);
        //	strncat(finalOutput, nextWord, 200);
	//	strncat(finalOutput, "]", 200);
        //}

	strncat(result, finalOutput, 200);

        fclose(file);
}

