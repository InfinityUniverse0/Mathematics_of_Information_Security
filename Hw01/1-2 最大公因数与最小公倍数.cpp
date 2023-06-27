#include<iostream>
using namespace std;

long long int gcd(long long int a, long long int b) {
	//辗转相除法求最大公因数
	a = a > 0 ? a : -a;//转为正数
	b = b > 0 ? b : -b;//转为正数
	if (a < b) {//令a为较大者，b为较小者
		long long int tmp = a;
		a = b;
		b = tmp;
	}
	while (a % b) {//余数不为0，继续循环
		long long int r = a % b;
		a = b;
		b = r;
	}
	return b;
}

long long int lcm(long long int a, long long int b) {
	a = a > 0 ? a : -a;//转为正数
	b = b > 0 ? b : -b;//转为正数
	return (a * b) / gcd(a, b);
}

int main() {
	long long int a, b;
	cout << "Please Input two non-zero integers:\n";
	cin >> a >> b;
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
	cout << "gcd(a,b)=" << gcd(a, b) << endl;
	cout << "lcm(a,b)=" << lcm(a, b) << endl;
	system("pause");//暂停界面
	return 0;
}