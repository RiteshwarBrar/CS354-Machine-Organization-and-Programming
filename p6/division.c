////////////////////////////////////////////////////////////////////////////////
// Main File:        division.c
// This File:        division.c
// Other Files:      mySigHandler.c, sendsig.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int ctr=0;// counts the number of successful divisions

/* The following is a Signal Handler for SIGFPE. It prints a message each time a SIGFPE signal is handled and
 * it also prints the number of times operations were completed successfully along with termination.
 *
 * The call to sigaction() in main should be successful in order for this handler to be assigned
 * and function properly
 */

void handler_SIGFPE() {

        printf("Error: a division by 0 operation was attempted.\n");
	printf("Total number of operations completed successfully: %d\n",ctr);
	printf("The program will be terminated.\n");

        exit(0);
}


/* The following is a Signal Handler for SIGINT. It prints a message each time a SIGINT signal is handled
 * along with termination
 *
 * The call to sigaction() in main should be successful in order for this handler to be assigned
 * and function properly
 */

void handler_SIGINT() {

	printf("\nTotal number of operations completed successfully: %d\n",ctr);
        printf("The program will be terminated.\n");

        exit(0);
}


/* 
 * This is the main function that contains all signal handler assignments and it also performs 
 * operations on numbers that are input by the user.
 *
 */

int main(){

	struct sigaction sf;
        memset(&sf, 0, sizeof(sf));

        sf.sa_handler = handler_SIGFPE;

        if(sigaction(SIGFPE, &sf, NULL) != 0){
                printf("Error binding SIGFPE handler\n");
                exit(1);
        }

	struct sigaction si;
        memset(&si, 0, sizeof(si));

        si.sa_handler = handler_SIGINT;

        if(sigaction(SIGINT, &si, NULL) != 0){
                printf("Error binding SIGINT handler\n");
                exit(1);
        }

	while(1){
		
		char* s1 = malloc(20*sizeof(char));
		char* s2 = malloc(20*sizeof(char));

		printf("Enter first integer: ");

		if(fgets(s1, 100, stdin ) == NULL){
			printf("Unsucessful at getting a value from the user");
		}

		int v1 = atoi(s1);//storing input strings as integers 

		printf("Enter second integer: ");
		
                if(fgets(s2, 100, stdin ) == NULL){
                        printf("Unsucessful at getting a value from the user");
                }
 
		int v2 = atoi(s2); 
		
		int quo = v1 / v2;//calculating the quotient
		int rem = v1 % v2;//calculating the remainder

		printf("%d / %d is %d with a remainder of %d\n",v1, v2, quo, rem);
		
		ctr+=1;//increamenting successful opertaions

		free(s1);//free the variable on heap memory
		free(s2);	

	}
}
