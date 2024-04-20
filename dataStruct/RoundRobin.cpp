

#include<iostream>
#include<vector>
using namespace std;

void schedule(vector< vector<int> >& table, int n, int k) {

	for (int i = 1; i <= n; i++) {
		//初始化表格第一行 
		table[1][i] = i;
	}

	int m = 1;

	for (int s = 1; s <= k; s++) {

		n /= 2;

		for (int t = 1; t <= n; t++) {  //对每一部分进行划分（达到分治目的） 

			for (int i = 1 + m; i <= 2 * m; i++) { //控制行 

				for (int j = 1 + m; j <= 2 * m; j++) {   //控制列 

					table[i][j + (t - 1) * m * 2] = table[i - m][j + (t - 1) * m * 2 - m];  //右下角等左于上角的值 
					table[i][j + (t - 1) * m * 2 - m] = table[i - m][j + (t - 1) * m * 2];  //左下角等于右上角的值 
				}
			}
		}
		m *= 2;
	}
}

int input(int n, int k) {

	do {

		n = n / 2;
		k++;
	} while (n > 1);

	return k;
}

void display(vector< vector<int> >& table, int n) {

	cout << "比赛日程表：" << endl;
	for (int i = 1; i <= n; i++) {

		for (int j = 1; j <= n; j++) {

			cout << table[i][j] << " ";
			if (j == 1) cout << "| ";

		}
		cout << endl;
	}

}

int RoundRobin() {

	int k = 0;
	int n = 0;
	cout << "请输入要比赛的人数: ";
	cin >> n;
	vector< vector<int> > table(n + 1, vector<int>(n + 1)); //创建一个二维数组表示日程表 
	k = input(n, k);  //2的K次方 
	schedule(table, n, k);
	display(table, n);

	return 0;
}
