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
	int insert(ELEMENT* e);
	int remove(ELEMENT* e);

protected:
	LIST* search(ELEMENT* e);
	LIST* mList;
	int mSize;
};



class CList {
public:
	CList();
	~CList();
	int insert(ELEMENT* e);
	int remove(ELEMENT* e);

protected:
	LIST* search(ELEMENT* e);
	LIST* mList;
	int mSize;
};

