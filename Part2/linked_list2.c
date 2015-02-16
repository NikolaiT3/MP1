//********************************************************
// Name			: Nicholas Warner and Jennings Fairchild
// Date			: 3 February 2015
// Subject		: CSCE 313-504
// Assignment	: Machine Problem 1
// Updated		: 15 February 2015
// Description	: Memory Management through Linked Lists
//********************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list2.h"

// All the memory ever needed is allocated at startup.
// the list is a set size memSize
// Each node is a set size blockSize
// the number of nodes is memSize / blockSize

int basicBlockSize;
int numNodes;
int size[ 1024 ];
int tiers;
int tierGap;
char *tierList[ 1024 ];
char *freePtrs[ 1024 ];
const int PTRSIZE = sizeof(char*);
const int INTSIZE = sizeof(int);

// returns what index a key should be placed in
int indexLookup( int key )
{
	int temp = tierGap;
	for ( int i = 0; i < tiers; ++i )
	{
		if ( key < temp )
		{
			return i;
		}
		temp += tierGap;
	}
}

// Moves the free pointer to an empty node at the lowest possible index.
// if in insert or delete, must be used AFTER incrementing or decrementing size
void freeReset( int index )
{
	char* temp = tierList[ index ];
	for ( int i = 0; i < size[ index ]; ++i )
	{
		if ( *(char**)temp != (temp + basicBlockSize) )
		{
			freePtrs[ index ] = temp + basicBlockSize;
		}
		else
		{
			temp += basicBlockSize;
		}
	}
}

// initializes each index of the tiers array
void indexInit( int memSize, int index )
{
	size[ index ] = 0;
	char *msg = " ";
	int msgLength = 2;
	tierList[ index ] = (char*)malloc( memSize );
	freePtrs[ index ] = tierList[ index ];

	for ( int i = 0; i < numNodes; ++i )
	{
		*(char**)freePtrs[ index ] = NULL;							// insert pointer to next node

		freePtrs[ index ] += PTRSIZE;								// move up by the size of char*
		*(int*)freePtrs[ index ] = 16;								// insert key at [4 or 8]

		freePtrs[ index ] += INTSIZE;								// move up by the size of an int
		*(int*)freePtrs[ index ] = msgLength;						// insert value length at [8 or 12]

		freePtrs[ index ] += INTSIZE;								// move up by the size of an int
		memcpy( freePtrs[ index ], msg, msgLength );				// insert a value at [12 or 16]
		freePtrs[ index ] += basicBlockSize - PTRSIZE - 2 * INTSIZE;// move to the next node
	}
	freePtrs[ index ] = tierList[ index ];
}

// memSize = amount of total memory bytes, blockSize = basic block size/memory in each list node
void Init( int memSize, int blockSize, int tierSize )
{
	tiers = tierSize;
	basicBlockSize = blockSize;
	numNodes = memSize / blockSize;
	tierGap = 2147483647 / tiers;					// 2^31 - 1 = 2147483647

	for ( int i = 0; i < tiers; ++i )
	{
		indexInit( memSize, i );
	}
}

void Destroy()
{
	for ( int i = 0; i < tiers; ++i )
	{
		free( tierList[ i ] );
	}
}

// use this to write to Init
int Insert( int key, char *valPtr, int valLength )
{
	int index = indexLookup( key );
	int basicValLength = basicBlockSize - 2 * INTSIZE - PTRSIZE;
	if ( size[ index ] == 0 )
	{
		freePtrs[ index ] += PTRSIZE;										// move up a pointer size
		*(int*)freePtrs[ index ] = key;										// insert key

		freePtrs[ index ] += INTSIZE;										// move up an int
		*(int*)freePtrs[ index ] = valLength;								// insert value length

		freePtrs[ index ] += INTSIZE;										// move up an int
		memcpy(freePtrs[ index ], " ", *(int*)(freePtrs[ index ] - INTSIZE));// delete the old contents
		memcpy(freePtrs[ index ], valPtr, valLength);						// insert message

		++(size[ index ]);													// increase list size
		freeReset( index );													// reset freeptr
		return 1;
	}
	else if ( size[ index ] > 0 && size[ index ] < numNodes )
	{
		freePtrs[ index ] -= basicBlockSize;								// move back a block
		*(char**)freePtrs[ index ] = freePtrs[ index ] + basicBlockSize;	// change it's next to point at this insert

		freePtrs[ index ] += basicBlockSize + PTRSIZE;						// move up a block and an int
		*(int*)freePtrs[ index ] = key;										// insert key

		freePtrs[ index ] += INTSIZE;										// move up an int
		*(int*)freePtrs[ index ] = valLength;								// insert value length

		freePtrs[ index ] += INTSIZE;										// move up an int
		memcpy(freePtrs[ index ], " ", *(int*)(freePtrs[ index ] - INTSIZE));// delete the old contents
		memcpy(freePtrs[ index ], valPtr, valLength);						// insert value

		++(size[ index ]);													// increase list size
		freeReset( index );													// reset freeptr
		return 1;
	}
	else
	{
		printf( "INSERT OVERFLOW ON TIER %u PREVENTED, KEY: %u\n", index, key );
		return 0;
	}
}

int Delete( int key )
{
	int index = indexLookup( key );
	char *del = Lookup( key, index );
	del -= PTRSIZE;
	if ( del != NULL && del != tierList[ index ] && freePtrs[ index ] > del )
	{
		del -= basicBlockSize;
		*(char**)del = del + 2 * basicBlockSize;
		--(size[ index ]);
		freeReset( index );
		return 1;
	}
	else if ( del == tierList[ index ] )
	{
		freePtrs[ index ] = tierList[ index ];
		--(size[ index ]);
		return 1;
	}
	else
	{
		return 0;
	}
}

// returns a pointer to the KEY
char* Lookup( int key, int index )
{
	char *shift = tierList[ index ];
	for ( int i = 0; i < size[ index ]; ++i )
	{
		if ( *(shift + PTRSIZE) == key )
		{
			return shift + PTRSIZE;
		}
		else
		{
			shift = *(char**)shift;
		}
	}
	return NULL;
}

void PrintList()
{
	char *temp;	
	for ( int i = 0; i < tiers; ++i )
	{
		temp = tierList[ i ];
		printf ( "tier: %u\n", i );
		for ( int k = 0; k < size[ i ]; ++k )
		{
			printf("Current: %x,\t Next: %x,\t Key = %d,\t Value Length = %d, Value: %s\n",
				temp, *(char**)temp, *(int*)(temp + PTRSIZE), *(int*)(temp + PTRSIZE + 4),
				temp + PTRSIZE + 8);
			if ( (k + 1) != size[ i ] )
			{
				temp = *(char**)temp;
			}
		}
	}
}