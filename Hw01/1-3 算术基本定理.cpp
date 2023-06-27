#include<iostream>
#include<math.h>
using namespace std;

void Eratosthenes(int n, bool*& A) {
	//n为代求范围[2,n]，A保存整数表
	A = new bool[n + 1]{ false };
	for (int i = 2; i <= n; i++)
		A[i] = true;//初始化为true
	if (n < 4)
		return;//递归结束
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
	//先用Eratosthenes筛法求[2,n]内所有素数
	bool* A = nullptr;
	Eratosthenes(n, A);
	int a = n;
	cout << n << "=";
	bool tag = true;//控制*的输出
	for (int i = 2; i <= n; i++) {
		if (A[i]) {//i为素数
			int count = 0;//记录素因子指数
			while (a % i == 0) {
				count++;
				a /= i;
			}
			if (count) {//count非零
				if (tag) {//第一次输出，前面不需要输出*
					cout << i << "^" << count;
					tag = false;
				}
				else {//非第一次输出，前面需输出*
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
	system("pause");//暂停界面
	return 0;
}