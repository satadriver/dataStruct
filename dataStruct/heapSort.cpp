

#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
	int temp = *b;
	*b = *a;
	*a = temp;
}

void max_heapify(int arr[], int start, int end) {
	// ���������cָ�˺��ӹ��cָ��
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) { // ���ӹ��cָ���ڹ����Ȳ������^
		if (son + 1 <= end && arr[son] < arr[son + 1]) // �ȱ��^�ɂ��ӹ��c��С���x������
			son++;
		if (arr[dad] > arr[son]) //��������c����ӹ��c�����{���ꮅ��ֱ����������
			return;
		else { // ��t���Q���Ӄ������^�m�ӹ��c�͌O���c���^
			swap(&arr[dad], &arr[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

void heap_sort(int arr[], int len) {
	int i;
	// ��ʼ����i������һ�������c�_ʼ�{��
	for (i = len / 2 - 1; i >= 0; i--)
		max_heapify(arr, i, len - 1);
	// �Ȍ���һ��Ԫ�غ����ź�Ԫ��ǰһλ�����Q���������{����ֱ�������ꮅ
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
