/***********************************************************************
* FILENAME: 537ps.c 
*
* DESCRIPTION:
* 	This is the main file of the program. It parses the user input
* 	and calls the neccessary helper methods. Once all the data
* 	is returned the program prints out the output.
* 
* AUTHORS: Matthew Derzay, CS Login: derzay
* 	   Ian Mark, CS Login: imark
*
***********************************************************************/
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
#define BUF_SIZE 100

/**
 *  This function checks if a string contains any non-numbers, returns 1
 *  if the string contains only numbers and 0 if it contains any letters.
 *
 *  Parameters: s - The string that is being checked.
 *
 *  Return: int - Boolean stating whether or not the string is a number.
 */
int isNumbers (const char *string){
	//Cycles through all character to see if any are letters.
        while(*string) {
		//If any are letters return false.
        	if(isdigit(*string++) == 0) { 
			return 0;
		}
        }
        return 1;
}

/**
 *  This function determines which process will be displayed then 
 *  passes these pids in the helper function and then prints the info
 *  once received.
 *
 *  Parameters: p - Boolean determining whether a specific process should
 *  		    be displayed or all.
 *  		s - Boolean determining whether or not the state of the
 *  		    process should be displayed.
 *  		U - Boolean determining whether or not the utime of 
 *  		    the process should be displayed.
 *              S - Boolean determining whether or not stime should be
 *                  displayed.
 *              v - Boolean determining whether or not the virtual
 *                  memory usage should be displayed.
 *              c - Boolean determining whether or not the command line
 *                  that called this process should be displayed.
 *              pid - PID of the process being displayed.
 *
 */
void getInfo (int p, int s, int U, int S, int v, int c, char* pid ){
	//Final line of information to be desiplayed.
	static char result[BUF_SIZE];
	
	//If a single or all processes should be displayed.
	if(p){
		//Add pid to output.
		strncat(result, pid, BUF_SIZE);
		strncat(result, ": ", BUF_SIZE);

		//Send to helper function if needed.
		if(s) { sHelper(pid, result); }
		if(U) { UHelper(pid, result); }
		if(S) { SHelper(pid, result); }
		if(v) { vHelper(pid, result); }
		if(c) { cHelper(pid, result); }

		//Print final output.
		printf("%s\n", result);
	} else {
		//Structure to store directory information.
		struct dirent *procFile;
		//Pointer to location of the proc directory.
        	DIR *proc;

		//First, open proc file.
                if ((proc = opendir("/proc")) != NULL){
			//Read through the entire proc directory.
                	while((procFile = readdir(proc))){
				//Filter out filenames that are not numbers.
                         	if(isNumbers((procFile -> d_name))) {
					//Add pid to output.
					strncat(result, procFile -> d_name, BUF_SIZE);
			                strncat(result, ": ", BUF_SIZE);
					
					//Call neccessary helper functions.
                                     	if(s) { sHelper((procFile -> d_name), result); }
                		      	if(U) { UHelper((procFile -> d_name), result); }
                		      	if(S) { SHelper((procFile -> d_name), result); }
                	  	      	if(v) { vHelper((procFile -> d_name), result); }
                		      	if(c) { cHelper((procFile -> d_name), result); }

					//Print output.
				      	printf("%s\n", result);
					//Clear output for the next line.
				      	memset(result, 0, sizeof(result));
                        	}
                	}
		} else {
			//Print error if unable to open directory.
                	printf("failure in opening proc\n");
                }
	}	
}
/**
 *  The main function where the arguments are parsed and the booleans of what
 *  information should be displayed. These boolean are then passed on to the 
 *  getInfo() method.
 *
 */
int main(int argc, char *argv[]) {
	//Argument being parsed.
	int opt;
	//One specific process or all process boolean.
	int p = 0;
	//Boolean for process state.
	int s = 0;
	//Boolean for utime.
	int U = 1;
	//Boolean for stime.
	int S = 0;
	//Boolean for visual memory usage.
	int v = 0;
	//Boolean for command line call.
	int c = 1;
	//Process' ID.
	char pid[BUF_SIZE];
	
	//Parse through the arguments
	while((opt = getopt(argc, argv, "p:s::U::S::v::c::")) != -1) {
		//Switch statement for the different argument cases.
		switch(opt) {
		case 'p':
			//Set to true if argument exists.
			p = 1;
			strcpy(pid, optarg);
			break;
		case 's':
			//Set to true if argument exists.
			s = 1;
			//Turn off if -s-.
			if(optarg != NULL){
				if(*optarg == '-') {
                                	s = 0;
                        	}
			}
			break;
		case 'U':
			//In case of -U.
			U = 1;
			//Turn off if -U-.
			if(optarg != NULL) {
				if(*optarg == '-') {
					U = 0;
				}
			}
			break;
		case 'S':
			//Set toe true if argument exists.
			S = 1;
			//Turn off if -S-.
			if(optarg != NULL) {
				if(*optarg == '-') {
                                	S = 0;
                        	}
			}
			break;
		case 'v':
			//Set to true if argument exists.
			v = 1;
			//Turn off if -v-.
			if(optarg != NULL) {
				if(*optarg == '-') {
                                	v = 0;
                        	}
			}
			break;
		case 'c':
			//In case of -c.
			c = 1;
			//Turn off if -c-.
			if(optarg != NULL) {
				if(*optarg == '-') {
					c = 0;
				}
			}
			break;
		default: 
			//Error if any invalid arguments
			printf("Invalid Arguments.\n");
			exit(EXIT_FAILURE);
		}

		//if(optind < argc) {
		//	printf("Invalid Arguments.\n");
		//	exit(EXIT_FAILURE);
		//}
	}

	//Send booleans to getInfo().
	getInfo( p, s, U, S, v, c, pid);
}
