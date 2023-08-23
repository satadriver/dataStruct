
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "queue.h"
#include "list.h"


Graph::Graph() {

}


Graph::~Graph() {

}

GRAPH* Graph::genGraph(int num, int init) {

	ELEMENT* element = new ELEMENT[num * num];
	memset(element, 0, num * num * sizeof(ELEMENT));
	GRAPH* g = new GRAPH;
	g->element = element;
	g->vertex = num;

	if (init)
	{
		srand(0);

		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {

				int t = rand() % 2;
				if (t)
				{
					int idx = i * num + j;
					g->element[idx].e = 1;
				}
			}
		}
	}
	return g;
}


int Graph::bft(GRAPH* g, int num, List* list) {
	int idx;

	Queue q;
	ELEMENT e;

	int ret = 0;

	for (int j = 0; j < g->vertex; j++)
	{
		idx = num * g->vertex + j;
		if (g->element[idx].e)
		{
			e.e = j;
			ret = list->insert(&e);
			if (ret)
			{

				q.enQueue(&e);
				printf("get bft element:%lld\r\n", e.e);
			}
		}
	}

	while (q.isEmpty() == 0)
	{

		q.deQueue(&e);
		bft(g, e.e, list);
		printf("get bft element:%lld\r\n", e.e);
	}

	return 0;
}


//breadth first traversal
int Graph::BFT(GRAPH* g, int num, List* list) {

	ELEMENT e;
	int ret = 0;

	for (int i = num; i < g->vertex; i++)
	{
		e.e = i;
		ret = list->insert(&e);

		bft(g, i, list);
	}

	for (int i = 0; i < num; i++)
	{
		e.e = i;
		ret = list->insert(&e);
		bft(g, i, list);
	}
	return 0;

}



int Graph::dft(GRAPH* g, int num, List* list) {

	ELEMENT e;

	int idx;

	int ret = 0;

	for (int j = 0; j < g->vertex; j++)
	{
		idx = num * g->vertex + j;
		if (g->element[idx].e)
		{
			e.e = j;
			ret = list->insert(&e);
			if (ret)
			{
				printf("get dft element:%d\r\n", j);
				dft(g, j, list);
			}
		}
	}

	return 0;
}


//Depth first traversal
int Graph::DFT(GRAPH* g, int num, List* list) {
	ELEMENT e;
	int ret = 0;

	for (int i = num; i < g->vertex; i++)
	{
		e.e = i;
		ret = list->insert(&e);
		dft(g, i, list);
	}

	for (int i = 0; i < num; i++)
	{
		e.e = i;
		ret = list->insert(&e);
		dft(g, i, list);
	}
	return 0;
}