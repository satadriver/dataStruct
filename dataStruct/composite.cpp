
int composite(int max) {
	if (max < 4)
	{
		return -1;
	}

	for (int i = max;i >= 4;i--)
	{
		for (int j = 2; j < i; j ++)
		{
			int v = i / j;
			int m = i % j;
			if (m == 0 )
			{
				if (v == 1 || v == i)
				{

				}
				else {
					return i;
				}
			}
			else {
				
			}
		}
	}

	return -1;
}