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
#include <string.h>
#include "linked_list.h"

// All the memory ever needed is allocated at startup.
// the list is a set size M
// Each node is a set size b
// the number of nodes is M/b

Node *headNP;
Node *freeNP;		// there's a variable "free" in stdlio.h, so i had to change all the pointers to suffix NP. who knew?
char* p;
char* headptr;
char* freeptr;
int basicBlockSize;
int numNodes;

// definitively works now
void Init ( int M, int b )	// M = amount of total memory bytes, b = basic block size/memory in each list node
{
	// variables to use
	basicBlockSize = b;
	numNodes = M/b;
	char *msg = "Initial shit";
	int vl = 13;		// intitial shit is 13 characters with the null termination "\n"
	char* temp;

	// memory
	p = (char*)malloc( M );				// allocate M memory
	headptr = p;						// set up the headptr

	for ( int i = 0; i < numNodes; ++i )
	{
		*(int*)p = i;						// insert key at [0]
		p += sizeof( int );					// move up by the size of an int
		*(int*)p = vl;						// insert value length at [4]
		p += sizeof( int );					// move up by the size of an int
		memcpy( p, msg, vl );				// insert a value at [8]
		p += b - 8;							// move to the next node
	}
}

void Destroy ()
{}

int Insert ( int key, char* value_ptr, int value_len )	// use this to write Init
{
	/*
	// key
	char* kaddr = freeNP + sizeof( char* );
	*(int*)kaddr = key;

	// value length
	char* vladdr = kaddr + sizeof( int );
	*(int*)vladdr = value_len;

	// value pointer
	char* valaddr = vladdr + sizeof( int );
	for ( int i = 0; i < value_len; ++i )
	{
		valaddr += i;
		value_len += i;
		*valaddr = *value_ptr;
	}
	*/
}
int Delete ( int key )
{}
char* Lookup ( int key )
{
	return NULL;
}
void PrintList ()
{
	char* temp;
	temp = headptr;
	for ( int i = 0; i < numNodes; ++i )
	{
		printf( "Key = %d, Value Len = %d, Value: %s\n", *(int *)temp , *(int *)(temp + 4), temp + 8 );
		temp += basicBlockSize;
	}
} 