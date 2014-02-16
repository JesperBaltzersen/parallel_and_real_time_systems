/**
 * @file   mm.c
 * @Author Nicklas Bo Jensen (nboa@dtu.dk)
 * @date   January, 2014
 * @brief  Memory management skeleton.
 * 
 * Copyright 2013-14 Nicklas Bo Jensen, et. al., All rights reserved.
 *
 * You are allowed to change the file for the purpose of solving
 * exercises in the 02333 course at DTU. You are not allowed to
 * change this message or disclose this file to anyone except for
 * course staff in the 02333 course at DTU. Disclosing contents
 * to fellow course mates or redistributing contents is a direct
 * violation.
 *
 * Replace the functions in this file with your own implementations.
 * You should not modify the function prototypes. 
 * 
 * As part of the assignment add new unit tests in 
 * check_mm.c.
 *
 */

#include <stdint.h>
#include "mm.h"

int align(int data_size);

typedef struct S {
	struct S* prev;
	struct S* next;
	void* data;
	int data_size;
	int status; //1 for full, 0 for empty
} list_elem;
/**
 * @name    embedded_malloc
 * @brief   Allocate at least size contiguous bytes of memory and return a pointer to the first byte.
 *
 * This function should behave similar to a normal malloc implementation. 
 *
 * @param size_t size Number of bytes to allocate.
 * @retval Pointer to the start of the allocated memory.
 *
 */
void* embedded_malloc(size_t size) {
/**
 * \todo { Implement malloc here. }
*/
	int mem_start, mem_end;
	int initialized;
	int header_size, mem_size;
	list_elem *this_elem, *new_elem;

	//init values
	mem_start = (int)lowest_available_physical_memory;
	mem_end = ((int)top_of_available_physical_memory) - 1;	//top_mem = initialized variable

	//init linked list elem.
	this_elem = (list_elem*)lowest_available_physical_memory;

	//align all sizes to 32 bit values
	header_size = align(sizeof(list_elem));
	mem_size = align(size);

	//initialized holds value of last point in memory. Used to determine if the memory has been initialized before.
	//If the value of initialized is == 39693896 then it has been init before.
	initialized = *(int* )top_of_available_physical_memory;

	if (initialized != 39693895)
	{

		this_elem -> prev = (list_elem *)mem_start;
		this_elem -> next = (list_elem *)mem_end;
		this_elem -> data = (void *)(mem_start + header_size);
		this_elem -> data_size = mem_size;
		this_elem -> status = 1;

		initialized = 39693895;

	}else{

		do{
			//If this elements data_size >= requested size and not big enough that there is room for an extra
			//elements in the space that is left after the allocation then we use all the space
			if ( (this_elem -> data_size >= mem_size) && (this_elem -> data_size <= mem_size + header_size) ){

				return this_elem -> data;

			//If the this elements data size > requested size and big enough that there is room for an extra element
			//we create a new element with free data chunk in the space that is left over
			}else if ( (this_elem -> data_size + header_size) > mem_size){

				//create new elem in space that is left after allocating new mem block
				new_elem = this_elem + mem_size;
				new_elem -> prev = this_elem;
				new_elem -> next = this_elem -> next;
				new_elem -> data = new_elem + header_size;
				new_elem -> data_size = this_elem -> data_size - mem_size - header_size;
				new_elem -> status = 0;

				//update this_elem
				this_elem -> next = new_elem;
				this_elem -> data_size = mem_size;
				this_elem -> status = 1;

				return this_elem -> data;

			}else{ //if we didn't find a space search next element of linked list
				this_elem = this_elem -> next;
			}
		}
		//stop searching if this element next pointer points to last place in memory
		while ((int)this_elem -> next != mem_end);
	}

	//return 0 if we don't have space in memory
	return 0;
}

int align(int data_size)
{
	return (((data_size / 32) + 1 )* 32) - data_size;
}

/**
 * @name    embedded_free
 * @brief   Frees previously allocated memory and make it available for subsequent calls to embedded_malloc
 *
 * This function should behave similar to a normal free implementation. 
 *
 * @param void *ptr Pointer to the memory to free.
 *
 */
void embedded_free(void * ptr) {
/**
 * \todo { Implement free here. }
*/
	list_elem *this_elem, *prev_elem, *next_elem;
	int header_size;

	this_elem = (list_elem*)ptr;

	header_size = align(sizeof(list_elem));

	//setup adjacent linked list elements
	prev_elem = this_elem -> prev;
	next_elem = this_elem -> next;

	//if adjacent elements are free, merge them with this one

	//both elements are free add size of both headers and their data
	if ((prev_elem -> status == 0) && (next_elem -> status == 0)){
		prev_elem -> data_size = prev_elem -> data_size + 2*header_size + this_elem -> data_size + next_elem -> data_size;

	//if only prev_elem is free
	}else if ( prev_elem -> status == 0){
		prev_elem -> data_size = prev_elem -> data_size + header_size + this_elem -> data_size;

	//if only next_elem is free
	}else if ( next_elem -> status == 0){
		this_elem -> data_size = this_elem -> data_size + header_size + next_elem -> data_size;

	//if no adjacent elements are free just update status of this one
	}else{
		this_elem -> status = 0;
	}

}
