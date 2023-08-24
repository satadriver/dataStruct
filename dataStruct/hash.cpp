
#include "hash.h"

#include "list.h"
#include <string.h>

Hash::Hash() {
	mBase = (LIST**) new LIST[DEFAULT_HASH_SIZE];
	memset((char*)mBase, 0, sizeof(LIST) * DEFAULT_HASH_SIZE);
	mSize = DEFAULT_HASH_SIZE;
}


Hash::Hash(int size) {
	mBase = (LIST**)new LIST[size];
	memset((char*)mBase, 0, sizeof(LIST) * size);
	mSize = size;
}


Hash::~Hash() {
	for (int i = 0; i < mSize; i++)
	{
		if (mBase[i])
		{
			LIST* p = mBase[i];
			do
			{
				if (p == 0)
				{
					break;
				}
				LIST* tmp = p->next;
				delete p->e;
				delete p;

				p = tmp;

			} while (p != mBase[i]);

			delete mBase[i];
		}
	}
	delete mBase;
}


LIST* Hash::search(ELEMENT* e) {
	int seq = e->e % mSize;
	LIST* p = (LIST*)mBase[seq];
	if (p->e->e == e->e)
	{
		return p;
	}

	LIST* list = p;

	do
	{
		if (list == 0)
		{
			break;
		}

		if (list->e->e == e->e)
		{
			return list;
		}

		list = list->next;
	} while (list != p);

	return 0;
}

int Hash::insert(ELEMENT* e) {

	int ret = 0;
	int seq = e->e % mSize;

	LIST* list = mBase[seq];
	if (list == 0) {
		list = new LIST;
		list->next = list;
		list->prev = list;
		list->e = new ELEMENT;
		memcpy(list->e, e, sizeof(ELEMENT));
		mBase[seq] = list;
		return 1;
	}

	CList clist(list);
	ret = clist.insert(e);
	return ret;
}

int Hash::remove(ELEMENT* e) {
	int ret = 0;
	int seq = e->e % mSize;

	LIST* list = mBase[seq];

	CList clist(list);
	ret = clist.remove(e);
	return ret;

}

