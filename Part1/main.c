//********************************************************
// Name			: Nicholas Warner and Jennings Fairchild
// Date			: 3 February 2015
// Subject		: CSCE 312-501
// Assignment	: Machine Problem 1
// Updated		: 3 February 2015
// Description	: Memory Management through Linked Lists
//********************************************************

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked_list.h"

int main ( int argc, char** argv ) 
{
	/*
	int key = 16;
	char tone = 'T';
	char tone2 = 'B';
	char* kaddr = &tone;
	printf( "key: %u, ", key);
	printf( "kaddr: %c, ", *kaddr );
	*(int*)kaddr = key;
	printf( "kaddr cast: %c", *(int*)kaddr );	// segmentation fault if *kaddr
	*/

	
	int b = 128;				// size of each node (128 bytes)
	int M = b * 11;				// total amount of memory (1408 bytes)
	
	char buf[1024];				// char array of 1024 bytes
	memset( buf, 1, 1024 );		// take buf and fill each byte with 1 for 1024 bytes
	
	char* msg = "a sample message";
	
	Init( M, b );				// initialize our list with 1408 bytes, block size of 128 bytes
	PrintList();
	/*
	// test operations
	int testnums[] = { 100, 5, 200, 7, 39, 25, 400, 50, 200, 300 };
	int i = 0;

	// some sample insertions
	for ( i = 0; i < 10; ++i )
	{
		Insert( testnums[ i ], buf, 50 );   // insert 50 bytes from the buffer as value for each of the insertions
	}

	Insert( 150, buf, 200 ); 				// this Insert should fail
	PrintList();
	Delete( 7 );
	Insert( 13, msg, strlen( msg ) + 1 );	// insertion of strings, copies the null byte at the end
	Delete( 55 );
	Insert( 15, "test msg", 8 );
	Delete( 3 );
	PrintList();
	
	// a sample lookup operations that should return null, because it is looking up a non-existent number
	char* kv = Lookup( 3 );
	if ( kv )
		printf( "Key = %d, Value Len = %d\n", *(int *)kv, *(int *)(kv + 4) );
	
	// this look up  should succeed and print the string "a sample message"
	kv = Lookup( 13 );
	if ( kv )
		printf( "Key = %d, Value Len = %d, Value = %s\n", *(int *)kv, *(int *)(kv + 4), kv + 8 );

	// end test operations	
	Destroy ();	*/
}