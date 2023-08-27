
#include "MergeSort.h"
#include <string.h>


void MSort(int* data, int start, int end) {

	int size = end - start;
	if (size <= 1) {
		return;
	}

	if (size >= 2) {
		int m = (end + start) / 2;

		int h1 = m - start;
		int h2 = end - m;
		if (h1 >= 2) {
			MSort(data, start, m);
		}

		if (h2 >= 2) {
			MSort(data, m, end);
		}

		int* tmp = new int[size];
		memset(tmp, 0, sizeof(int*) * size);

		int i = start;
		int k = 0;
		int j = m;

		for (; i < m && j < end; k++) {			//why "i < m, j <end " is error?
			if (data[j] < data[i]) {
				tmp[k] = data[j];
				j++;
			}
			else {
				tmp[k] = data[i];
				i++;
			}
		}

		if (i != m) {
			for (int n = i; n < m; n++, k++) {
				tmp[k] = data[n];
			}
		}

		if (j != end) {
			for (int n = j; n < end; n++, k++) {
				tmp[k] = data[n];
			}
		}

		for (int l = start, k = 0; l < size; l++, k++) {
			data[l] = tmp[k];
		}

		delete[]tmp;
	}

	return;

}




int mergeSort(int* data, int size) {
	if (size <= 1) {
		return 0;
	}

	MSort(data, 0, size);

	return 0;
}
