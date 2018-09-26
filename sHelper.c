#include "sHelper.h"

char[] sHelper(char[] pid) {
	//Create file object.
	FILE *file;
	//Start of the filepath.
        char[] filePath = "/proc/;
	char next[100];
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

   	while(fscanf(file, "%s", next) != EOF) {
        	if(infoLine == 2) {
                	break;
        	}

        	infoLine++;
	}

   	fclose(file);

	return next;
}
