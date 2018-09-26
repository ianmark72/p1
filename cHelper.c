#include "cHelper.h"

void cHelper(char* pid, char* result) {
        //Create file object.
        FILE *file;
        //Start of the filepath.
        char[] filePath = "/proc/;
        char next[100];
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

        while(fscanf(file, "%s", next) != EOF) {
        	strncat(finalOutput, next, 100);
        }

	result = finalOutput;

        fclose(file);
}

