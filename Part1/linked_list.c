//********************************************************
// Name			: Nicholas Warner and Jennings Fairchild
// Date			: 3 February 2015
// Subject		: CSCE 312-501
// Assignment	: Machine Problem 1
// Updated		: 8 February 2015
// Description	: Memory Management through Linked Lists
//********************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

// All the memory ever needed is allocated at startup.
// the list is a set size M
// Each node is a set size b
// the number of nodes is M/b

char* p;
char* headptr;
char* freeptr;		// there's a variable "free" in stdlio.h, so i had to change all the pointers to suffix ptr. who knew?
int basicBlockSize;
int numNodes;
int size;
int nxtptr;
int intsize;

// definitively works now
void Init ( int M, int b )	// M = amount of total memory bytes, b = basic block size/memory in each list node
{
	intsize = sizeof( int );
	nxtptr = sizeof( char* );
	size = 0;
	basicBlockSize = b;
	numNodes = M/b;
	char *msg = "Initial shit";
	int vl = 13;		// intitial shit is 13 characters with the null terminator "\n"
	char* temp;

	// memory
	p = (char*)malloc( M );				// allocate M memory
	headptr = p;						// set up the headptr
	freeptr = headptr;

	for ( int i = 0; i < numNodes; ++i )
	{
		temp = p + basicBlockSize;
		*(char**)p = temp;				// insert pointer to next node
		p += nxtptr;					// move up by the size of char*
		*(int*)p = -1;					// insert key at [4 or 8]
		p += intsize;					// move up by the size of an int
		*(int*)p = vl;					// insert value length at [8 or 12]
		p += intsize;					// move up by the size of an int
		memcpy( p, msg, vl );			// insert a value at [12 or 16]
		p += b - nxtptr - 2 * intsize;	// move to the next node
	}
	p = headptr;
}

void Destroy ()
{
	free( p );
}

int Insert ( int key, char* value_ptr, int value_len )	// use this to write Init
{
	int basicValueLength = basicBlockSize - 8 - sizeof( char* );
	if ( ( value_len < basicValueLength ) && ( size < numNodes ) )
	{
		// next ptr is already in existence at freeptr
		char *shift = freeptr;
		if ( ( size + 1 ) < numNodes )
			freeptr = *(char**)shift;		// move freeptr up a node

		//key
		shift += nxtptr;
		*(int*)shift = key;

		// value length
		shift += intsize;
		*(int*)shift = value_len;

		//value
		shift += intsize;
		memcpy( shift, value_ptr , value_len);

		// increment list size
		++size;
	}
}

int Delete ( int key )
{
	char *del = Lookup( key );
	if ( del != NULL )
	{
		free( del );
		--numNodes;
		return 0;
	}
	else
	{
		return 1;
	}
}

char* Lookup ( int key )
{
	char *shift = headptr + nxtptr;
	for ( int i = 0; i < size; ++i )
	{
		if ( *shift == key )
		{
			return shift;
		}
		else
			shift += basicBlockSize;
	}
	return NULL;
}

void PrintList ()
{
	char* temp;
	temp = headptr;
	for ( int i = 0; i < size; ++i )
	{
		printf( "Current: %x, Next: %x, Key = %d, Value Len = %d, Value: %s\n",
			temp, *(char**)temp, *(int *)(temp + nxtptr), *(int *)(temp + nxtptr + 4), temp + nxtptr + 8 );
		//temp += basicBlockSize;
		temp = *(char**)temp;
	}
} 