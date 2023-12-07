#pragma once

#include "Element.h"
#include "queue.h"
#include "list.h"
#include "stack.h"

#pragma pack(1)

typedef struct  _BBSTREE
{
	_BBSTREE* parent;
	_BBSTREE* lchild;
	_BBSTREE* rchild;

	int ld;

	int rd;

	ELEMENT data;
}BBST;

#pragma pack()

int deep(BBST* b);

class BBSTree {
public:
	BBSTree();
	~BBSTree();

	int insert(ELEMENT* e);

	int remove(ELEMENT* e);


	BBST* BBSTree::newnode(ELEMENT* e);

	BBST* search(ELEMENT* e);

	int ltr(List* list);
	int LTR(BBST* t, List* list, Stack* s);

	int rtr(List* list);

	int mtr(List* list);
private:
	int mSize;
	BBST* mTree;

};