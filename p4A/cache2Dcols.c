////////////////////////////////////////////////////////////////////////////////
////////// Main File:        All 4 files mentioned below
////////// This File:        cache2Dcols.c
////////// Other Files:      cache1D.c, cache2Drows.c, cache2Dclash.c
////////// Semester:         CS 354 Lecture 003 Spring 2022
////////// Instructor:       deppeler
//////////
////////// Author:           Riteshwar Singh Brar
////////// Email:            rbrar@wisc.edu
////////// CS Login:         riteshwar
//////////
/////////////////////////////////// OTHER SOURCES OF HELP //////////////////////////////////////                   Fully acknowledge and credit all sources of help,
//////////                         other than Instructors and TAs.
//////////                   Do credit and acknowledge peer mentors,
//////////                         tutors, friends, family, etc.
//////////
////////// Persons:          none.
//////////
////////// Online sources:   none.
//////////////////////////////////// 80 columns wide /////////////////////////////////

int arr2D[3000][500];

int main(){

	for(int col = 0; col < 500 ; col++){

	        for(int row = 0; row < 3000; row++){
			arr2D[row][col] = row + col;
		}
	
	}

}
