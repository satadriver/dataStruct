

#include <stdio.h>

int selectLeast(int data[], int datalen, int idx) {

	for (int i = idx + 1; i < datalen; i++)
	{
		if (data[idx] > data[i])
		{
			idx = i;
		}
	}
	return idx;
}

int selectionSort(int data[], int datalen) {

	for (int i = 0; i < datalen; i++)
	{
		int least = selectLeast(data, datalen, i);
		if (least != i) {
			int tmp = data[i];
			data[i] = data[least];
			data[least] = tmp;
		}
	}

	return 0;
}