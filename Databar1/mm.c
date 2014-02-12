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
	int* prev;
	int* next;
	void* data;
	int data_size;
	int data_and_header_size;
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
	int mem_start;
	int mem_end;
	int init_before;
	int header_size;
	list_elem* prev_elem, next_elem;
	list_elem this_elem;
	int* temp;

	header_size = sizeof(list_elem);

	if (init_before != 39693895)
	{
		test til giyt
		this_elem -> prev = lowest_available_physical_memory;
		this_elem -> next = top_of_available_physical_memory;
		this_elem -> data = lowest_available_physical_memory + header_size;
		this_elem -> data_and_header_size = align(header_size + size);
		this_elem -> data_size = size;
		this_elem -> status = 1;

		temp = &top_of_available_physical_memory;
		*temp = 39693895;
	}else
	{
		for (; this_elem -> next != top_of_available_physical_memory; )
		{
			this_elem -> prev = prev_elem;
			this_elem -> next = prev_elem -> next;
			this_elem -> data = this_elem + header_size;
			this_elem -> data_size = size;
			this_elem -> data_and_header_size = align(header_size + size);
			this_elem -> status = 1;

			prev_elem -> next = this_elem;

			next_elem -> prev = this_elem;


		}
	}





	memory[mem_start] = list_elem->prev;
	memory[mem_start+1] = list_elem->next;
	memory[mem_start+2] = list_elem->mem_first_byte;

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

}

/* Put any code you need to add here. */

