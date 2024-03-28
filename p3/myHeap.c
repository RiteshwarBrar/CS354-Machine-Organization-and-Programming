///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020-2022 Deb Deppeler based on work by Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission Spring 2022, CS354-deppeler
//
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//// Main File:        Programs(tests) in the ./tests
//// This File:        myHeap.c
//// Other Files:      myHeap.h
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
//// Persons:          Harry Wang, Peer Mentor, wang2476@wisc.edu.
////                   Helped me understand the basic concept of the project 
////
//// Online sources:   none.
////////////////////////////// 80 columns wide ///////////////////////////////////

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include "myHeap.h"
 
/*
 * This structure serves as the header for each allocated and free block.
 * It also serves as the footer for each free block but only containing size.
 */
typedef struct blockHeader {           

    int size_status;
    /*
     * Size of the block is always a multiple of 8.
     * Size is stored in all block headers and in free block footers.
     *
     * Status is stored only in headers using the two least significant bits.
     *   Bit0 => least significant bit, last bit
     *   Bit0 == 0 => free block
     *   Bit0 == 1 => allocated block
     *
     *   Bit1 => second last bit 
     *   Bit1 == 0 => previous block is free
     *   Bit1 == 1 => previous block is allocated
     * 
     * End Mark: 
     *  The end of the available memory is indicated using a size_status of 1.
     * 
     * Examples:
     * 
     * 1. Allocated block of size 24 bytes:
     *    Allocated Block Header:
     *      If the previous block is free      p-bit=0 size_status would be 25
     *      If the previous block is allocated p-bit=1 size_status would be 27
     * 
     * 2. Free block of size 24 bytes:
     *    Free Block Header:
     *      If the previous block is free      p-bit=0 size_status would be 24
     *      If the previous block is allocated p-bit=1 size_status would be 26
     *    Free Block Footer:
     *      size_status should be 24
     */
} blockHeader;         

/* Global variable - DO NOT CHANGE. It should always point to the first block,
 * i.e., the block at the lowest address.
 */
blockHeader *heapStart = NULL;     

/* Size of heap allocation padded to round to nearest page size.
 */
int allocsize;

/*
 * Additional global variables may be added as needed below
 */

 
/* 
 * Function for allocating 'size' bytes of heap memory.
 * Argument size: requested size for the payload
 * Returns address of allocated block (payload) on success.
 * Returns NULL on failure.
 *
 * This function must:
 * - Check size - Return NULL if not positive or if larger than heap space.
 * - Determine block size rounding up to a multiple of 8 
 *   and possibly adding padding as a result.
 *
 * - Use BEST-FIT PLACEMENT POLICY to chose a free block
 *
 * - If the BEST-FIT block that is found is exact size match
 *   - 1. Update all heap blocks as needed for any affected blocks
 *   - 2. Return the address of the allocated block payload
 *
 * - If the BEST-FIT block that is found is large enough to split 
 *   - 1. SPLIT the free block into two valid heap blocks:
 *         1. an allocated block
 *         2. a free block
 *         NOTE: both blocks must meet heap block requirements 
 *       - Update all heap block header(s) and footer(s) 
 *              as needed for any affected blocks.
 *   - 2. Return the address of the allocated block payload
 *
 * - If a BEST-FIT block found is NOT found, return NULL
 *   Return NULL unable to find and allocate block for desired size
 *
 * Note: payload address that is returned is NOT the address of the
 *       block header.  It is the address of the start of the 
 *       available memory for the requesterr.
 *
 * Tips: Be careful with pointer arithmetic and scale factors.
 */
void* myAlloc(int size) {     
    //TODO: Your code goes in here.
	if(size<1 || size>allocsize){
		return NULL;
	}
	int blocksize=0;
	int remain= 8 - (size+sizeof(blockHeader))%8; //padding
	//if size+sizeof(blockheader is a multiple of 8 then no padding needed
	if(remain==8)
		remain=0;
	blocksize = size + sizeof(blockHeader) + remain;
	blockHeader* cur_pos = heapStart;
	blockHeader* lastBase=(blockHeader*)((void*)heapStart+allocsize) ;
        int tot_size = 0;
        int abs_size = 0;      
	//create a bookkeepr to track current best fit
	blockHeader* cur_best;
	//current best size
	int cur_best_size = -1;
	while( cur_pos->size_status != 1){
		abs_size = ((cur_pos->size_status)/8)*8;
		//case 1. memory is too smal move on
		if(blocksize > cur_pos->size_status){
		}
		else if(blocksize <= cur_pos->size_status){
			if(((cur_pos->size_status) % 8) % 2 != 0){
				
			}
			else if( abs_size == blocksize){
				cur_best = cur_pos;
				cur_best_size = abs_size;
				break;
			}
			else if(cur_best_size == -1){
				cur_best = cur_pos;
				cur_best_size = abs_size;
			}
			else if(cur_best_size > cur_pos->size_status){
				 cur_best = cur_pos;
	                         cur_best_size = abs_size;
			}
		}
		cur_pos = (blockHeader*)((void*)cur_pos + abs_size);
		//case 2. memory is big enough
		//2.1: if it's a perfect fit, set to cur addr, break
		//2.3: if cur_best not initialized (-1), set cur_best to cur
		//2.4 if cur_best initialized, then check if the cur is better 
	}
	//if cur_best -1 null
	if(cur_best_size == -1){
		return NULL;
	}
	cur_best->size_status += 1;//allocated
	
	//    printf("%d ",(cur_best->size_status));//used for debugging
	    //set the a bit
	//check if need to split
	tot_size = cur_best->size_status;
	abs_size = (tot_size / 8) * 8;
	if(abs_size - blocksize > 8 ){
		cur_best->size_status = blocksize + (tot_size % 8) ;//allocated block
		cur_best = (blockHeader*)((void*)cur_best + blocksize);//moving to next free space  
			cur_best->size_status = abs_size - blocksize + 2;//free-space header
			cur_best = (blockHeader*)((void*)cur_best + (abs_size-blocksize) - 4);//moving to free space footer
			cur_best-> size_status= abs_size - blocksize;
	       		cur_best= (blockHeader*)((void*)cur_best + 4 -(abs_size-blocksize) - blocksize + 4);//back to allocted payload
	}
	else{
		cur_best = (blockHeader*)((void*)cur_best + abs_size );//next header
		if(cur_best != lastBase)
			cur_best->size_status += 2;
	       	cur_best = (blockHeader*)((void*)cur_best - abs_size + 4 );//back to allocated payload 	
	}	
	//q

    return (void*)cur_best;
} 
 
/* 
 * Function for freeing up a previously allocated block.
 * Argument ptr: address of the block to be freed up.
 * Returns 0 on success.
 * Returns -1 on failure.
 * This function should:
 * - Return -1 if ptr is NULL.
 * - Return -1 if ptr is not a multiple of 8.
 * - Return -1 if ptr is outside of the heap space.
 * - Return -1 if ptr block is already freed.
 * - Update header(s) and footer as needed.
 */                    
int myFree(void *ptr) {    
    //TODO: Your code goes in here
    blockHeader* curr;
    blockHeader* foot;
    if(ptr==NULL || (int)(ptr) % 8 !=0)
    	return -1;
    
    if( ((void*)heapStart + allocsize ) < ptr || ptr <(void*)heapStart)
    	return -1; 
    
    curr = (blockHeader*)((void*)ptr - 4);

    if((curr->size_status) % 2 == 0){
	return -1;
    }
    blockHeader* nex = (blockHeader*)((void*)curr + (((curr->size_status) / 8) * 8));
    if(nex->size_status != 1)
	nex->size_status -= 2;
    
       
    curr->size_status -=1 ;
    foot=(blockHeader*)((void*)curr + (((curr->size_status) / 8) * 8) - 4);
    foot->size_status = ((curr->size_status) / 8 ) * 8;
    return 0;
} 

/*
 * Function for traversing heap block list and coalescing all adjacent 
 * free blocks.
 *
 * This function is used for delayed coalescing.
 * Updated header size_status and footer size_status as needed.
 */
int coalesce() {
    //TODO: Your code goes in here
    blockHeader* cur_pos = heapStart;
    blockHeader* nxt_pos;
   
    int tot_size = 0;
    int abs_size = 0;
    int chkr = 0;//checks whether adjacent blocks were coalesced
	while( cur_pos->size_status != 1){
		tot_size = cur_pos->size_status;
		abs_size = (tot_size / 8 ) * 8;
	       				
		if(tot_size % 2 == 0){
			
			nxt_pos = (blockHeader*)((void *)cur_pos + abs_size);
			while((nxt_pos->size_status) % 2 == 0){
				tot_size += ((nxt_pos->size_status) / 8) * 8;
				nxt_pos = (blockHeader*)((void *)nxt_pos + ((nxt_pos->size_status / 8 ) * 8 ));
				chkr += 1;
			}	
			cur_pos->size_status = tot_size;
			abs_size = (tot_size / 8 ) * 8;
			cur_pos = (blockHeader*)((void*)cur_pos + abs_size - 4);//coalesced free space footer
			cur_pos->size_status = abs_size;
			cur_pos = (blockHeader*)((void*)cur_pos + 4);
		
		}
		else{
			cur_pos = (blockHeader*)((void*)cur_pos + abs_size);
		}
	}	
	return chkr;
}

 
/* 
 * Function used to initialize the memory allocator.
 * Intended to be called ONLY once by a program.
 * Argument sizeOfRegion: the size of the heap space to be allocated.
 * Returns 0 on success.
 * Returns -1 on failure.
 */                    
int myInit(int sizeOfRegion) {    
 
    static int allocated_once = 0; //prevent multiple myInit calls
 
    int pagesize;   // page size
    int padsize;    // size of padding when heap size not a multiple of page size
    void* mmap_ptr; // pointer to memory mapped area
    int fd;

    blockHeader* endMark;
  
    if (0 != allocated_once) {
        fprintf(stderr, 
        "Error:mem.c: InitHeap has allocated space during a previous call\n");
        return -1;
    }

    if (sizeOfRegion <= 0) {
        fprintf(stderr, "Error:mem.c: Requested block size is not positive\n");
        return -1;
    }

    // Get the pagesize
    pagesize = getpagesize();

    // Calculate padsize as the padding required to round up sizeOfRegion 
    // to a multiple of pagesize
    padsize = sizeOfRegion % pagesize;
    padsize = (pagesize - padsize) % pagesize;

    allocsize = sizeOfRegion + padsize;

    // Using mmap to allocate memory
    fd = open("/dev/zero", O_RDWR);
    if (-1 == fd) {
        fprintf(stderr, "Error:mem.c: Cannot open /dev/zero\n");
        return -1;
    }
    mmap_ptr = mmap(NULL, allocsize, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (MAP_FAILED == mmap_ptr) {
        fprintf(stderr, "Error:mem.c: mmap cannot allocate space\n");
        allocated_once = 0;
        return -1;
    }
  
    allocated_once = 1;

    // for double word alignment and end mark
    allocsize -= 8;

    // Initially there is only one big free block in the heap.
    // Skip first 4 bytes for double word alignment requirement.
    heapStart = (blockHeader*) mmap_ptr + 1;

    // Set the end mark
    endMark = (blockHeader*)((void*)heapStart + allocsize);
    endMark->size_status = 1;

    // Set size in header
    heapStart->size_status = allocsize;

    // Set p-bit as allocated in header
    // note a-bit left at 0 for free
    heapStart->size_status += 2;

    // Set the footer
    blockHeader *footer = (blockHeader*) ((void*)heapStart + allocsize - 4);
    footer->size_status = allocsize;
  
    return 0;
} 
                  
/* 
 * Function to be used for DEBUGGING to help you visualize your heap structure.
 * Prints out a list of all the blocks including this information:
 * No.      : serial number of the block 
 * Status   : free/used (allocated)
 * Prev     : status of previous block free/used (allocated)
 * t_Begin  : address of the first byte in the block (where the header starts) 
 * t_End    : address of the last byte in the block 
 * t_Size   : size of the block as stored in the block header
 */                     
void dispMem() {     
 
    int counter;
    char status[6];
    char p_status[6];
    char *t_begin = NULL;
    char *t_end   = NULL;
    int t_size;

    blockHeader *current = heapStart;
    counter = 1;

    int used_size = 0;
    int free_size = 0;
    int is_used   = -1;

    fprintf(stdout, 
	"*********************************** Block List **********************************\n");
    fprintf(stdout, "No.\tStatus\tPrev\tt_Begin\t\tt_End\t\tt_Size\n");
    fprintf(stdout, 
	"---------------------------------------------------------------------------------\n");
  
    while (current->size_status != 1) {
        t_begin = (char*)current;
        t_size = current->size_status;
    
        if (t_size & 1) {
            // LSB = 1 => used block
            strcpy(status, "alloc");
            is_used = 1;
            t_size = t_size - 1;
        } else {
            strcpy(status, "FREE ");
            is_used = 0;
        }

        if (t_size & 2) {
            strcpy(p_status, "alloc");
            t_size = t_size - 2;
        } else {
            strcpy(p_status, "FREE ");
        }

        if (is_used) 
            used_size += t_size;
        else 
            free_size += t_size;

        t_end = t_begin + t_size - 1;
    
        fprintf(stdout, "%d\t%s\t%s\t0x%08lx\t0x%08lx\t%4i\n", counter, status, 
        p_status, (unsigned long int)t_begin, (unsigned long int)t_end, t_size);
    
        current = (blockHeader*)((char*)current + t_size);
        counter = counter + 1;
    }

    fprintf(stdout, 
	"---------------------------------------------------------------------------------\n");
    fprintf(stdout, 
	"*********************************************************************************\n");
    fprintf(stdout, "Total used size = %4d\n", used_size);
    fprintf(stdout, "Total free size = %4d\n", free_size);
    fprintf(stdout, "Total size      = %4d\n", used_size + free_size);
    fprintf(stdout, 
	"*********************************************************************************\n");
    fflush(stdout);

    return;  
} 


// end of myHeap.c (Spring 2022)                                         


