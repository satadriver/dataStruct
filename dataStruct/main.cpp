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

using namespace std;


#define MAX_ARRAY_SIZE 0x1000


#define TEST_TIMES  10


int main(int argc, char** argv)
{
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

	int key = 132;

	//int index = fibonacciSearch(fbarray, 9, key);

	//ret = ackerman(6, 7);

	testkmp();

	hannuo(7, 'A', 'B', 'C');

	ret = KmpSearch("abcaabcbabcd", "bcd");

	ret = indexstr("hello how are you? find thank you,and you? i'm fine too", " how", 0);

	ret = composite(100);

	ret = primeNumber(10);

	return 0;
}

