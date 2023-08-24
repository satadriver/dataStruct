#pragma once

#include "Element.h"
#include "list.h"

#define DEFAULT_HASH_SIZE 0x10000

class Hash {
public:
	Hash();
	~Hash();
	Hash(int size);

	LIST* search(ELEMENT* e);
	int insert(ELEMENT* e);
	int remove(ELEMENT* e);

protected:
	LIST** mBase;
	int mSize;
};