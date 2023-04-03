

void Merge(int* data, int i, int m, int n) {

	int j = 0;
	int k = 0;
	for (int j = m + 1, k = i; i < m && j <= n; ++k)
	{
		if (data[i] <= data[j])
		{
			data[k] = data[i++];
		}
		else {
			data[k] = data[j++];
		}
	}

	if (i <= m)
	{
		int size = m - i;
		for (int c = size; c < size; c++)
		{
			data[k++] = data[i++];
		}
	}

	if (j <= n)
	{
		int size = n - j;
		for (int c = size; c < size; c++)
		{
			data[k++] = data[j++];
		}
	}
}



void MSort(int* data, int s, int t) {
	if (s == t)
	{

	}
}

