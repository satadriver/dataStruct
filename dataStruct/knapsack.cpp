#include "knapsack.h"

#include <stdio.h>

#include <string.h>
#include <assert.h>

#define MAX_ARRAY_SIZE 1024


unsigned int knapsack(unsigned int n, unsigned int*v, unsigned int*w, unsigned int capacity) {

	unsigned int val[MAX_ARRAY_SIZE] = { 0 };
	for (int i = 0; i < n; i++) {
		for (int j = capacity; j >= 0; j--) {
			int t = val[j - w[i]] + v[i];

			if (j >= w[i] && val[j] < t) {
				val[j] = t;
			}
		}
	}
	assert(capacity < MAX_ARRAY_SIZE);
	return val[capacity];
}


int knapsackTest() {
	unsigned int i, n, c, w[MAX_ARRAY_SIZE],v[MAX_ARRAY_SIZE];
	int ret = 0;
	
	printf("input the number[2-%d]:\r\n", MAX_ARRAY_SIZE);

	ret = scanf("%d", &n);

	printf("input the capacity[above 0]:\r\n");

	ret = scanf("%d", &c);

	for (int i = 0; i < n; i++) {
		printf("input weight(remain %d):\r\n",n - i);
		ret = scanf("%d", &w[i]);
	}

	
	for (int i = 0; i < n; i++) {
		printf("input value(remain %d):\r\n", n - i);
		ret = scanf("%d", &v[i]);
	}

	unsigned int result = knapsack(n, v, w, c);

	printf("knapsack:%u\r\n", result);

	return 0;
}