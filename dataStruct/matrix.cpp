

#include "matrix.h"


int transpose(int * mat1,int width,int height) {
	for (int i = 0;i < width; i ++)
	{
		//for (int j = 0;j < i;j ++)
		for (int j = i;j < height;j ++)
		{
			{
				int* p1 = mat1 +  j * width + i;
				int* p2 = mat1 + i * width + j;
				int tmp = *p1;
				*p1 = *p2;
				*p2 = tmp;
			}
		}
	}
	return 0;
}

int matmul(int* mat1, int width1, int height1, int* mat2, int width2, int height2, int* mat3) {

	int* m1 = mat1;
	int* m2 = mat2;
	int* m3 = mat3;

	int n = 0;
	for (int i = 0; i < height1; i++) {


		for (int m = 0; m < width2; m++) {
			int tmp = 0;

			int k = m;
			for (int j = i * width1; j < i * width1 + width1; j++) {

				tmp += m1[j] * m2[k];

				k += width2;
			}

			m3[n] = tmp;
			n++;
		}

	}
	return 0;
}


#include<iostream>
#define inf 0x7fffffff
using namespace std;
int a[256] = { 0 };//存储矩阵的行和列 
int m[256][256] = { 0 };//存储i到j的最少计算次数 
int s[256][256] = { 0 };//存储i到j的中转站k 
void m_print(int i, int j)
{
	if (i == j)
	{
		printf("M%d", i);
	}
	else
	{
		printf("(");
		m_print(i, s[i][j]);
		m_print(s[i][j] + 1, j);
		printf(")");
	}
}
int matrixMultiple()
{
	int n = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n + 1; i++)
	{
		scanf("%d", &a[i]);
	}
	for (int d = 2; d <= n; d++)//d个矩阵相乘 
	{
		for (int i = 1; i <= n - d + 1; i++)//斜着到第i个 
		{
			int j = i + d - 1;
			m[i][j] = inf;
			for (int k = i; k <= i + d - 2; k++)
			{
				int temp = m[i][k] + m[k + 1][j] + a[i] * a[k + 1] * a[j + 1];
				if (temp < m[i][j])
				{
					m[i][j] = temp;
					s[i][j] = k;
				}
			}
		}
	}
	printf("%d ", m[1][n]);
	m_print(1, n);
	return 0;
}
