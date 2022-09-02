

int primeNumber(int max) {
	if (max < 2)
	{
		return -1;
	}


	for (int i = max; i >= 2; i--)
	{
		int isprime = 1;

		for (int j = 2; j < i; j++)
		{
			int v = i / j;
			int m = i % j;
			if (m == 0)
			{
				if (v == 1 || v == i)
				{

				}
				else {
					isprime = 0;
					break;
				}
			}
			else {

			}
		}

		if (isprime )
		{
			return i;
		}
	}

	return -1;
}