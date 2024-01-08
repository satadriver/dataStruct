
#include "graph.h"
#include <memory.h>
#include "floyd.h"


#define TEST_ARRAY_SIZE 10

void floydTest() {
	GRAPH* g = genGraph(TEST_ARRAY_SIZE, 1, -1);

	floyd(g);
}

int floyd(GRAPH * g) {
	
	int size = g->vertex;
	int array[TEST_ARRAY_SIZE][TEST_ARRAY_SIZE][TEST_ARRAY_SIZE];
	memset(array, 0, size * size*size);

	int dist[TEST_ARRAY_SIZE][TEST_ARRAY_SIZE];

	memset(dist, 0, size * size);

	for (int v = 0; v < size; v++) {
		for (int w = 0; w < size; w++) {
			int pos = v * size + w;
			//dist[v][w] = 0;
			int s = (int)(g->element[pos].e);
			dist[v][w] = (int)(g->element[pos].e);
			for (int u = 0; u < size; u++) {
				array[v][w][u] = 0;
			}
			if (dist[v][w] != -1) {
				array[v][w][v] = 1;
				array[v][w][w] = 1;
			}
		}
	}

	for (int u = 0; u < size; u++) {
		for (int v = 0; v < size; v++) {
			for (int w = 0; w < size; w++) {
				if (dist[v][u] + dist[u][w] < dist[v][w]) {
					dist[v][w] = dist[v][u] + dist[u][w];
					for (int i = 0; i < size; i++) {
						array[v][w][i] = array[v][u][i] || array[u][w][i];
					}
				}
			}
		}
	}
	return 0;
}