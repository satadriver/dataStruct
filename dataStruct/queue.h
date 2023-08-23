#pragma once

#include "Element.h"

#define DEFAULT_QUEUE_SIZE 0x1000


class Queue {

public:
	Queue();
	Queue(int size);
	~Queue();

	int isFull();

	int isEmpty();

	int enQueue(ELEMENT* e);

	int deQueue(ELEMENT* e);

protected:
	int getPayload();
	ELEMENT* mBase;
	ELEMENT* mHdr;
	ELEMENT* mTail;
	int mSize;

};