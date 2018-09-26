#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include "sHelper.h"
#include "UHelper.h"
#include "SHelper.h"
#include "vHelper.h"
#include "cHelper.h"

// This function checks if a string contains any non-numbers, returns 1 if the string contains only numbers and 0 if it contains any letters
int isNumbers (const char *s){
        while(*s) {
        	if(isdigit(*s++) == 0) { 
			return 0;
		}
        }
        return 1;
}

void getInfo (int p, int s, int U, int S, int v, int c, char* pid ){
	static char result[1000];

	if(p){
		if(s) { sHelper(pid, result); }
		if(U) { UHelper(pid, result); }
		if(S) { SHelper(pid, result); }
		if(v) { vHelper(pid, result); }
		if(c) { cHelper(pid, result); }
	} else {
		struct dirent *procFile;
        	DIR *proc;
		//first, open proc file
                if ((proc = opendir("/proc")) != NULL){
                	while((procFile = readdir(proc))){
				//filter out filenames that are not numbers
                         	if(isNumbers((procFile -> d_name))) {
                                      if(s) { sHelper((procFile -> d_name), result); }
                		      if(U) { UHelper((procFile -> d_name), result); }
                		      if(S) { SHelper((procFile -> d_name), result); }
                	  	      if(v) { vHelper((procFile -> d_name), result); }
                		      if(c) { cHelper((procFile -> d_name), result); }
                        	}
                	}
		} else {
                	printf("failure in opening proc\n");
                }
	}	
}

int main(int argc, char *argv[]) {
	int opt;
	int p = 0;
	int s = 0;
	int U = 1;
	int S = 0;
	int v = 0;
	int c = 1;
	char pid[] = "-1";
	while((opt = getopt(argc, argv, "p:s::U::S::v::c::")) != -1) {
		switch(opt) {
		case 'p':
			//if no -p print all
			//otherwise print specific pid
			//printf("p %s\n", optarg);
			p = 1;
			strcpy(pid, optarg);
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

	getInfo( p, s, U, S, v, c, pid);
}
