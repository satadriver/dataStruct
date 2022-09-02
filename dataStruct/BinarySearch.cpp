

unsigned int binarySearch(int data[], int datasize, int v) {
	int result = -1;
	if (datasize <= 0)
	{
		return result;
	}

	int max = datasize - 1;
	int min = 0;
	if (v >= min && v <= max)
	{
	}
	else {
		return result;
	}

	int idx = datasize / 2;

	do
	{
		int tmp = data[idx];
		if (v == tmp)
		{
			return idx;
		}else if (v > tmp)
		{
			min = idx;
			idx = (idx + max) >>1;
			if (idx <= min)
			{
				break;
			}
		}else if (v < tmp)
		{
			max = idx;
			idx = (idx + min) >> 1;
			if (idx <= max)
			{
				break;
			}
		}
	} 
	while (1);

	return result;
}