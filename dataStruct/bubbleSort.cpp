

int bubbleSortInc(int data[], int size) {
	if (size <= 0)
	{
		return -1;
	}

	for (int i = 0; i <= size - 1; i++) {
		for (int j = 0; j < i; j++)
		{
			if (data[j] > data[j + 1])
			{
				int tmp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = tmp;
			}
		}
	}

	return 0;
}


int bubbleSortDec(int data[], int size) {
	if (size <= 0)
	{
		return -1;
	}

	for (int i = size - 1; i >= 0; i--) {
		for (int j = 0; j < i; j++)
		{
			if (data[j] > data[j + 1])
			{
				int tmp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = tmp;
			}
		}
	}

	return 0;
}