

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