#include<iostream>
using namespace std;

long long int gcd(long long int a, long long int b) {
	//շת��������������
	a = a > 0 ? a : -a;//תΪ����
	b = b > 0 ? b : -b;//תΪ����
	if (a < b) {//��aΪ�ϴ��ߣ�bΪ��С��
		long long int tmp = a;
		a = b;
		b = tmp;
	}
	while (a % b) {//������Ϊ0������ѭ��
		long long int r = a % b;
		a = b;
		b = r;
	}
	return b;
}

long long int lcm(long long int a, long long int b) {
	a = a > 0 ? a : -a;//תΪ����
	b = b > 0 ? b : -b;//תΪ����
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
	system("pause");//��ͣ����
	return 0;
}