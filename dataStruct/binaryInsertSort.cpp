

#include <stdio.h>


void binaryInsertSort(int* data,int size) {
	for (int i = 1;i < size;i ++)
	{
		int tmp = data[i];
		int low = 0;
		int high = i - 1;
		while (low <= high) {
			int m = (low + high ) / 2;
			if (data[i] < data[m])
			{
				high = m - 1;
			}
			else {
				low = m + 1;
			}
		}

		for ( int j = i - 1;j >= high + 1; j --)
		{
			data[j + 1] = data[j];
			
		}
		data[high + 1] = tmp;
	}
}