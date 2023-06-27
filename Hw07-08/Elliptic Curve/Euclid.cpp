#include "Euclid.h"

int Euclid(int a, int b) {
	/*
	* 求a模b的乘法逆元（小者模大者的乘法逆元）
	* return: a^(-1) (mod b)
	*/
	vector<int> r;//余数序列
	r.push_back(a > b ? a : b);//a, b中的大者
	r.push_back(a < b ? a : b);//a, b中的小者
	vector<int> q;//商序列
	q.push_back(-1);//q[0]中的值无效
	vector<int> s;
	s.push_back(1);
	s.push_back(0);
	vector<int> t;
	t.push_back(0);
	t.push_back(1);

	int x = 0;//索引
	while (r[x] % r[x + 1]) {//余数非零，则循环
		r.push_back(r[x] % r[x + 1]);
		q.push_back(r[x] / r[x + 1]);
		s.push_back(s[x] - s[x + 1] * q[x + 1]);
		t.push_back(t[x] - t[x + 1] * q[x + 1]);
		x++;
	}

	int l = r.size() - 1;//序列的末尾元素下标
	if (r[l] == 1) {
		//可用扩展欧几里得算法求逆元(乘法逆元存在)
		if (a > b) {//根据a, b的大小讨论
			//转为最小正缩系中
			if (s[l] < 0)
				s[l] = b + s[l];
			if (t[l] < 0)
				t[l] = a + t[l];
			return t[l];
		}
		else {
			//转为最小正缩系中
			if (s[l] < 0)
				s[l] = a + s[l];
			if (t[l] < 0)
				t[l] = b + t[l];
			return t[l];
		}
	}
	return 0; // 实则不需要
}

void Factor(int m, vector<int>& A) {
	// m >= 1
	for (int i = 2; i <= m; i++) {
		if (m % i == 0) {
			A.push_back(i); // m的因子从小到大排列
		}
	}
}

int Legendre(int a, int p) {
	// a \in Z_p
	if (a == 0)
		return 0; // Legendre符号为0，表示倍数
	if (a == 1)
		return 1; // Legendre符号为1
	if (a == 2) {
		if ((p % 8 == 3) || ((p % 8) == 5))
			return -1;
		return 1;
	}
	
	vector<int> Factor;
	vector<int> Count;
	PrimeFactor(a, Factor, Count); // 素因子分解

	int Ans = 1; // 保存结果

	int len = Factor.size();
	for (int i = 0; i < len; i++) {
		Count[i] %= 2;
		if (Count[i]) { // 非零
			if (Factor[i] == 2) {
				// (2/p)单独处理
				if (p % 8 == 3 || p % 8 == 5)
					Ans *= -1;
			}
			else {
				// 利用二次互反律
				int t = ((p - 1) / 2) * ((Factor[i] - 1) / 2);
				if (t % 2)
					t = -1;
				else
					t = 1;
				t *= Legendre((p % Factor[i]), Factor[i]);
				Ans *= t;
			}
		}
	}
	return Ans;
}

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

void PrimeFactor(int n, vector<int>& F, vector<int>& C) {
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
				F.push_back(i);
				C.push_back(count);
			}
		}
	}
}