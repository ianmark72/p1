#include "cHelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void cHelper(char* pid, char* result) {
        //Create file object.
        FILE *file;
        //Start of the filepath.
        char filePath[] = "/proc/";
        char nextWord[100];
	char finalOutput[100];

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

        while(fscanf(file, "%s", nextWord) != EOF) {
        	strncat(finalOutput, nextWord, 100);
        }

	strncat(result, finalOutput, 100);

        fclose(file);
}

