#include <stdio.h>
#include <windows.h>
#include "BinarySearch.h"
#include "primeNumber.h"
#include "composite.h"
#include "bubbleSort.h"
#include "insertSort.h"
#include <stdlib.h>
#include <string.h>
#include "mystring.h"
#include "kmp.h"
#include "recursion.h"
#include "fibonacciSearch.h"
#include "SelectionSort.h"
#include "fastSort.h"
#include "heapSort.h"
#include "binaryInsertSort.h"
#include "shellSort.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include "rsa.h"
#include "lzss.h"
#include "mylzss.h"
#include "random.h"

using namespace std;


#define MAX_ARRAY_SIZE 0x1000


#define TEST_TIMES  10


int main(int argc, char** argv)
{
	testrandom();

	test_lgzz();

	lzss_test();

	// 	ackerman(2, 1);
	// 
	// 	int ii = 3 % 8;
	// 	int jj = 4 % 8;
	// 	int kk = 8 % 3;
	// 	int nn = 8 % 4;
	// 	myInt64 iii = 2106;
	// 	DWORD res = pow_i(981, 937, 2537) % 2537;

	rsaInit(97, 43);
	const char* myteststr = "Hello!\r\n Hi! \r\nHow are you ?\r\n Fine,thank you, and you ? \r\nI am fine, too!\r\n";
	int teststrlen = lstrlenA(myteststr);
	char dst0[1024] = { 0 };
	rsa_encrypt((char*)myteststr, teststrlen + 1, dst0);
	char dst1[1024];
	rsa_decrypt((char*)dst0, teststrlen + 1, dst1);

	DWORD totol = 0;
	hanoi(1, 2, 3, 16, &totol);

	int ret = 0;

	int* testarray = new int[MAX_ARRAY_SIZE];

	int* arr = new int[MAX_ARRAY_SIZE];

	srand(0);

	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		testarray[i] = rand();
	}

	LARGE_INTEGER startli, endli;

	unsigned __int64 selectionSortTimes = 0;

	unsigned __int64 counter = 0;

	int elements_counter = MAX_ARRAY_SIZE;

	for (int i = 0; i < TEST_TIMES; i++)
	{
		memcpy(arr, testarray, MAX_ARRAY_SIZE * sizeof(int));

		QueryPerformanceCounter(&startli);

		selectionSort(arr, elements_counter);				//22747859

		QueryPerformanceCounter(&endli);

		counter = endli.QuadPart - startli.QuadPart;
		selectionSortTimes += counter;
	}
	selectionSortTimes = selectionSortTimes / TEST_TIMES;


	unsigned __int64 heapSortTimes = 0;
	for (int i = 0; i < TEST_TIMES; i++)
	{
		memcpy(arr, testarray, MAX_ARRAY_SIZE * sizeof(int));

		QueryPerformanceCounter(&startli);

		//heapSort(arr, elements_counter);				//279254

		heap_sort(arr, (int)elements_counter);

		QueryPerformanceCounter(&endli);

		counter = endli.QuadPart - startli.QuadPart;
		heapSortTimes += counter;
	}
	heapSortTimes = heapSortTimes / TEST_TIMES;


	// 	unsigned __int64 quickSortTimes = 0;
	// 	for (int i = 0; i < TEST_TIMES; i++)
	// 	{
	// 		QueryPerformanceCounter(&startli);
	// 		quickSort(arr, 0, elements_counter - 1);
	// 
	// 		QueryPerformanceCounter(&endli);
	// 		counter = endli.QuadPart - startli.QuadPart;
	// 		quickSortTimes += counter;
	// 	}
	// 	quickSortTimes = quickSortTimes / TEST_TIMES;


	unsigned __int64 fastSortTimes = 0;
	for (int i = 0; i < TEST_TIMES; i++)
	{
		memcpy(arr, testarray, MAX_ARRAY_SIZE * sizeof(int));

		QueryPerformanceCounter(&startli);

		ret = fastSort(arr, 0, elements_counter);			//62327

		QueryPerformanceCounter(&endli);

		counter = endli.QuadPart - startli.QuadPart;
		fastSortTimes += counter;
	}
	fastSortTimes = fastSortTimes / TEST_TIMES;


	unsigned __int64 insertSortTimes = 0;
	for (int i = 0; i < TEST_TIMES; i++)
	{
		memcpy(arr, testarray, MAX_ARRAY_SIZE * sizeof(int));

		QueryPerformanceCounter(&startli);

		insertSort(arr, elements_counter);				//37111301

		QueryPerformanceCounter(&endli);

		counter = endli.QuadPart - startli.QuadPart;
		insertSortTimes += counter;
	}
	insertSortTimes = insertSortTimes / TEST_TIMES;


	unsigned __int64 bubbleSortTimes = 0;
	for (int i = 0; i < TEST_TIMES; i++)
	{
		memcpy(arr, testarray, MAX_ARRAY_SIZE * sizeof(int));

		QueryPerformanceCounter(&startli);

		bubbleSort(arr, elements_counter);					//71178061

		QueryPerformanceCounter(&endli);

		counter = endli.QuadPart - startli.QuadPart;
		bubbleSortTimes += counter;
	}
	bubbleSortTimes = bubbleSortTimes / TEST_TIMES;


	//	unsigned __int64 fastSortTimes = 0;
	// 	for (int i = 0; i < TEST_TIMES; i++)
	// 	{
	// 		QueryPerformanceCounter(&endli);
	// 		binarySearch(arr, elements_counter, 15);
	// 		QueryPerformanceCounter(&startli);
	// 
	// 		counter = endli.QuadPart - startli.QuadPart;
	// 		selectionSortTimes += counter;
	// 	}
	// 	selectionSortTimes = selectionSortTimes / TEST_TIMES;


	unsigned __int64 binaryInsertSortTimes = 0;
	for (int i = 0; i < TEST_TIMES; i++)
	{
		memcpy(arr, testarray, MAX_ARRAY_SIZE * sizeof(int));

		QueryPerformanceCounter(&startli);

		binaryInsertSort(arr, elements_counter);				//12901049

		QueryPerformanceCounter(&endli);

		counter = endli.QuadPart - startli.QuadPart;
		binaryInsertSortTimes += counter;
	}
	binaryInsertSortTimes = binaryInsertSortTimes / TEST_TIMES;


	unsigned __int64 shellSortTimes = 0;
	int delta[] = { MAX_ARRAY_SIZE / 0x1000,MAX_ARRAY_SIZE / 64 ,1 };
	for (int i = 0; i < TEST_TIMES; i++)
	{
		memcpy(arr, testarray, MAX_ARRAY_SIZE * sizeof(int));

		QueryPerformanceCounter(&startli);

		shellSort(arr, elements_counter, delta, sizeof(delta) / sizeof(int));		//843180

		QueryPerformanceCounter(&endli);

		counter = endli.QuadPart - startli.QuadPart;
		shellSortTimes += counter;
	}
	shellSortTimes = shellSortTimes / TEST_TIMES;


	char szinfo[1024];
	wsprintfA(szinfo, " shellSort:%I64u\r\n binaryInsertSort:%I64u\r\n bubbleSort:%I64u\r\n "
		"insertSort:%I64u\r\n heapSort:%I64u\r\n fastSort:%I64u\r\n selectionSort:%I64u\r\n",
		shellSortTimes, binaryInsertSortTimes, bubbleSortTimes, insertSortTimes, heapSortTimes, fastSortTimes, selectionSortTimes);
	//printf(szinfo);
	cout << szinfo;
	// 	printf(" shellSort:%I64u\r\n binaryInsertSort:%I64u\r\n bubbleSort:%I64u\r\n "
	// 		"insertSort:%I64u\r\n heapSort:%I64u\r\n fastSort:%I64u\r\n selectionSort:%I64u\r\n",
	// 		shellSortTimes, binaryInsertSortTimes, bubbleSortTimes, insertSortTimes, heapSortTimes, fastSortTimes, selectionSortTimes);



	ret = getchar();

	return FALSE;

	//ret = factorial(7);

	//ret = fibonacci(7);

	//int fbarray[] = { 0, 16, 24, 35, 47, 59, 62, 73, 132 };
	//int key = 132;
	//int index = fibonacciSearch(fbarray, 9, key);

	//ret = ackerman(6, 7);

	testkmp();

	ret = KmpSearch("abcaabcbabcd", "bcd");

	ret = composite(100);

	ret = primeNumber(100);

	return 0;
}

