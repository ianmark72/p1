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
	printf("Entered getInfo\n");
	static char result[100];
	printf("Variables initialized\n");
	
	if(p){
		strncat(result, pid, 100);
		strncat(result, ": ", 100);
		if(s) { sHelper(pid, result); }
		printf("After s helper\n");
		if(U) { UHelper(pid, result); }
		printf("After U helper\n");
		if(S) { SHelper(pid, result); }
		if(v) { vHelper(pid, result); }
		if(c) { cHelper(pid, result); }
		printf("After c helper\n");
		printf("%s\n", result);
	} else {
		printf("This should not print\n");
		struct dirent *procFile;
        	DIR *proc;
		//first, open proc file
                if ((proc = opendir("/proc")) != NULL){
                	while((procFile = readdir(proc))){
				//filter out filenames that are not numbers
                         	if(isNumbers((procFile -> d_name))) {
					strncat(result, procFile -> d_name, 100);
			                strncat(result, ": ", 100);

                                      if(s) { sHelper((procFile -> d_name), result); }
                		      if(U) { UHelper((procFile -> d_name), result); }
                		      if(S) { SHelper((procFile -> d_name), result); }
                	  	      if(v) { vHelper((procFile -> d_name), result); }
                		      if(c) { cHelper((procFile -> d_name), result); }
				      printf("%s\n", result);
				      memset(result, 0, sizeof(result));
                        	}
                	}
		} else {
                	printf("failure in opening proc\n");
                }
	}	
}

int main(int argc, char *argv[]) {
	printf("Program starts\n");
	int opt;
	int p = 0;
	int s = 0;
	int U = 1;
	int S = 0;
	int v = 0;
	int c = 1;
	char pid[100];
	printf("Variables initialized\n");

	while((opt = getopt(argc, argv, "p:s::U::S::v::c::")) != -1) {
		switch(opt) {
		case 'p':
			printf("Entered p case\n");

			//if no -p print all
			//otherwise print specific pid
			//printf("p %s\n", optarg);
			p = 1;
			strcpy(pid, optarg);
			break;
		case 's':
			printf("Entered s case\n");

			//do not print if no argument
			//print if -s
			//-s- is valid but no effect
			//printf("s %c\n", *optarg);
			s = 1;
			break;
		case 'U':
			printf("Entered U case\n");

			//print if no argument
			//do not print if -U-
			//does not state what to do for -U
			//printf("U %c\n", *optarg);
			if(*optarg == '-') {
				printf("Turned U off\n");
				U = 0;
			}
			break;
		case 'S':
			printf("Entered S case\n");

			//do not print if no argument
			//print if -S
			//-S- is valid but no effect
			//printf("S %c\n", *optarg);
			S = 1;
			break;
		case 'v':
			printf("Entered v case\n");

			//do not print if no argument
			//print if -v
			//-v- is valid but no effect
			//printf("v %c\n", *optarg);
			v = 1;
			break;
		case 'c':
			printf("Entered c case\n");

			//print if no argument
			//do not print if -c-
			//does not state what to do for -c
			//printf("c %c\n", *optarg);
			if(*optarg == '-') {
				printf("Turned c off\n");
				c = 0;
			}
			break;
		default: 
			printf("Invalid Arguments.\n");
			exit(EXIT_FAILURE);
		}
	}
	printf("Before getInfo call\n");

	getInfo( p, s, U, S, v, c, pid);
}
