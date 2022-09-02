
void shellInsert(int arr[],int arrsize, int dk) {
	for (int i = dk ;i <= arrsize - 1;i ++)
	{
		if (arr[i] < arr[i-dk])
		{
			int tmp = arr[i]; 
			int j = i - dk;
			for (;j >= 0 && tmp < arr[j];j -= dk)
			{
				arr[j + dk] = arr[j];

			}
			arr[j + dk] = tmp;
		}
	}
}


void shellSort(int arr[], int size, int delta[], int deltasize) {
	for (int i = 0;i < deltasize; i ++)
	{
		shellInsert(arr, size, delta[i]);
	}
}