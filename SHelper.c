#include "SHelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void SHelper(char* pid, char* result) {
        //Create file object.
        FILE *file;
        //Start of the filepath.
        char filePath[] = "/proc/";
        char nextWord[100];
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

        while(fscanf(file, "%s", nextWord) != EOF) {
                if(infoLine == 13) {
			strncat(result, nextWord, 100);
			strncat(result, " ", 100);
                        break;
                }

                infoLine++;
        }

        fclose(file);
}

