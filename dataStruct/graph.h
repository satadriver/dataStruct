#pragma once




#include "Element.h"

#include "list.h"

#pragma pack(1)

typedef struct {

	ELEMENT* element;
	int vertex;
	int weight;

}GRAPH;

#pragma pack()


class Graph {
public:
	Graph();
	~Graph();

	GRAPH* genGraph(int num, int init);

	int BFT(GRAPH* graph, int num, List* list);

	int bft(GRAPH* g, int num, List* list);

	int DFT(GRAPH* g, int num, List* list);

	int dft(GRAPH* g, int num, List* list);
};

