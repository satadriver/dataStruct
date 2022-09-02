

int insertSort(int data[], int size) {
	if (size <= 1)
	{
		return 0;
	}

	for (int i = 0; i < size-1;i++)
	{
		if (data[i] > data[i+1] )
		{
			int tmp = data[i+1];
			data[i + 1] = data[i];
			data[i] = tmp;

			if (i >= 1)
			{
				for (int j = i; j > 0;j--)
				{
					if (data[j] < data[j-1])
					{
						int tmp2 = data[j];
						data[j] = data[j-1];
						data[j - 1] = tmp2;
					}
				}
			}
		}
	}

	return 0;
}