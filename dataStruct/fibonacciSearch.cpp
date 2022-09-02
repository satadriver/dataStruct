#include <stdio.h>
#include <windows.h>

#define FBARRAY_MAX_SIZE 16

int g_fbarray[FBARRAY_MAX_SIZE] = { 0 };

void fibonacci(int fbarray[] ) {
	fbarray[0] = 0;
	fbarray[1] = 1;
	for (int i = 2; i < FBARRAY_MAX_SIZE; ++i) {
		fbarray[i] = fbarray[i - 1] + fbarray[i - 2];
	}
}


int fibonacciSearch(int data[], int datalen, int v) {

	if (g_fbarray[1] == 0)
	{
		fibonacci(g_fbarray);
	}

	int k = 0;
	while (datalen > g_fbarray[k] - 1) {
		++k;
	}

	int *tmp = new int[g_fbarray[k] - 1];
	memcpy(tmp, data,sizeof(int)*datalen);
	for (int i = datalen; i < g_fbarray[k] - 1; ++i) {
		tmp[i] = data[datalen - 1];
	}
		

	int low = 0;
	int high = datalen - 1;
	while (low <= high) {
		int mid = low + g_fbarray[k - 1] - 1;
		if (v < tmp[mid]) {
			high = mid - 1;
			k -= 1;
		}
		else if (v > tmp[mid] ) {
			low = mid + 1;
			k -= 2;		//?why
		}
		else {
			if (mid < datalen)
				return mid;
			else
				return datalen - 1;
		}
	}

	return -1;
}
