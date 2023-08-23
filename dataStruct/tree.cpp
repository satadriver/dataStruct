

#include "tree.h"
#include "queue.h"
#include "list.h"
#include "stack.h"

Tree::Tree() {
	mTree = 0;

}


Tree::~Tree() {
	if (mTree)
	{
		delete mTree;
	}
}


int Tree::insert(ELEMENT* e) {
	if (mTree == 0)
	{
		mTree = new TREE;
		mTree->data.e = e->e;
		mTree->parent = 0;
		mTree->lchild = 0;
		mTree->rchild = 0;
		return 1;
	}

	TREE* t = mTree;

	while (1) {
		if (e->e == t->data.e) {
			return 0;
		}
		else if (e->e > t->data.e)
		{
			if (t->rchild == 0)
			{
				TREE* newt = new TREE;
				newt->data.e = e->e;
				newt->lchild = 0;
				newt->rchild = 0;
				newt->parent = t;
				t->rchild = newt;
				break;
			}
			else {
				t = t->rchild;
			}
		}
		else {
			if (t->lchild == 0)
			{
				TREE* newt = new TREE;
				newt->data.e = e->e;
				newt->lchild = 0;
				newt->rchild = 0;
				newt->parent = t;

				t->lchild = newt;
				break;
			}
			else {
				t = t->lchild;
			}
		}
	}

	return 0;
}

int Tree::remove(ELEMENT* e) {
	return 0;
}

int Tree::LTR(TREE* t, List* list, Stack* s) {
	if (t == 0)
	{
		return 0;
	}

	int cnt = 0;

	ELEMENT e;

	e.e = (unsigned __int64)t;
	s->push(&e);
	cnt++;

	while (1) {

		while (t->lchild)
		{
			t = t->lchild;
			e.e = (unsigned __int64)t;
			s->push(&e);
		}

		list->insert(&e);
		printf("get LTR element:%lld\r\n", e.e);

		if (t->rchild)
		{
			t = t->rchild;
			list->insert(&e);
			printf("get LTR element:%lld\r\n", e.e);
			continue;
		}

		if (s->isEmpty())
		{
			return 0;
		}
		else {
			s->pop(&e);
			t = (TREE*)e.e;

			list->insert(&e);
			printf("get LTR element:%lld\r\n", e.e);
			t = t->rchild;
		}

	}

	return 0;
}

int Tree::ltr(List* list) {
	int cnt = 0;
	TREE* t = mTree;
	if (t == 0)
	{
		return 0;
	}

	Stack s;

	LTR(t, list, &s);

	return cnt;
}

int Tree::rtr(List* list) {
	return 0;
}

int Tree::mtr(List* list) {
	return 0;
}