#pragma once

#include "Element.h"


class Queue {


public:
	Queue();
	Queue(int size);
	~Queue();

	int isFull();

	int isEmpty();

	int enQueue(ELEMENT* e);

	int deQueue(ELEMENT* e);

	int getPayload();

protected:
	ELEMENT* mBase;
	ELEMENT* mHdr;
	ELEMENT* mTail;
	int mSize;

};