#pragma once

#pragma pack(1)
struct node {
	int father;
	int height;
};
#pragma pack()

node g_uf_set[0x1000];

inline int uf_find(int x) {
	while (x != g_uf_set[x].father) {
		x = g_uf_set[x].father;
	}
	return x;
}


inline void uf_union(int x, int y) {
	if (x == y) {
		return;
	}
	if (g_uf_set[x].height > g_uf_set[y].height) {
		g_uf_set[y].father = x;
	}
	else {
		if (g_uf_set[x].height == g_uf_set[y].height) {
			g_uf_set[y].height++;
		}
		g_uf_set[x].father = y;
	}
}