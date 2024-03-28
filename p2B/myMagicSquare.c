///////////////////////////////////////////////////////////////////////////////
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Spring 2022, Deb Deppeler
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//// Main File:        myMagicSquare.c
//// This File:        myMagicSquare.c
//// Other Files:      none
//// Semester:         CS 354 Lecture 003 Spring 2022
//// Instructor:       deppeler
//// 
//// Author:           Riteshwar Singh Brar
//// Email:            rbrar@wisc.edu
//// CS Login:         riteshwar
////
///////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
////                   Fully acknowledge and credit all sources of help,
////                         other than Instructors and TAs.
////                   Do credit and acknowledge peer mentors, 
////                         tutors, friends, family, etc.
////
//// Persons:          Harry Wang, Peer mentor, wang2476@wisc.edu.
////                   helped me understand the problem in my code due to incorrect
////                   use of pointers.
////		       Shreyans Sakhlecha, Peer mentor, sakhlecha@wisc.edu
////		       Helped me understand the uses for my code related to the use
////		       of I/O statements.
////
////
//// Online sources:   none..
////////////////////////////// 80 columns wide ///////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
    int size;           // dimension of the square
    int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* TODO:
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize() {
     int n=0;
	printf("Enter magic square's size (odd integer >=3)\n");
        scanf("%i",&n);
	if(n%2==0){
		printf("Magic square size must be odd.\n");
		exit(1);
	}
	else if(n<3){
		printf("Magic square size must be >= 3.\n");
		exit(1);
	}
	return n;   
} 
   
/* TODO:
 * Makes a magic square of size n using the alternate 
 * Siamese magic square algorithm from assignment and 
 * returns a pointer to the completed MagicSquare struct.
 *
 * n the number of rows and columns
 */
MagicSquare *generateMagicSquare(int n) {
	MagicSquare* m = malloc(sizeof(MagicSquare));
	if(m==NULL){
		printf("Allocation Error: failed to allocate memory");
		exit(1);
	}
	m->size=n;
	m->magic_square = malloc(sizeof(int*) * m->size);
	if( m->magic_square == NULL){
	 	printf("Allocation Error: failed to allocate memory");
	        exit(1);
       }
	for(int i=0; i<(m->size) ; i++){
		*(m->magic_square + i) = malloc(sizeof(int) * m->size);
		if(*(m->magic_square+i)==NULL){
			printf("Allocation Error: failed to allocate memory");
			exit(1);
		}
	}
	for(int x=0;x<n;x++){
		for(int y=0;y<n;y++){
			*(*(m->magic_square + x ) + y )=0;
		}
	}

	int num=1;
	int row=((n+1)/2)-1 ; 	//finds the index of the central row
	int col=n-1;		//finds the index of the last col
	int tempr = row;
	int tempc = col;
	while(num<=(n*n)){
		tempr = row;
		tempc = col;
		*(*(m->magic_square + row) + col)=num;
		num++;
		if(tempr+1==n)
			tempr=0;
		else
			tempr++;
		if(tempc+1==n)
			tempc=0;
		else
			tempc++;

		if(*(*(m->magic_square + tempr)+tempc)==0){
			//checks for vacancy at the next index
			row=tempr;
			col=tempc;
		}
		else{
			if(col-1<0)
				col=n-1;
			else
				col--;
			}
	}
    return m;    
} 

/* TODO:  
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * magic_square the magic square to write to a file
 * filename the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {
	FILE *fp= fopen(filename,"w");
	if(fp == NULL) {
		printf("Can't open file for writing.\n");
		exit(1);
	}
	int temp;
	int s= magic_square->size;
	fprintf(fp,"%i\n", s);
	 for(int x=0;x < s ;x++){
		 for(int y=0;y < s ;y++){
                        temp=*(*(magic_square->magic_square + x ) + y );
			fprintf(fp,"%i",temp);
			if(y< (s)-1)
				fputs(",",fp);
		 }
		fputs("\n",fp);
	 }
	if(fclose(fp)!=0){
		printf("Error while closing the file.\n");
		exit(1);
	}
	
}

/* TODO:
 * Generates a magic square of the user specified size and
 * output the quare to the output filename
 *
 * argc the number of arguements passed when the program is run
 * argv an array of string values for each arguement passed in
 *      the terminal while running the program.
 */
int main(int argc, char **argv) {
    // TODO: Check input arguments to get output filename
	if(argc!=2){
		printf("Usage: ./myMagicSquare <output_filename>\n");
		exit(1);
	}
    // TODO: Get magic square's size from user
    	int x = getSize();
    // TODO: Generate the magic square
	MagicSquare* m = generateMagicSquare(x);
    // TODO: Output the magic square
	fileOutputMagicSquare( m, argv[1]);
	for(int i=0; i<(m->size) ; i++){
		free(*(m->magic_square + i));
	}
	free(m->magic_square);	
	free(m);
    return 0;
}


//  S22 deppeler myMagicSquare.c      
