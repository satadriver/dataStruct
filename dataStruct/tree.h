#pragma once

#include "Element.h"
#include "queue.h"
#include "list.h"
#include "stack.h"

#pragma pack(1)

typedef struct  _TREE
{
	_TREE* parent;
	_TREE* lchild;
	_TREE* rchild;

	ELEMENT data;
}TREE;

#pragma pack()

class Tree {
public:
	Tree();
	~Tree();

	int insert(ELEMENT* e);

	int remove(ELEMENT* e);

	TREE* search(ELEMENT* e);

	TREE* newnode(ELEMENT* e);

	int ltr(List* list);
	int LTR(TREE* t, List* list, Stack* s);

	int rtr(List* list);

	int mtr(List* list);
private:
	int mSize;
	TREE* mTree;

};