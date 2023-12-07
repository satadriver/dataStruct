

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


int deep(BBST* b) {
	if (b == 0)
	{
		return 0;
	}

	int ld =  deep(b->lchild);
		
	int rd = deep(b->rchild) ;
	
	return ld > rd ? ld + 1 : rd + 1;
}


BBST* BBSTree::newnode(ELEMENT* e) {

	BBST* t = new BBST;
	t->data.e = e->e;
	t->parent = 0;
	t->lchild = 0;
	t->rchild = 0;
	t->ld = 0;
	t->rd = 0;

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

	BBST* tc = 0;
	Stack s;

	ELEMENT elem;

	while (1) {
		if (e->e == t->data.e) {
			return 0;
		}
		else if (e->e > t->data.e)
		{
			if (t->rchild == 0)
			{
				tc = newnode(e);
				tc->parent = t;
				t->rchild = tc;
				mSize++;
				break;
			}
			else {			
				elem.e = (unsigned long long)t;
				s.push((ELEMENT*)&elem);

				t = t->rchild;				
			}
		}
		else {
			if (t->lchild == 0)
			{
				tc = newnode(e);
				tc->parent = t;

				t->lchild = tc;
				mSize++;
				break;
			}
			else {
				elem.e = (unsigned long long)t;
				s.push((ELEMENT*)&elem);

				t = t->lchild;		
			}
		}
	}

	while (s.isEmpty() == 0) {

		s.pop(&elem);
		BBST* b = (BBST*)elem.e;
		b->ld = deep(b->lchild);
		b->rd = deep(b->rchild);

		t->ld = deep(t->lchild);
		t->rd = deep(t->rchild);

		int high_diff = b->ld - b->rd;
		int low_diff = t->ld - t->rd;
		if(high_diff == 2 && low_diff == 1)
		{
			BBST* f = (BBST*)b->parent;
			if (f&&f->lchild == b)
			{
				f->lchild = t;
			}
			else if (f&&f->rchild == b)
			{
				f->rchild = t;
			}
			t->parent = f;

			BBST* tr = t->rchild;
			t->rchild = b;
			b->parent = t;
		
			b->lchild = tr;
			if (tr)
			{
				tr->parent = b;
			}

			if (b == mTree)
			{
				mTree = t;
			}
		}
		else if (high_diff == 2 && low_diff == -1)
		{
			BBST* f = (BBST*)b->parent;
			if (f->lchild == b)
			{
				f->lchild = tc;
			}
			else if (f->rchild == b)
			{
				f->rchild = tc;
			}
			tc->parent = f;

			t->parent = tc;
			if (tc->lchild)
			{
				tc->lchild->parent = t;
			}
			
			t->rchild = tc->lchild;

			b->parent = tc;
			if (tc->rchild)
			{
				tc->rchild->parent = b;
			}
			
			b->lchild = tc->rchild;

			tc->rchild = b;
			tc->lchild = t;		

			if (b == mTree)
			{
				mTree = tc;
			}
		}
		else if (high_diff == -2 && low_diff == 1)
		{
			BBST* f = (BBST*)b->parent;
			if (f&&f->lchild == b)
			{
				f->lchild = tc;
			}
			else if (f&&f->rchild == b)
			{
				f->rchild = tc;
			}
			tc->parent = f;

			b->parent = tc;
			b->rchild = tc->lchild;
			if (tc->lchild)
			{
				tc->lchild->parent = b;
			}

			t->parent = tc;
			t->lchild = tc->rchild;
			if (tc->rchild)
			{
				tc->rchild->parent = t;
			}
			
			tc->rchild = t;
			tc->lchild = b;

			if (b == mTree)
			{
				mTree = tc;
			}
		}
		else if (high_diff == -2 && low_diff == -1)
		{
			BBST* f = (BBST*)b->parent;
			if (f && f->lchild == b)
			{
				f->lchild = t;
			}
			else if (f && f->rchild == b)
			{
				f->rchild = t;
			}
			t->parent = f;

			BBST* tl = t->lchild;
			t->lchild = b;
			b->parent = t;
		
			b->rchild = tl;
			if (tl)
			{
				tl->parent = b;
			}

			if (b == mTree)
			{
				mTree = t;
			}
		}
		tc = t;
		t = b;
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