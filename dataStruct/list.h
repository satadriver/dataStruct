#pragma once

#include "Element.h"


#pragma pack(1)

typedef struct  _LIST
{
	_LIST* prev;
	_LIST* next;
	ELEMENT* e;
}LIST;

#pragma pack()


class List {
public:
	List();
	~List();
	List(LIST* l);
	int insert(ELEMENT* e);
	int remove(ELEMENT* e);

	int clear();
	LIST* get();
protected:
	LIST* search(ELEMENT* e);
	LIST* mList;
	int mSize;
};



class CList {
public:
	CList();
	~CList();
	CList(LIST* l);
	int insert(ELEMENT* e);
	int remove(ELEMENT* e);
	int clear();
	LIST* get();
protected:
	LIST* search(ELEMENT* e);
	LIST* mList;
	int mSize;
};

