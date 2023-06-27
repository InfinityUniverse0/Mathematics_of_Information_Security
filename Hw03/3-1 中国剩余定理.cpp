#include<iostream>
#include<vector>
using namespace std;

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

int Euclid(int a, int b) {
	//扩展欧几里得算法，求a模b的乘法逆元
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
		//乘法逆元存在
		if (a > b) {//根据a, b的大小讨论
			//转为最小正缩系中
			if (s[l] < 0)
				s[l] = b + s[l];
			if (t[l] < 0)
				t[l] = a + t[l];
			return s[l];
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
	return 0;//gcd(a, b) != 1, 乘法逆元不存在
}


bool CRT(int n, int* b, int* m) {
	//Chinese Remainder Theorem
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (!isCoprime(m[i], m[j]))
				return false;//模数不互素，不符合CRT的适用条件，返回false
	//Now, all m[i] and m[j] (where i != j) is Coprime to each other
	int M = 1;//保存 \sum m[i]
	for (int i = 0; i < n; i++)
		M *= m[i];
	int Ans = 0;//保存结果
	for (int i = 0; i < n; i++) {
		Ans += (M / m[i]) * Euclid((M / m[i]), m[i]) * b[i];
		Ans %= M;
	}
	cout << "x ≡ " << Ans << " (mod " << M << ")\n";
	return true;
}

int main() {
	int n;
	cout << "n = ";
	cin >> n;
	int* b = new int[n];
	int* m = new int[n];
	for (int i = 0; i < n; i++) {
		cout << "  b_" << (i + 1) << " = ";
		cin >> b[i];
		cout << "  m_" << (i + 1) << " = ";
		cin >> m[i];
	}
	if (!CRT(n, b, m))
		cout << "模数不满足两两互素的条件，CRT不适用!\n";
	system("pause");//暂停窗口
	return 0;
}