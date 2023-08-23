#pragma once


#include <stdio.h>

#include "Element.h"

#define DEFAULT_STACK_SIZE 0x4000




class Stack {

public:

	Stack();
	Stack(int size);

	~Stack();

	int push(ELEMENT* e);
	int pop(ELEMENT* e);

	int isEmpty();

	int isFull();

protected:
	ELEMENT* mBase = 0;
	ELEMENT* mPtr = 0;
	int mSize;

};