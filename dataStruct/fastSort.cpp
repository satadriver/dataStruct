


int partition(int data[], int low, int high) {
	int  pivot = data[low];
	while (low < high)
	{
		while (low < high && data[high] >= pivot) // 从右向左找第一个小于x的数
			high--;
		if (low < high)
			data[low++] = data[high];
		while (low < high && data[low] < pivot) // 从左向右找第一个大于等于x的数
			low++;
		if (low < high)
			data[high--] = data[low];
	}
	data[low] = pivot;
	return low;
}

void quickSort(int s[], int low, int high)
{
	if (low < high)
	{
		int pivot = partition(s, low, high);
		quickSort(s, low, pivot - 1);
		quickSort(s, pivot + 1, high);
	}
}


int fastSort(int data[], int left, int right) {
	if (right - left <= 1)
	{
		return 0;
	}

	int pos = left;

	int tmp = data[pos];

	int empty = pos;

	int low = left;
	int high = right;

	while (low < high)
	{
		while (low < high)
		{
			if (data[high] > tmp)
			{
				high--;
				if (high <= low)
				{

					break;
				}
			}
			else {
				data[empty] = data[high];

				empty = high;
				high--;

				break;
			}
		}

		while (low < high)
		{
			if (low == pos)
			{
				low++;
				if (high <= low)
				{

					break;
				}
			}

			if (data[low] < tmp)
			{
				low++;
				if (high <= low)
				{

					break;
				}
			}
			else {
				data[empty] = data[low];

				empty = low;
				low++;

				break;
			}
		}
	}

	data[empty] = tmp;

	fastSort(data, left, low - 1);
	fastSort(data, low + 1, right);

	return 0;
}