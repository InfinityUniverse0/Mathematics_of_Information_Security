#include<iostream>
#include<math.h>
using namespace std;
//平方-乘算法

int FMM(int a, int n, int m) {
	//return a^n(mod m)
	int N = int(log2(1.0 * n)) + 1;//用来计算n转为二进制时的位数
	bool* A = new bool[N];//保存n的二进制
	for (int i = N - 1; i >= 0; i--) {
		A[i] = bool(n % 2);//n转为二进制
		n /= 2;
	}
	int c = 1;//初始化c
	for (int i = 0; i < N; i++) {//从高位开始
		c *= c;
		c %= m;
		if (A[i])
			c = (c * a) % m;
	}
	return c;
}

int main() {
	int a, n, m;
	cout << "Calculate a^n(mod m):\n";
	cout << "Please Input:\n";
	cout << "  a = ";
	cin >> a;
	cout << "  n = ";
	cin >> n;
	cout << "  m = ";
	cin >> m;

	cout << a << "^" << n << "(mod " << m << ") = ";
	cout << FMM(a, n, m) << endl;
	system("pause");//暂停窗口
	return 0;
}