

#include "stack.h"


Stack::Stack() {
	if (mBase == 0)
	{
		mBase = new ELEMENT[DEFAULT_STACK_SIZE];
		mPtr = mBase;
		mSize = DEFAULT_STACK_SIZE;
	}
}


Stack::Stack(int size) {
	if (mBase == 0)
	{
		mBase = new ELEMENT[size];
		mPtr = mBase;
		mSize = size;
	}
}

Stack::~Stack() {
	if (mBase)
	{
		delete mBase;
		mBase = 0;
		mPtr = 0;
	}
}


int Stack::isFull() {
	return mPtr == (mBase + mSize);
}


int Stack::isEmpty() {
	return mBase == mPtr;
}


int Stack::push(ELEMENT* e) {
	if (mPtr < mBase + mSize)
	{
		*mPtr = *e;
		mPtr++;
		return mPtr - mBase;
	}
	return 0;
}


int Stack::pop(ELEMENT* e) {
	if (mPtr > mBase)
	{
		mPtr--;
		*e = *mPtr;
		return mPtr - mBase;
	}
	return 0;
}