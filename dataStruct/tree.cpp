

#include "tree.h"
#include "queue.h"
#include "list.h"
#include "stack.h"

Tree::Tree() {


}


Tree::~Tree() {

}


int Tree::insert(ELEMENT* e) {

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

	while (t->lchild)
	{
		t = t->lchild;
		e.e = (unsigned __int64)t;
		s->push(&e);
	}

	list->insert(&e);

	if (t->rchild)
	{
		t = t->rchild;
		list->insert(&e);
		LTR(t, list, s);
	}

	if (s->isEmpty())
	{
		return 0;
	}
	s->pop(&e);
	t = (TREE*)e.e;

	list->insert(&e);
	t = t->rchild;
	LTR(t, list, s);

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