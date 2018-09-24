#include "sHelper.h"

char[] sHelper(char[] pid) {
	//Create file object.
	FILE *file;
	//Start of the filepath.
        char[] filePath = "/proc/;
	//Next string in the file.
	char nextStr[60];

	

	//Concatenate filepath with pid to get full filepath.	
	strncat(filePath, pid, 20);

	//Open file, r means read only.
	file = fopen(filePath, "r");
	//Check if the file is open.
	if(file == NULL) {
		printf("File cannot be opened\n");
		exit(0);
	}

	//Not sure how do search through file yet.
	//if(fgets(nextStr, 60, file) != NULL) {
		
	//}
	
}
