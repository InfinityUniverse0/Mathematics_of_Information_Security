#include<iostream>
#include<vector>
using namespace std;
//扩展欧几里得算法

void Euclid(int a, int b) {
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
	cout << "gcd(a, b) = " << r[l] << endl;
	cout << "lcm(a, b) = " << (a * b) / r[l] << endl;
	if (r[l] == 1) {
		//可用扩展欧几里得算法求逆元(乘法逆元存在)
		if (a > b) {//根据a, b的大小讨论
			//转为最小正缩系中
			if (s[l] < 0)
				s[l] = b + s[l];
			if (t[l] < 0)
				t[l] = a + t[l];
			cout << "a^(-1) = " << s[l] << " (mod " << b << ")\n";
			cout << "b^(-1) = " << t[l] << " (mod " << a << ")\n";
		}
		else {
			//转为最小正缩系中
			if (s[l] < 0)
				s[l] = a + s[l];
			if (t[l] < 0)
				t[l] = b + t[l];
			cout << "a^(-1) = " << t[l] << " (mod " << b << ")\n";
			cout << "b^(-1) = " << s[l] << " (mod " << a << ")\n";
		}
	}
	else {
		cout << "gcd(a, b) != 1\n";
		cout << "无法通过扩展欧几里得算法求逆元! (即: 乘法逆元不存在)\n";
	}
}

int main() {
	cout << "Note: the two integers you input must be positive!\n";
	int a, b;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	Euclid(a, b);
	system("pause");//暂停界面
	return 0;
}