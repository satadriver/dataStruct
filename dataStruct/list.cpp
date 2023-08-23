
#include <string.h>
#include "list.h"



List::List() {
	mList = 0;
	mSize = 0;
}


List::~List() {
	if (mList)
	{
		delete[] mList;
		mList = 0;
	}
}

LIST* List::search(ELEMENT* e) {
	LIST* list = mList;
	int cnt = 0;
	while (list)
	{
		if (list->e->e == e->e)
		{
			return list;
		}
		list = list->next;
		cnt++;
	}

	return 0;
}





int List::insert(ELEMENT* e) {
	LIST* list = search(e);
	if (list)
	{
		return 0;
	}

	list = new LIST;

	ELEMENT* e_new = new ELEMENT;
	memcpy(e_new, e, sizeof(ELEMENT));

	list->e = e_new;

	int cnt = 0;

	if (mList == 0)
	{
		list->next = 0;
		list->prev = 0;
		mList = list;

		cnt++;
	}
	else {
		LIST* tmp = mList;
		while (tmp->next)
		{
			tmp = tmp->next;
			cnt++;
		}

		list->next = 0;
		list->prev = tmp;

		tmp->next = list;

		cnt++;
	}

	mSize = cnt;

	return cnt;
}


int List::remove(ELEMENT* e) {
	LIST* list = search(e);
	if (list == 0)
	{
		return 0;
	}

	LIST* next = list->next;
	LIST* prev = list->prev;
	if (next)
	{
		next->prev = prev;
	}

	if (prev)
	{
		prev->next = next;
	}

	delete list->e;
	if (list == mList)
	{
		if (mList->next == 0)
		{
			mList = 0;
		}
		else {
			mList = mList->next;
		}
	}

	delete list;

	int result = mSize;

	mSize--;

	return result;
}











CList::CList() {
	mList = 0;
	mSize = 0;
}


CList::~CList() {
	if (mList)
	{
		delete[] mList;
		mList = 0;
	}
}

LIST* CList::search(ELEMENT* e) {
	LIST* list = mList;
	int cnt = 0;
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
		cnt++;
	} while (list != mList);

	return 0;
}

int CList::insert(ELEMENT* e) {
	LIST* list = search(e);
	if (list)
	{
		return 0;
	}

	list = new LIST;

	ELEMENT* e_new = new ELEMENT;
	memcpy(e_new, e, sizeof(ELEMENT));

	list->e = e_new;

	if (mList == 0)
	{
		list->next = list;
		list->prev = list;
		mList = list;
	}
	else {
		LIST* prev = mList->prev;

		list->next = mList;
		list->prev = mList->prev;

		if (prev)
		{
			prev->next = list;
		}

		mList->prev = list;
	}

	mSize++;

	return 1;
}


int CList::remove(ELEMENT* e) {
	LIST* list = search(e);
	if (list == 0)
	{
		return 0;
	}

	LIST* next = list->next;
	LIST* prev = list->prev;
	if (next)
	{
		next->prev = prev;
	}

	if (prev)
	{
		prev->next = next;
	}

	delete list->e;

	if (list == mList)
	{
		if (mList->next == mList || mList->prev == mList)
		{
			mList = 0;
		}
		else {
			mList = mList->next;
		}
	}

	delete list;

	int result = mSize;

	mSize--;

	return result;
}