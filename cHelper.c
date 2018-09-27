#include "cHelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

void cHelper(char* pid, char* result) {
        //Create file object.
        FILE *file;
        //Start of the filepath.
        char filePath[] = "/proc/";
        //char nextWord[100];
	char finalOutput[200];

        //Concatenate filepath with pid and status file to get full filepath.
        strncat(filePath, pid, 20);
        strncat(filePath, "/cmdline", 30);

        //Open file, r means read only.
        file = fopen(filePath, "r");
        //Check if the file is open.
        if(file == NULL) {
                printf("File cannot be opened\n");
                exit(0);
        }
	strncat(finalOutput, "[", 200);
	 do {
		 char c;
                if(( c = fgetc(file) ) == EOF ) { break; }
                if ( c == '0' ) { /* add space to results */ 
			       strncat(finalOutput, " ", 200);
		}
		else { /* add char to results */
			char tmp[2];
		       	tmp[0]	= c;
			tmp[1] = '\0';
			strncat(finalOutput, tmp , 200);       
		}

} while(1);
strncat(finalOutput, "]", 200);
       // while(fscanf(file, "%s", nextWord) != EOF) {
	//	strncat(finalOutput, "[", 200);
        //	strncat(finalOutput, nextWord, 200);
	//	strncat(finalOutput, "]", 200);
        //}

	strncat(result, finalOutput, 200);

        fclose(file);
}

