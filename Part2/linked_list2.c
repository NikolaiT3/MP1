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
#include "linked_list2.h"

// All the memory ever needed is allocated at startup.
// the list is a set size memSize
// Each node is a set size blockSize
// the number of nodes is memSize / blockSize

char* p;
char* headPtr;
char* freePtr;
int basicBlockSize;
int numNodes;
int size;
const int PTRSIZE = sizeof(char*);
const int INTSIZE = sizeof(int);

// memSize = amount of total memory bytes, blockSize = basic block size/memory in each list node
void Init(int memSize, int blockSize) {
	size = 0;
	basicBlockSize = blockSize;
	numNodes = memSize / blockSize;
	char* msg = "Basic Message";
	int msgLength = msg.size() + 1;					// Add one for the "\n" null terminator

	// Memory
	p = (char*)malloc(memSize);						// allocate memSize memory
	headPtr = p;									// set up the headPtr
	freePtr = headPtr;

	for (int i = 0; i < numNodes; ++i) {
		*(char**)p = NULL;							// insert pointer to next node
		p += PTRSIZE;								// move up by the size of char*
		*(int*)p = -1;								// insert key at [4 or 8]
		p += INTSIZE;								// move up by the size of an int
		*(int*)p = msgLength;						// insert value length at [8 or 12]
		p += INTSIZE;								// move up by the size of an int
		memcpy(p, msg, msgLength);					// insert a value at [12 or 16]
		p += blockSize - PTRSIZE - 2 * INTSIZE;		// move to the next node
	}
	p = headPtr;
}

void freeReset() {
	char* temp = headPtr;
	for (int i = 0; i < size; ++i) {
		if (*(char**)temp != (temp + basicBlockSize)) {
			freePtr = temp + basicBlockSize;
		}
		else {
			temp += basicBlockSize;
		}
	}
}

void Destroy() {
	free(p);
}

// use this to write to Init
int Insert(int key, char* valPtr, int valLength) {
	int basicValLength = basicBlockSize - 2 * INTSIZE - PTRSIZE;
	if (size == 0) {
		freePtr += PTRSIZE;								// move up a pointer size
		*(int*)freePtr = key;							// insert key
		freePtr += INTSIZE;								// move up an int
		*(int*)freePtr = valLength;						// insert value length
		freePtr += INTSIZE;								// move up an int
		memcpy(freePtr, " ", *(int*)(freePtr - INTSIZE));// delete the old contents
		memcpy(freePtr, valPtr, valLength);				// insert message
		++size;											// increase list size
		freeReset();									// reset freeptr
		return 1;
	}
	else if (size != 0) {
		freePtr -= basicBlockSize;						// move back a block
		*(char**)freePtr = freePtr + basicBlockSize;	// change it's next to point at this insert
		freePtr += basicBlockSize + PTRSIZE;			// move up a block and an int
		*(int*)freePtr = key;							// insert key
		freePtr += INTSIZE;								// move up an int
		*(int*)freePtr = valLength;						// insert value length
		freePtr += INTSIZE;								// move up an int
		memcpy(freePtr, " ", *(int*)(freePtr - INTSIZE));// delete the old contents
		memcpy(freePtr, valPtr, valLength);				// insert value
		++size;											// increase list size
		freeReset();									// reset freeptr
		return 1;
	}
	else {
		return 0;
	}
}

int Delete(int key) { 
	char* del = Lookup(key);
	del -= PTRSIZE;
	if (del != NULL && del != headPtr && freePtr > del) {
		del -= basicBlockSize;
		*(char**)del = del + 2 * basicBlockSize;
		--size;
		freeReset();
		return 1;
	}
	else if (del == headPtr) {
		freePtr = headPtr;
		--size;
		return 1;
	}
	else {
		return 0;
	}
}

char* Lookup(int key) {
	char* shift = headPtr;
	for (int i = 0; i < size; ++i) {
		if (*(shift + PTRSIZE) == key) {
			return shift + PTRSIZE;
		}
		else {
			shift = *(char**)shift;
		}
	}
	return NULL;
}

void PrintList() {
	char* temp;
	temp = headPtr;
	for (int i = 0; i < size; ++i) {
		printf("Current: %x, Next: %x, Key = %d, Value Length = %d, Value: %s\n",
			temp, *(char**)temp, *(int*)(temp + PTRSIZE), *(int*)(temp + PTRSIZE + 4),
			temp + PTRSIZE + 8);
		if ((i + 1) != size) {
			temp = *(char**)temp;
		}
	}
}
