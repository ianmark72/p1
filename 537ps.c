#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int opt;

	while((opt = getopt(argc, argv, "p:s::U::S::v::c::")) != -1) {
		switch(opt) {
		case 'p':
			//if no -p print all
			//otherwise print specific pid
			printf("p %s\n", optarg);	
			break;
		case 's':
			//do not print if no argument
			//print if -s
			//-s- is valid but no effect
			printf("s %c\n", *optarg);
			break;
		case 'U':
			//print if no argument
			//do not print if -U-
			//does not state what to do for -U
			printf("U %c\n", *optarg);
			break;
		case 'S':
			//do not print if no argument
			//print if -S
			//-S- is valid but no effect
			printf("S %c\n", *optarg);
			break;
		case 'v':
			//do not print if no argument
			//print if -v
			//-v- is valid but no effect
			printf("v %c\n", *optarg);
			break;
		case 'c':
			//print if no argument
			//do not print if -c-
			//does not state what to do for -c
			printf("c %c\n", *optarg);
			break;
		default: 
			printf("You fucked up.\n");
			exit(EXIT_FAILURE);
		}
	}
}
