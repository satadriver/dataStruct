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
#include <conio.h>



using namespace std;


#define MAX_ARRAY_SIZE 0x10000

#define TEST_TIMES 3

//#define TEST_RECCURSIVE

#define TEST_RSA


#define TEST_SEARCH

#define TEST_SORT

int main(int argc, char** argv)
{
	int ret = 0;

#ifdef TEST_SEARCH
	int fbarray[] = { 0, 16, 24, 35, 47, 59, 62, 73, 132,197,251,299,1044,2011,2033,2045,3011,4098,5000,5002 };
	int key = 132;
	int index = fibonacciSearch(fbarray, sizeof(fbarray) / sizeof(fbarray[0]), key);
	printf("find:%u result:%u\r\n", key, index);

	index = binarySearch(fbarray, sizeof(fbarray) / sizeof(fbarray[0]), key);
	printf("find:%u result:%u\r\n", key, index);
#endif


#ifdef TEST_RECCURSIVE

	int testnum = 16;

	unsigned __int64 count = 0;

	int level = 15;

	hanoi(1, 2, 3, level, (unsigned long*)&count);
	printf("hannoi level:%u, count:%lld\r\n", level, count);

	count = factorial(testnum);

	printf("factorial:%u result:%lld\r\n", testnum, count);

	count = fibonacci(testnum);

	printf("fibonacci:%u result:%lld\r\n", testnum, count);

	count = ackerman(3, 2);

	printf("ackerman:%u result:%lld\r\n", testnum, count);
#endif

	unsigned long testa = 0x12345678;
	unsigned long testb = 0xfedcba98;

	testa = testa ^ testb;
	testb = testa ^ testb;
	testa = testa ^ testb;
	printf("testa:%X,testb:%x\r\n", testa, testb);

	_getch();
	//testrandom();

	//test_lgzz();

	//lzss_test();

	int result = 0;
	char* s = "assaasssas";
	char* p = "ssas";
	result = KmpSearch(s, p);
	ret = KmpSearch("abcaabcbabcd", "bcd");



#ifdef TEST_RSA
	ret = composite(1000);

	ret = primeNumber(2000);

	rsaInit(997, 1999);
	const char* myteststr = "Hello!\r\n Hi! \r\nHow are you ?\r\n Fine,thank you, and you ? \r\nI am fine, too!\r\n";
	int teststrlen = lstrlenA(myteststr);
	char dst0[1024] = { 0 };
	rsa_encrypt((char*)myteststr, teststrlen + 1, dst0);
	char dst1[1024];
	rsa_decrypt((char*)dst0, teststrlen + 1, dst1);
#endif


#ifdef TEST_SORT
	srand(0);
	int* testarray = new int[MAX_ARRAY_SIZE];

	int* arr = new int[MAX_ARRAY_SIZE];

	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		testarray[i] = rand();
	}

	memcpy(arr, testarray, MAX_ARRAY_SIZE * sizeof(int));

	int delta[] = { MAX_ARRAY_SIZE / 0x1000,MAX_ARRAY_SIZE / 64 ,1 };
	//shellSort(arr, MAX_ARRAY_SIZE, delta, sizeof(delta) / sizeof(int));
	//selectionSort(arr, MAX_ARRAY_SIZE);
	//bubbleSortInc(arr, MAX_ARRAY_SIZE);
	//heapSort(arr, MAX_ARRAY_SIZE);

	LARGE_INTEGER startli, endli, freq;

	QueryPerformanceFrequency(&freq);

	int elements_counter = MAX_ARRAY_SIZE;

	double bubbleSortTimes = 0;
	for (int i = 0; i < TEST_TIMES; i++)
	{
		memcpy(arr, testarray, MAX_ARRAY_SIZE * sizeof(int));

		QueryPerformanceCounter(&startli);

		bubbleSortDec(arr, elements_counter);					//71178061

		QueryPerformanceCounter(&endli);

		bubbleSortTimes = endli.QuadPart - startli.QuadPart;

	}
	bubbleSortTimes = bubbleSortTimes / freq.QuadPart;

	double insertSortTimes = 0;
	for (int i = 0; i < TEST_TIMES; i++)
	{
		memcpy(arr, testarray, MAX_ARRAY_SIZE * sizeof(int));

		QueryPerformanceCounter(&startli);

		insertSort(arr, elements_counter);				//37111301

		QueryPerformanceCounter(&endli);

		insertSortTimes = endli.QuadPart - startli.QuadPart;

	}
	insertSortTimes = insertSortTimes / freq.QuadPart;


	double selectionSortTimes = 0;
	for (int i = 0; i < TEST_TIMES; i++)
	{
		memcpy(arr, testarray, MAX_ARRAY_SIZE * sizeof(int));

		QueryPerformanceCounter(&startli);

		selectionSort(arr, elements_counter);				//22747859

		QueryPerformanceCounter(&endli);

		selectionSortTimes = endli.QuadPart - startli.QuadPart;

	}
	selectionSortTimes = selectionSortTimes / freq.QuadPart;



	double binaryInsertSortTimes = 0;
	for (int i = 0; i < TEST_TIMES; i++)
	{
		memcpy(arr, testarray, MAX_ARRAY_SIZE * sizeof(int));

		QueryPerformanceCounter(&startli);

		binaryInsertSort(arr, elements_counter);				//12901049

		QueryPerformanceCounter(&endli);

		binaryInsertSortTimes = endli.QuadPart - startli.QuadPart;

	}
	binaryInsertSortTimes = binaryInsertSortTimes / freq.QuadPart;


	double shellSortTimes = 0;
	for (int i = 0; i < TEST_TIMES; i++)
	{
		memcpy(arr, testarray, MAX_ARRAY_SIZE * sizeof(int));

		QueryPerformanceCounter(&startli);

		shellSort(arr, elements_counter, delta, sizeof(delta) / sizeof(int));		//843180

		QueryPerformanceCounter(&endli);

		shellSortTimes = endli.QuadPart - startli.QuadPart;

	}
	shellSortTimes = shellSortTimes / freq.QuadPart;


	double fastSortTimes = 0;
	for (int i = 0; i < TEST_TIMES; i++)
	{
		memcpy(arr, testarray, MAX_ARRAY_SIZE * sizeof(int));

		QueryPerformanceCounter(&startli);

		ret = fastSort(arr, 0, elements_counter);			//62327

		QueryPerformanceCounter(&endli);

		fastSortTimes = endli.QuadPart - startli.QuadPart;

	}
	fastSortTimes = fastSortTimes / freq.QuadPart;






	double heapSortTimes = 0;
	for (int i = 0; i < TEST_TIMES; i++)
	{
		memcpy(arr, testarray, MAX_ARRAY_SIZE * sizeof(int));

		QueryPerformanceCounter(&startli);

		heapSort(arr, elements_counter);				//279254

		//heap_sort(arr, (int)elements_counter);

		QueryPerformanceCounter(&endli);

		heapSortTimes = endli.QuadPart - startli.QuadPart;
		heapSortTimes = heapSortTimes / freq.QuadPart;

	}


	char szinfo[1024];
	printf(" bubbleSort:%lf\r\n insertSort:%lf\r\n selectionSort:%lf\r\n shellSort:%lf\r\n binaryInsertSort:%lf\r\n heapSort:%lf\r\n fastSort:%lf\r\n ",
		bubbleSortTimes, insertSortTimes, selectionSortTimes, shellSortTimes, binaryInsertSortTimes, heapSortTimes, fastSortTimes);
	//printf(szinfo);
	//cout << szinfo;

	ret = getchar();

#endif

	return 0;
}

