//********************************************************
// Name			: Nicholas Warner and Jennings Fairchild
// Date			: 3 February 2015
// Subject		: CSCE 312-501
// Assignment	: Machine Problem 1
// Updated		: 3 February 2015
// Description	: Memory Management through Linked Lists
//********************************************************

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

void Init ( int M, int b )	// M = amount of total memory bytes, b = basic block size/memory in each list node
{
	head = malloc( M );
	basicBlockSize = b;
	Node temp;
	head->next = &temp;
	for ( int i = 0; i < M/b; ++i )
	{
	}
}

void Destroy ()
{}
void memset( char* buf, int b, int sizeOfBuf )
{}
int Insert ( int key, char* value_ptr, int value_len )
{}
int Delete ( int key )
{}
char* Lookup ( int key )
{
	return NULL;
}
void PrintList ()
{}