
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
算法思路：1将 n-1个盘子先放到B座位上
2.将A座上地剩下的一个盘移动到C盘上
3、将n-1个盘从B座移动到C座上
*/
void move(char x, char y)
{
	printf("%c--->%c", x, y);
}

void hannuo(int n, char one, char two, char three)
{
	if (n == 1)
		move(one, three); //递归截止条件
	else
	{
		hannuo(n - 1, one, three, two);//将 n-1个盘子先放到B座位上
		move(one, three);//将A座上地剩下的一个盘移动到C盘上
		hannuo(n - 1, two, one, three);//将n-1个盘从B座移动到C座上

	}
}


