

#include "searchTree.h"


int g_x[0x1000];

int searchTree(int t) {

	int ret = 0;

	t = 0;

	g_x[t] = 0;

	searchTree(t + 1);

	g_x[t] = 1;

	ret = searchTree(t+ 1);

	return 0;
}