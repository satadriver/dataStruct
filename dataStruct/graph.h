#pragma once




#include "Element.h"

#include "list.h"

#pragma pack(1)

typedef struct {

	int vertex;

	ELEMENT* element;
	
}GRAPH;

#pragma pack()

GRAPH* genGraph(int num,int n,int v);


class Graph {
public:
	Graph();
	~Graph();

	int BFT(GRAPH* graph, int num, List* list);

	int bft(GRAPH* g, int num, List* list);

	int DFT(GRAPH* g, int num, List* list);

	int dft(GRAPH* g, int num, List* list);
};

