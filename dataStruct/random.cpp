#include "random.h"
#include <stdio.h>
#include <windows.h>



DWORD g_init = 0;



DWORD initRandom(DWORD v) {
	g_init = v;
	return g_init;
}


//xn = xn- 1 * 7 ^5 % m
DWORD getRandom() {
	g_init = (g_init * 7 ^ 5) % 0xffffffff;
	return g_init;
}


DWORD testrandom() {
	initRandom(GetTickCount());
	for (int i = 0; i < 10000; i++)
	{
		printf("%u          %u\r\n", i, getRandom());
	}
	return 0;
}