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
	Eratosthenes(n_, A_);
	for (int i = 2; i <= n_; i++) {
		if (A_[i]) {
			for (int j = 2; j <= n; j++) {
				if (j % i == 0 && j != i)
					A[j] = false;
			}
		}
	}
}

void PrimeFactor(int n) {
	if (n == 1) {
		cout << n << "=2^0\n";
		return;
	}
	//����Eratosthenesɸ����[2,n]����������
	bool* A = nullptr;
	Eratosthenes(n, A);
	int a = n;
	cout << n << "=";
	bool tag = true;//����*�����
	for (int i = 2; i <= n; i++) {
		if (A[i]) {//iΪ����
			int count = 0;//��¼������ָ��
			while (a % i == 0) {
				count++;
				a /= i;
			}
			if (count) {//count����
				if (tag) {//��һ�������ǰ�治��Ҫ���*
					cout << i << "^" << count;
					tag = false;
				}
				else {//�ǵ�һ�������ǰ�������*
					cout << "*";
					cout << i << "^" << count;
				}
			}
		}
	}
}

int main() {
	cout << "Please Input n (n>0):\n";
	int n;
	cin >> n;
	if (n <= 0)
		cout << "Wrong Input!\n";
	else
		PrimeFactor(n);
	system("pause");//��ͣ����
	return 0;
}