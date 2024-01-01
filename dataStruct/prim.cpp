

#include "prim.h"

#include "graph.h"





int prim(GRAPH* g) {

	int num = 0;

	unsigned __int64* cost = new unsigned __int64[g->vertex];

	int* visit = new int[g->vertex];

	int* vertex = new int[g->vertex];

	int total = 0;

	int idx = 0;

	for (int i = 0,num = 0; i < g->vertex; i++) {

		idx = num * g->vertex + i;

		cost[i] = g->element[idx].e;

		visit[i] = 0;
		vertex[i] = 0;
	}

	visit[0] = 1;
	vertex[0] = 0;

	int pos = 1;

	for (num = pos; num < g->vertex; num++) {

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

		total += t;

		vertex[num-1] = n;
		
		for (int k = pos; k < g->vertex; k++) {
			//已经找到的顶点不再更新权值，比如k=0时不用更新权值
			if (visit[n] == 0) {
				idx = n * g->vertex + k;

				if (g->element[idx].e) {

					if (cost[k] > g->element[idx].e) {
						cost[k] = g->element[idx].e;
						vertex[ k] = n;
					}
				}
			}
		}

		visit[n] = 1;
	}

	return 0;
}



void testPrim() {

	GRAPH* g = genGraph(4, 1,-1);

	prim(g);

	return;
}