
#include <stdio.h>
#include <string.h>

int factorial(int n) {
	if (n <= 0)
	{
		return 0;
	}
	else if (n == 1)
	{
		return 1;
	}
	else {
		return n * factorial(n - 1);
	}
}


int fibonacci(unsigned int n) {
	if (n == 0)
	{
		
		return 0;

	}
	else if (n == 1)
	{
		
		return 1;
	}
	else {
		return fibonacci(n - 1) + fibonacci(n - 2);
	}
}


int ackerman(unsigned int m, unsigned int n) {
	if (m == 0)
	{
		printf("%d\r\n",n+1);
		return n + 1;
	}
	else if (n == 0)
	{
		
		int res = ackerman(m - 1, 1);
		printf("%d\r\n", res);
		return res;
	}
	else {
		int res= ackerman(m - 1, ackerman(m, n - 1));
		printf("%d\r\n", res);
		return res;
	}
}



/*
�㷨˼·��1�� n-1�������ȷŵ�B��λ��
2.��A���ϵ�ʣ�µ�һ�����ƶ���C����
3����n-1���̴�B���ƶ���C����
*/
void move(unsigned int x, unsigned int y, unsigned long* count)
{
	printf("%d--->%d\r\n", x, y);
	(*count)++;
}

void hannuo(int n, char one, char two, char three, unsigned long* count)
{
	if (n == 1)
		move(one, three, count); //�ݹ��ֹ����
	else
	{
		hannuo(n - 1, one, three, two, count);//�� n-1�������ȷŵ�B��λ��
		move(one, three, count);//��A���ϵ�ʣ�µ�һ�����ƶ���C����
		hannuo(n - 1, two, one, three, count);//��n-1���̴�B���ƶ���C����

	}


}



void hanoi(unsigned int a, unsigned int c, unsigned int b, int level, unsigned long* count) {
	if (level == 1)
	{
		move(a, c, count);
	}
	else {
		hanoi(a, b, c, level - 1, count);
		move(a, c, count);
		hanoi(b, c, a, level - 1, count);
	}

	
}


