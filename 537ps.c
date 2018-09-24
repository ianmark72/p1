#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>



int main(int argc, char *argv[]) {
	int opt;
	int p = 0;
	int s = 0;
	int U = 1;
	int S = 0;
	int v = 0;
	int c = 1;

	while((opt = getopt(argc, argv, "p:s::U::S::v::c::")) != -1) {
		switch(opt) {
		case 'p':
			//if no -p print all
			//otherwise print specific pid
			//printf("p %s\n", optarg);
			p = 1;	
			break;
		case 's':
			//do not print if no argument
			//print if -s
			//-s- is valid but no effect
			//printf("s %c\n", *optarg);
			s = 1;
			break;
		case 'U':
			//print if no argument
			//do not print if -U-
			//does not state what to do for -U
			//printf("U %c\n", *optarg);
			if(*optarg == '-') {
				U = 0;
			}
			break;
		case 'S':
			//do not print if no argument
			//print if -S
			//-S- is valid but no effect
			//printf("S %c\n", *optarg);
			S = 1;
			break;
		case 'v':
			//do not print if no argument
			//print if -v
			//-v- is valid but no effect
			//printf("v %c\n", *optarg);
			v = 1;
			break;
		case 'c':
			//print if no argument
			//do not print if -c-
			//does not state what to do for -c
			//printf("c %c\n", *optarg);
			if(*optarg == '-') {
				c = 0;
			}
			break;
		default: 
			printf("You fucked up.\n");
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
