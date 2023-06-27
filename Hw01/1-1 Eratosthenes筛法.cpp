#include<iostream>
#include<math.h>
using namespace std;

void Eratosthenes(int n, bool*& A) {
	//nΪ����Χ[2,n]��A����������
	A = new bool[n + 1]{ false };
	for (int i = 2; i <= n; i++)
		A[i] = true;//��ʼ��Ϊtrue
	if (n < 4)
		return;//�ݹ����
	int n_ = (int)(sqrt(1.0 * n));
	bool* A_ = nullptr;
	Eratosthenes(n_, A_);//�ݹ�
	for (int i = 2; i <= n_; i++) {
		if (A_[i]) {//iΪ����
			for (int j = 2; j <= n; j++) {
				if (j % i == 0 && j != i)
					A[j] = false;
			}
		}
	}
}

int main() {
	int n;
	cout << "Please Input the integer n (n>1):\n";
	cin >> n;
	if (n <= 1) {
		cout << "Wrong Input!\n";
	}
	else {
		bool* A = nullptr;
		Eratosthenes(n, A);
		int count = 0;//����ͳ����������
		for (int i = 2; i <= n; i++)
			if (A[i]) {//iΪ����
				count++;
				cout << i << ",";
			}
		cout << endl << "Total: " << count << endl;
	}
	system("pause");//��ͣ����
	return 0;
}