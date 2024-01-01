
#include <stdio.h>

#include "dijkstra.h"

#include "graph.h"




int dijkstra(GRAPH * g) {

	int num = 0;

	unsigned __int64 * cost = new unsigned __int64[g->vertex];

	int * visit = new int[g->vertex];

	int* vertex = new int[g->vertex];

	int idx = 0;

	for (int i = 0; i < g->vertex; i++) {

		idx = num * g->vertex + i;

		cost[i] = g->element[idx].e;

		visit[i] = 0;
		vertex[i] = 0;
	}

	int pos = 1;

	visit[0] = 1;

	for (num = 0; num < g->vertex; num++) { //num start from 0,why not 1?

		int n = 0;		//must be in circle

		unsigned __int64 t = 0xffffffffffffffff;	//must be in circle

		for (int j = 0; j < g->vertex; j++)
		{
			if (visit[j] == 0) {
				if (cost[j] < t) {
					t = cost[j];
					n = j;
				}
			}
		}
	
		if (visit[n] == 0) {
			int srcpos = num * g->vertex + n;

			for (int k = 0; k < g->vertex; k++) {
				idx = n * g->vertex + k;

				if ( (idx != srcpos) && (g->element[idx].e) && (g->element[srcpos].e) ) {
					if (cost[k] > g->element[idx].e + g->element[srcpos].e) {
						cost[k] = g->element[idx].e + g->element[srcpos].e;
						vertex[k] = n;
					}
				}
			}
		}

		visit[n] = 1;
	}

	return 0;
}



void testDijkstra() {

	GRAPH* g = genGraph(5,1,-1);

	dijkstra(g);

	return;
}