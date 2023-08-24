

#include "tree.h"
#include "queue.h"
#include "list.h"
#include "stack.h"

Tree::Tree() {
	mTree = 0;
	mSize = 0;
}


Tree::~Tree() {
	List list;
	ltr(&list);

	list.clear();

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
		mSize = 1;
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
				mSize++;
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
				mSize++;
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

	TREE* t = search(e);
	if (t == 0)
	{
		return 0;
	}

	TREE* parent = t->parent;
	TREE* lchild = t->lchild;
	TREE* rchild = t->rchild;

	if (lchild == 0 && rchild == 0)
	{
		if (parent->lchild == t)
		{
			parent->lchild = 0;
		}
		else if (parent->rchild == t)
		{
			parent->rchild = 0;
		}
		else {
			return 0;
		}
	}
	else if (lchild == 0)
	{
		if (parent->lchild == t)
		{
			parent->lchild = rchild;
		}
		else if (parent->rchild == t)
		{
			parent->rchild = rchild;
		}
		else {
			return 0;
		}
	}
	else if (rchild == 0)
	{
		if (parent->lchild == t)
		{
			parent->lchild = lchild;
		}
		else if (parent->rchild == t)
		{
			parent->rchild = lchild;
		}
		else {
			return 0;
		}
	}
	else {
		//left subtree upwards and move right subtree ,or right subtree upwards and move left subtree
		if (parent->lchild == t)
		{
			parent->lchild = lchild;
			lchild->parent = parent;

			TREE* tmp = lchild;
			while (tmp->rchild)
			{
				tmp = tmp->rchild;
			}
			tmp->rchild = rchild;
			rchild->parent = tmp;


			/*parent->lchild = rchild;
			rchild->parent = parent;

			TREE* tmp = rchild;
			while (tmp->lchild)
			{
				tmp = tmp->lchild;
			}
			tmp->lchild = lchild;
			lchild->parent = tmp; */

		}
		else if (parent->rchild == t)
		{
			parent->rchild = lchild;
			lchild->parent = parent;

			TREE* tmp = lchild;
			while (tmp->rchild)
			{
				tmp = tmp->rchild;
			}
			tmp->rchild = rchild;
			rchild->parent = tmp;


			/*
			parent->rchild = rchild;
			rchild->parent = parent;

			TREE* tmp = rchild;
			while (tmp->lchild)
			{
				tmp = tmp->lchild;
			}
			tmp->lchild = lchild;
			lchild->parent = tmp;*/
		}
		else {
			return 0;
		}
	}

	return 0;
}


TREE* Tree::search(ELEMENT* e) {
	if (mTree == 0)
	{
		return 0;
	}

	TREE* t = mTree;

	while (1) {
		if (e->e == t->data.e) {
			return t;
		}
		else if (e->e > t->data.e)
		{
			if (t->rchild == 0)
			{
				break;
			}
			else {
				t = t->rchild;
			}
		}
		else {
			if (t->lchild == 0)
			{
				break;
			}
			else {
				t = t->lchild;
			}
		}
	}

	return 0;
}

int Tree::LTR(TREE* t, List* list, Stack* s) {

	int cnt = 0;

	ELEMENT e;

	if (t == 0)
	{
		return cnt;
	}

	while (t->lchild)
	{
		e.e = (unsigned __int64)t;
		s->push(&e);

		t = t->lchild;
	}

	e.e = (unsigned __int64)t;
	e.data = t->data.data;
	list->insert(&e);
	cnt++;
	printf("get LTR element:%lld value:%lld\r\n", e.e, t->data.e);

	if (t->rchild)
	{
		t = t->rchild;
		cnt += LTR(t, list, s);
	}

	while (s->isEmpty() == 0)
	{
		s->pop(&e);

		t = (TREE*)e.e;

		list->insert(&e);
		cnt++;
		printf("get LTR element:%lld value:%lld\r\n", e.e, t->data.e);

		t = t->rchild;

		cnt += LTR(t, list, s);
	}

	return cnt;
}

int Tree::ltr(List* list) {
	int cnt = 0;
	TREE* t = mTree;
	if (t == 0)
	{
		return 0;
	}

	Stack s;


	cnt = LTR(t, list, &s);

	return cnt;
}

int Tree::rtr(List* list) {
	return 0;
}

int Tree::mtr(List* list) {
	return 0;
}