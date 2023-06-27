#include<iostream>
#include<vector>
#include<math.h>
using namespace std;
//求解m的最小原根g并基于最小原根构造指数表

bool isCoprime(int a, int b) {
	//辗转相除法求最大公因数，判断a,b是否互素
	a = a > 0 ? a : -a;//转为正数
	b = b > 0 ? b : -b;//转为正数
	if (a < b) {//令a为较大者，b为较小者
		int tmp = a;
		a = b;
		b = tmp;
	}
	while (a % b) {//余数不为0，继续循环
		int r = a % b;
		a = b;
		b = r;
	}
	return b == 1;
}

int phi(int m) {//求解\phi(m)
	int count = 0;//记录m的最小非负完全剩余系中与m互素的整数个数
	for (int i = 1; i <= m; i++) {
		if (isCoprime(m, i))
			count++;
	}
	return count;//phi(m)
}

void Eratosthenes(int n, bool*& A) {//Eratosthenes筛法
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

void PrimeFactor(int n, vector<int>& Q) {
	//n = phi(m)
	//先用Eratosthenes筛法求[2,n]内所有素数
	bool* A = nullptr;
	Eratosthenes(n, A);
	int a = n;
	for (int i = 2; i <= n; i++) {
		if (A[i]) {//i为素数
			int count = 0;//记录素因子指数
			while (a % i == 0) {
				count++;
				a /= i;
			}
			if (count) {//count非零
				Q.push_back(n / i);
			}
		}
	}
}

int FMM(int a, int n, int m) {//平方-乘算法，快速模幂运算
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

bool MinPrimitiveRoot(int m, int& g) {
	//求m的最小原根g
	if (m == 1)//m==1, 不存在原根
		return false;
	if (m == 2) {//m为2，单独处理
		g = 1;
		return true;
	}
	vector<int> Q;
	PrimeFactor(phi(m), Q);//求phi(m)的素因子
	int i = 1;
	for (; i <= m; i++) {
		if (isCoprime(m, i)) {//m,i互素
			int len = Q.size();
			int j = 0;
			for (; j < len; j++) {
				if (FMM(i, Q[j], m) == 1) {
					break;//失败
				}
			}
			if (j == len) {
				g = i;//最小原根
				return true;
			}
		}
	}
	return false;
}

void IndTable(int m) {
	int g;
	if (MinPrimitiveRoot(m, g)) {//原根存在
		int phi_m = phi(m);
		int length = m / 10 + 1;//行数
		int** A = new int* [length];//存储Ind_Table
		for (int i = 0; i < length; i++) {
			A[i] = new int[10];
			for (int j = 0; j < 10; j++)
				A[i][j] = -1;//默认值为-1
		}
		A[0][1] = 0;
		for (int i = 1; i < phi_m; i++) {
			int a = FMM(g, i, m);
			A[a / 10][a % 10] = i;
		}
		//输出指数表
		cout << "The Min Primitive Root of " << m << ": g = " << g << endl;
		cout << "The Ind_Table of " << m << " base on g = " << g << " is:\n";
		cout << "\t";
		for (int i = 0; i < 10; i++) {
			cout << "\t" << i;
		}
		cout << endl;
		for (int i = 0; i < length; i++) {
			cout << "\t" << i;
			for (int j = 0; j < 10; j++) {
				cout << "\t";
				if (A[i][j] != -1) {
					cout << A[i][j];
				}
				else {
					cout << "-";
				}
			}
			cout << endl;
		}
		//回收内存
		for (int i = 0; i < length; i++) {
			delete[]A[i];
		}
		delete[]A;
	}
	else {
		cout << m << "的原根不存在!\n";
	}
}



int main() {
	cout << "Please Input n (n>0): ";
	int m;
	cin >> m;
	IndTable(m);
	system("pause");
	return 0;
}