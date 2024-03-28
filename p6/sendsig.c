////////////////////////////////////////////////////////////////////////////////
// Main File:        sendsig.c
// This File:        sendsig.c
// Other Files:      mySigHandler.c, division.c
// Semester:         CS 354 Lecture 003 Spring 2022
// Instructor:       deppeler
// 
// Author:           Riteshwar Singh Brar
// Email:            rbrar@wisc.edu
// CS Login:         riteshwar
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                         other than Instructors and TAs.
//                   Do credit and acknowledge peer mentors, 
//                         tutors, friends, family, etc.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of 
//                   of any information you find.
//////////////////////////// 80 columns wide ///////////////////////////////////


#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * This is the main function and is used to send signals to mySigHandler.
 * It takes arguements from the user and sends the appropriate signal
 *
 */
int main(int argc, char* argv[]){
	
	int signum = 0; //stores the number of the signal
	char* s = argv[1]; //storing the type of signal	
	
	if(argc != 3){
		printf("Usage: sendsig <signal type> <pid>\n");
		exit(0);
	}
	
	if( strcmp(s, "-u") == 0) {
		signum = SIGUSR1;
	}	
	
	else if( strcmp(s, "-i") == 0){    
		signum = SIGINT;
        }
	
	int pid = atoi(argv[2]);

	int ret_val = kill(pid, signum);//sending the signals to mySigHandler
	
	if(ret_val != 0 ){ //checks if kill() call was successful
		printf("kill function call was not successful");
	}
}

