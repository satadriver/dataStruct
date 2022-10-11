

#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
	int temp = *b;
	*b = *a;
	*a = temp;
}

void max_heapify(int arr[], int start, int end) {
	// 建立父節點指標和子節點指標
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) { // 若子節點指標在範圍內才做比較
		if (son + 1 <= end && arr[son] < arr[son + 1]) // 先比較兩個子節點大小，選擇最大的
			son++;
		if (arr[dad] > arr[son]) //如果父節點大於子節點代表調整完畢，直接跳出函數
			return;
		else { // 否則交換父子內容再繼續子節點和孫節點比較
			swap(&arr[dad], &arr[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

void heap_sort(int arr[], int len) {
	int i;
	// 初始化，i從最後一個父節點開始調整
	for (i = len / 2 - 1; i >= 0; i--)
		max_heapify(arr, i, len - 1);
	// 先將第一個元素和已排好元素前一位做交換，再重新調整，直到排序完畢
	for (i = len - 1; i > 0; i--) {
		swap(&arr[0], &arr[i]);
		max_heapify(arr, 0, i - 1);
	}
}





void swap(int& i, int& k) {
	int tmp = k;
	k = i;
	i = tmp;
}


void heapAdjust(int arr[], int num, int arrsize) {
	int pos = num;
	for (int j = 2 * num + 1; j < arrsize; j = j * 2 + 1)
	{
		if (j < arrsize - 1 && arr[j] < arr[j + 1])
		{
			j++;
		}

		if (arr[pos] < arr[j])
		{
			break;
		}
		else {
			arr[num] = arr[j];
			num = j;
		}
	}
	arr[num] = arr[pos];
}


void heapSort2(int arr[], int arrsize) {
	for (int i = arrsize / 2 - 1; i >= 0; i--)		// n/2-1 is previous root dot
	{
		heapAdjust(arr, i, arrsize);
	}

	for (int i = arrsize - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);
		heapAdjust(arr, 0, i);
	}
}


void heapify(int arr[], int arrsize, int num) {
	int lowest = num;
	int lchild = 2 * num + 1;	//lchild
	int rchild = 2 * num + 2;	//rchild
	if (lchild < arrsize && arr[lchild] > arr[lowest])
	{
		lowest = lchild;
	}
	if (rchild < arrsize && arr[rchild]> arr[lowest])
	{
		lowest = rchild;
	}
	if (lowest != num)
	{
		swap(arr[num], arr[lowest]);
		heapify(arr, arrsize, lowest);
	}
}
//				0
//		1				2
//	3		4		5		6
//7	 8    9  10   11 12   13 14

void heapSort(int arr[], int arrsize) {
	for (int i = arrsize / 2 - 1; i >= 0; i--)		// n/2-1 is previous root dot
	{
		heapify(arr, arrsize, i);
	}

	for (int i = arrsize - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}
