////////////////////////////////////////////////////////////////////////////////
// Main File:        mySigHandler.c
// This File:        mySigHandler.c
// Other Files:      sendsig.c, division.c
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



#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int alrmt = 3;//number of seconds passes in the alarm function for arming the alarm
int suctr = 0;//counter suctr counts the number of time SIGUSR1 is handled successfully

/* The following is a Signal Handler for SIGALRM. It print a message along with time when
 * an alrm goes off
 * 
 * The call to sigaction() in main should be successful in order for this handler to be assigned
 * and function properly
 */
void handler_SIGALRM() {
	
	int pid = getpid();//storing the process ID
	printf("PID: %d ",pid );
	
	time_t curtime;
	
	if( time(&curtime) == -1) {
		printf("ERROR: Unsucessful attempt to get time");
		exit(0);
	}

	if( ctime(&curtime) == NULL) {
		printf("ERROR: Unsucessful attempt to get current time");
                exit(0);
	}

	printf("CURRENT TIME: %s", ctime(&curtime));
	
	alarm(alrmt);

}


/* The following is a Signal Handler for SIGUSR1. It prints a message each time a SIGUSR1 signal is handled
 *
 * The call to sigaction() in main should be successful in order for this handler to be assigned
 * and function properly
 */

void handler_SIGUSR1() {
	
	suctr+=1;

        printf("SIGUSR1 handled and counted!\n");


}


/* The following is a Signal Handler for SIGINT. It prints a message with the number of times a SIGUSR1 signal was 
 * handled and then exits.
 *
 * The call to sigaction() in main should be successful in order for this handler to be assigned
 * and function properly
 */

void handler_SIGINT() {

        printf("\nSIGINT handled.\nSIGUSR1 was handled %d times. Exiting now.\n", suctr);
	
	exit(0);
}


/* 
 * This is the main funtion where each signal handler is assigned.
 *
 */
int main(){
	
	alarm(alrmt);

	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	
	sa.sa_handler = handler_SIGALRM;

	if(sigaction(SIGALRM, &sa, NULL) != 0){// checking is signal handler is assigned successfully
		printf("Error binding SIGALRM handler\n");
		exit(1);
	}

	struct sigaction su;
        memset(&su, 0, sizeof(su));

        su.sa_handler = handler_SIGUSR1;

        if(sigaction(SIGUSR1, &su, NULL) != 0){
                printf("Error binding SIGUSR1 handler\n");
                exit(1);
        }

	struct sigaction si;
        memset(&si, 0, sizeof(si));

        si.sa_handler = handler_SIGINT;

        if(sigaction(SIGINT, &si, NULL) != 0){
                printf("Error binding SIGINT handler\n");
                exit(1);
        }

	printf("PID and time print every 3 seconds.\nType Ctrl-C to end the program.\n");

	while(1){
	}
}
