
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
		return n*factorial(n - 1);
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
	if (m ==0)
	{
		return n + 1;
	}else if (n == 0)
	{
		return ackerman(m - 1, 1);
	}
	else {
		return ackerman(m - 1, ackerman(m,n-1));
	}
}



/*
�㷨˼·��1�� n-1�������ȷŵ�B��λ��
2.��A���ϵ�ʣ�µ�һ�����ƶ���C����
3����n-1���̴�B���ƶ���C����
*/
void move(char x, char y)
{
	printf("%c--->%c", x, y);
}

void hannuo(int n, char one, char two, char three)
{
	if (n == 1)
		move(one, three); //�ݹ��ֹ����
	else
	{
		hannuo(n - 1, one, three, two);//�� n-1�������ȷŵ�B��λ��
		move(one, three);//��A���ϵ�ʣ�µ�һ�����ƶ���C����
		hannuo(n - 1, two, one, three);//��n-1���̴�B���ƶ���C����

	}
}


