
#include "rsa.h"
#include <windows.h>
#include <stdio.h>

myInt64 g_n = 0;

myInt64 g_d = 0;

myInt64 g_w = 0;

int g_blocksize = 0;

int g_blocksize_src = 1;

myInt64 pow_i_old(myInt64 a, myInt64 b, myInt64 p) {
	myInt64 res = 1;
	for (myInt64 i = 0; i < b; i++)
	{
		res = (res * a) % p;
		if (res == 0)			//caution here: avert to overlow 
		{
			break;
		}
	}

	return res;
}


myInt64 pow_i(myInt64 x, myInt64 n, myInt64 p)
{
	if (n == 0)
	{
		return 1;
	}
	myInt64 temp = pow_i((x * x) % p, n / 2, p); //µÝ¹é¼ÆËã£¨X*X£©^[N/2]
	if ((n & 1) != 0) //ÅÐ¶ÏnµÄÆæÅ¼ÐÔ
	{
		temp = (temp * x) % p;
	}
	return temp;
}


myInt64 pow_ii(myInt64 a, myInt64 b, myInt64 g_n) {
	myInt64 res = 1;
	for (myInt64 i = 0; i < b; i++)
	{
		res = (res * a) % g_n;
		if (res == 0)			//caution here: avert to overlow 
		{
			//break;
		}
	}

	return res;
}

int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int isMutualPrime(myInt64 n, myInt64 m) {
	return 1;
}

int isPrimeNumber(myInt64 n) {
	for (myInt64 i = 2; i < n; i++)
	{
		myInt64 quotient = n % i;
		if (quotient == 0)
		{
			return FALSE;
		}
	}

	return TRUE;
}



int rsaInit(myInt64 p, myInt64 q)
{
	if (p == q || p <= 2 || q <= 2 || isPrimeNumber(p) == 0 || isPrimeNumber(q) == 0)
	{
		return FALSE;
	}

	g_n = p * q;
	if (g_n < 128)
	{
		return FALSE;
	}

	myInt64 mi64 = 0x8000000000000000;
	int bh = 63;
	for (int i = 63; i >= 0; i--)
	{
		if (g_n & mi64)
		{
			bh = i;
			break;
		}
		mi64 = mi64 >> 1;
	}

	if (bh >= 32)
	{
		g_blocksize = 8;
	}
	else if (bh >= 16)
	{
		g_blocksize = 4;
	}
	else if (bh >= 8)
	{
		g_blocksize = 2;
	}
	else
	{
		g_blocksize = 1;
	}


	myInt64 fai_n = (p - 1) * (q - 1);

	myInt64 w = 2;
	myInt64 d = 2;
	for (w = 2; w < fai_n; w++)
	{
		int result = isPrimeNumber(w);
		if (result)
		{
			for (d = 2; d < fai_n; d++)
			{
				result = isPrimeNumber(w);
				if (result) {
					myInt64 m = w * d;
					if ((d != w) && (m % fai_n == 1))
					{
						g_d = d;
						g_w = w;
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

//g_w is used to encrypt and g_d used to decrypt,and g_w must be primer to fai(n)
int rsa_encrypt(char* data, int size, char* dst) {
	if (g_n == 0 || g_w == 0 || g_d == 0)
	{
		return FALSE;
	}
	int block_cnt = size / g_blocksize_src;
	int mod = size % g_blocksize_src;

	unsigned char* s = (unsigned char*)data;
	myInt64* d = (myInt64*)dst;
	for (int i = block_cnt; i > 0; i--)
	{
		myInt64 tmp = 0;
		if (g_blocksize == 8)
		{
			tmp = *s;
			tmp = (tmp & 0xffffffffffffffff);
			tmp = (pow_i_old(tmp, g_w, g_n));
			*d = tmp;
		}
		else if (g_blocksize == 4)
		{
			tmp = *s;
			tmp = tmp & 0xffffffff;
			tmp = (pow_i_old(tmp, g_w, g_n));
			*(DWORD*)d = *(DWORD*)&tmp;
		}
		else if (g_blocksize == 2)
		{
			tmp = *s;
			tmp = tmp & 0xffff;
			tmp = (pow_i_old(tmp, g_w, g_n));
			*(WORD*)d = *(WORD*)&tmp;
		}
		else if (g_blocksize == 1)
		{
			tmp = *(unsigned char*)s;
			tmp = (tmp & 0xff);
			tmp = (pow_i_old(tmp, g_w, g_n));
			*(unsigned char*)d = *(unsigned char*)&tmp;
		}

		s = (unsigned char*)((unsigned char*)s + g_blocksize_src);
		d = (myInt64*)((unsigned char*)d + g_blocksize);
	}

	if (mod)
	{
		myInt64 tmp = 0;
		memcpy(&tmp, s, mod);
		if (g_blocksize == 8)
		{
			tmp = tmp & 0xffffffffffffffff;
		}
		else if (g_blocksize == 4)
		{
			tmp = tmp & 0xffffffff;
		}
		else if (g_blocksize == 2)
		{
			tmp = tmp & 0xffff;
		}
		else if (g_blocksize == 1)
		{
			tmp = tmp & 0xff;
		}
		tmp = pow_i_old(tmp, g_w, g_n);
		memcpy(d, &tmp, mod);
	}
	return size;
}

int rsa_decrypt(char* data, int size, char* dst) {
	if (g_n == 0 || g_w == 0 || g_d == 0)
	{
		return FALSE;
	}
	int block_cnt = size / g_blocksize_src;
	int mod = size % g_blocksize_src;

	myInt64* s = (myInt64*)data;
	unsigned char* d = (unsigned char*)dst;
	for (int i = block_cnt; i > 0; i--)
	{
		myInt64 tmp = 0;
		if (g_blocksize == 8)
		{
			tmp = *s;
			tmp = (tmp & 0xffffffffffffffff);
			tmp = (pow_i_old(tmp, g_d, g_n));
			*d = (unsigned char)tmp;
		}
		else if (g_blocksize == 4)
		{
			tmp = *(DWORD*)s;
			tmp = tmp & 0xffffffff;
			tmp = (pow_i_old(tmp, g_d, g_n));
			*d = (unsigned char)tmp;
		}
		else if (g_blocksize == 2)
		{
			tmp = *(WORD*)s;
			tmp = tmp & 0xffff;
			tmp = (pow_i_old(tmp, g_d, g_n));
			*d = (unsigned char)tmp;
		}
		else if (g_blocksize == 1)
		{
			tmp = *(unsigned char*)s;
			tmp = (tmp & 0xff);
			tmp = (pow_i_old(tmp, g_d, g_n));
			*d = (unsigned char)tmp;
		}
		s = (myInt64*)((unsigned char*)s + g_blocksize);
		d = (unsigned char*)((unsigned char*)d + g_blocksize_src);
	}

	if (mod)
	{
		myInt64 tmp = 0;
		memcpy(&tmp, s, mod);
		if (g_blocksize == 8)
		{
			tmp = tmp & 0xffffffffffffffff;
		}
		else if (g_blocksize == 4)
		{
			tmp = tmp & 0xffffffff;
		}
		else if (g_blocksize == 2)
		{
			tmp = tmp & 0xffff;
		}
		else if (g_blocksize == 1)
		{
			tmp = tmp & 0xff;
		}
		tmp = pow_i_old(tmp, g_d, g_n);
		memcpy(d, &tmp, mod);
	}
	return size;
}