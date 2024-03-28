////////////////////////////////////////////////////////////////////////////////
//////////// Main File:        All 4 files mentioned below
//////////// This File:        cache2Dclash.c
//////////// Other Files:      cache1D.c, cache2Drows.c, cache2Dcols.c
//////////// Semester:         CS 354 Lecture 003 Spring 2022
//////////// Instructor:       deppeler
////////////
//////////// Author:           Riteshwar Singh Brar
//////////// Email:            rbrar@wisc.edu
//////////// CS Login:         riteshwar
////////////
///////////////////////////////////// OTHER SOURCES OF HELP //////////////////////////////////////                   Fully acknowledge and credit all sources of help,
////////////                         other than Instructors and TAs.
////////////                   Do credit and acknowledge peer mentors,
////////////                         tutors, friends, family, etc.
////////////
//////////// Persons:          none.
////////////
//////////// Online sources:   none.
////////////////////////////////////// 80 columns wide ///////////////////////////////

int arr2D[128][8];

int main(){

        for(int i = 0; i < 100 ; i++){

		for(int row = 0; row < 128; row+=64){
			
			for( int col = 0; col < 8; col++){
				
				arr2D[row][col] = i + row + col;//i=iteration
			}
		}
        }
}
