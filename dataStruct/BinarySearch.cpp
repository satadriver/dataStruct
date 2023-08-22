

unsigned int binarySearch(int data[], int datasize, int v) {
	int result = -1;
	if (datasize <= 0)
	{
		return result;
	}

	int max = datasize - 1;
	int min = 0;

	int idx = 0;

	do
	{
		idx = (min + max) >> 1;
		if (idx < min || idx > max)
		{
			break;
		}

		int tmp = data[idx];
		if (v == tmp)
		{
			return idx;
		}
		else if (v > tmp)
		{
			min = idx + 1;
		}
		else if (v < tmp)
		{
			max = idx - 1;
		}
	} while (1);

	return idx;
}