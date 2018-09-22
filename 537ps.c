#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int opt;
	DIR* procDirectory = opendir("/proc");

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
}
