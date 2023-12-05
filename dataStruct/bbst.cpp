

#include "bbst.h"
#include "queue.h"
#include "list.h"
#include "stack.h"

BBSTree::BBSTree() {
	mTree = 0;
	mSize = 0;
}


BBSTree::~BBSTree() {
	List list;
	ltr(&list);

	list.clear();

	if (mTree)
	{
		delete mTree;
	}
}


BBST* BBSTree::newnode(ELEMENT* e) {

	BBST* t = new BBST;
	t->data.e = e->e;
	t->parent = 0;
	t->lchild = 0;
	t->rchild = 0;
	t->depth = 0;

	return t;
}

int BBSTree::insert(ELEMENT* e) {
	if (mTree == 0)
	{
		mTree = newnode(e);
		mSize = 1;
		return 1;
	}

	BBST* t = mTree;

	Stack s;

	while (1) {
		if (e->e == t->data.e) {
			return 0;
		}
		else if (e->e > t->data.e)
		{
			if (t->rchild == 0)
			{
				BBST* newt = newnode(e);
				newt->parent = t;
				t->rchild = newt;
				mSize++;
				break;
			}
			else {
				ELEMENT elem;
				elem.e = (unsigned long long)t;
				s.push((ELEMENT*)&elem);

				t = t->rchild;				
			}
		}
		else {
			if (t->lchild == 0)
			{
				BBST* newt = newnode(e);
				newt->parent = t;

				t->lchild = newt;
				mSize++;
				break;
			}
			else {
				ELEMENT elem;
				elem.e = (unsigned long long)t;
				s.push((ELEMENT*)&elem);

				t = t->lchild;		
			}
		}
	}

	while (s.isEmpty() == 0) {
		ELEMENT elem;
		s.pop(&elem);
		BBST* b = (BBST*)elem.e;
		if( b->lchild == t)
		{
			b->depth++;
			if (b->depth >= 2)
			{
				if (t->depth == 1)
				{
					
				}
				else if (t->depth == -1)
				{

				}
			}

			t = b->lchild;
		}
		else if (b->rchild == t)
		{
			b->depth--;
			if (b->depth <= -2)
			{
				if (t->depth == 1)
				{

				}else if (t->depth == -1)
				{

				}
			}
			t = b->rchild;
		}
	}

	return 0;
}

int BBSTree::remove(ELEMENT* e) {

	BBST* t = search(e);
	if (t == 0)
	{
		return 0;
	}

	BBST* parent = t->parent;
	BBST* lchild = t->lchild;
	BBST* rchild = t->rchild;

	if (lchild == 0 && rchild == 0)
	{
		if (parent == 0 || t == mTree) {
			delete mTree;
			mTree = 0;
		}
		else if (parent->lchild == t)
		{
			parent->lchild = 0;
		}
		else if (parent->rchild == t)
		{
			parent->rchild = 0;
		}
		else {

		}
	}
	else if (lchild == 0)
	{
		if (parent == 0 || t == mTree) {
			delete mTree;
			mTree = rchild;
			rchild->parent = 0;
		}
		else if (parent->lchild == t)
		{
			parent->lchild = rchild;
		}
		else if (parent->rchild == t)
		{
			parent->rchild = rchild;
		}
		else {

		}
	}
	else if (rchild == 0)
	{
		if (parent == 0 || t == mTree) {
			delete mTree;
			mTree = lchild;
			lchild->parent = 0;
		}
		else if (parent->lchild == t)
		{
			parent->lchild = lchild;
		}
		else if (parent->rchild == t)
		{
			parent->rchild = lchild;
		}
		else {

		}
	}
	else {
		//left subtree upwards and move right subtree ,or right subtree upwards and move left subtree
		if (parent == 0 || t == mTree) {
			BBST* tmp = lchild;
			while (tmp->rchild)
			{
				tmp = tmp->rchild;
			}
			rchild->parent = tmp;
			tmp->rchild = rchild;
			lchild->parent = 0;
			delete mTree;
			mTree = lchild;
		}
		else if (parent->lchild == t)
		{
			parent->lchild = lchild;
			lchild->parent = parent;

			BBST* tmp = lchild;
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

			BBST* tmp = lchild;
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


BBST* BBSTree::search(ELEMENT* e) {

	BBST* t = mTree;

	while (1) {
		if (t == 0)
		{
			break;
		}
		if (e->e == t->data.e) {
			return t;
		}
		else if (e->e > t->data.e)
		{
			t = t->rchild;
		}
		else {
			t = t->lchild;
		}
	}

	return 0;
}

int BBSTree::LTR(BBST* t, List* list, Stack* s) {

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
	//e.data = t->data.data;
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

		t = (BBST*)e.e;

		list->insert(&e);
		cnt++;
		printf("get LTR element:%lld value:%lld\r\n", e.e, t->data.e);

		t = t->rchild;

		cnt += LTR(t, list, s);
	}

	return cnt;
}

int BBSTree::ltr(List* list) {
	int cnt = 0;
	BBST* t = mTree;
	if (t == 0)
	{
		return 0;
	}

	Stack s;


	cnt = LTR(t, list, &s);

	return cnt;
}

int BBSTree::rtr(List* list) {
	return 0;
}

int BBSTree::mtr(List* list) {
	return 0;
}