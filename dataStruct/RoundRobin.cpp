

#include<iostream>
#include<vector>
using namespace std;

void schedule(vector< vector<int> >& table, int n, int k) {

	for (int i = 1; i <= n; i++) {
		//��ʼ������һ�� 
		table[1][i] = i;
	}

	int m = 1;

	for (int s = 1; s <= k; s++) {

		n /= 2;

		for (int t = 1; t <= n; t++) {  //��ÿһ���ֽ��л��֣��ﵽ����Ŀ�ģ� 

			for (int i = 1 + m; i <= 2 * m; i++) { //������ 

				for (int j = 1 + m; j <= 2 * m; j++) {   //������ 

					table[i][j + (t - 1) * m * 2] = table[i - m][j + (t - 1) * m * 2 - m];  //���½ǵ������Ͻǵ�ֵ 
					table[i][j + (t - 1) * m * 2 - m] = table[i - m][j + (t - 1) * m * 2];  //���½ǵ������Ͻǵ�ֵ 
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

	cout << "�����ճ̱�" << endl;
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
	cout << "������Ҫ����������: ";
	cin >> n;
	vector< vector<int> > table(n + 1, vector<int>(n + 1)); //����һ����ά�����ʾ�ճ̱� 
	k = input(n, k);  //2��K�η� 
	schedule(table, n, k);
	display(table, n);

	return 0;
}
