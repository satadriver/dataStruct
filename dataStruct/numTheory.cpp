
#include "numTheory.h"
#include <math.h>

unsigned long long getprime(unsigned long long n) {
	double t = ceil(sqrt(n));
	for (unsigned long long ll = 2; ll < n; ll++) {
		if (ll) {

		}
	}
	return 0;
}



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




int composite(int max) {
	if (max < 4)
	{
		return -1;
	}

	for (int i = max; i >= 4; i--)
	{
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
					return i;
				}
			}
			else {

			}
		}
	}

	return -1;
}