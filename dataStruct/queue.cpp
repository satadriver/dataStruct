

#include "queue.h"




Queue::Queue() {
	if (mBase == 0)
	{
		mBase = new ELEMENT[DEFAULT_QUEUE_SIZE];
		mSize = DEFAULT_QUEUE_SIZE;
		mHdr = mBase;
		mTail = mBase;
	}
}
Queue::Queue(int size) {
	if (mBase == 0)
	{
		mBase = new ELEMENT[size];
		mSize = size;
		mHdr = mBase;
		mTail = mBase;
	}
}
Queue::~Queue() {
	if (mBase)
	{
		delete[] mBase;
		mBase = 0;
		mTail = 0;
		mHdr = 0;
		mSize = 0;
	}
}

int Queue::isFull() {
	ELEMENT* next = mTail;
	if (next == mBase + mSize)
	{
		next = mBase;
	}
	else {
		next++;
	}

	if (next == mHdr)
	{
		return 1;
	}

	return 0;
}

int Queue::isEmpty() {
	return mHdr == mTail;
}

int Queue::getPayload() {
	if (mTail > mHdr)
	{
		return mTail - mHdr;
	}
	else {
		return mSize - (mHdr - mTail);
	}
}

int Queue::enQueue(ELEMENT* e) {

	*mTail = *e;

	mTail++;
	if (mTail == mBase + mSize)
	{
		mTail = mBase;
	}

	return getPayload();
}

int Queue::deQueue(ELEMENT* e) {
	if (mHdr == mTail)
	{
		return 0;
	}

	*e = *mHdr;

	mHdr++;
	if (mHdr == mBase + mSize)
	{
		mHdr = mBase;
	}

	return getPayload();
}