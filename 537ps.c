#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>



int main(int argc, char *argv[]) {
	int opt;

	while((opt = getopt(argc, argv, "psUSvc:")) != -1) {
		switch(opt) {
		case 'p':
			printf("p");
			break;
		case 's':
			printf("s");
			break;
		case 'U':
			printf("U");
			break;
		case 'S':
			printf("S");
			break;
		case 'v':
			printf("v");
			break;
		case 'c':
			printf("c");
			break;
		default: 
			printf("You fucked up.");
			exit(EXIT_FAILURE);
		}
	}
	struct dirent *myFile;
	DIR *proc;
	if ((proc = opendir("/proc")) != NULL){
		printf("success in opening proc\n");
		while((myFile = readdir(proc)))
			printf("%s\n", myFile->d_name);
	}
	else {
		printf("failure in opening proc\n");
	}
	
}
