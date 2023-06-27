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
	Eratosthenes(n_, A_);//递归
	for (int i = 2; i <= n_; i++) {
		if (A_[i]) {//i为素数
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
		int count = 0;//用于统计素数个数
		for (int i = 2; i <= n; i++)
			if (A[i]) {//i为素数
				count++;
				cout << i << ",";
			}
		cout << endl << "Total: " << count << endl;
	}
	system("pause");//暂停界面
	return 0;
}