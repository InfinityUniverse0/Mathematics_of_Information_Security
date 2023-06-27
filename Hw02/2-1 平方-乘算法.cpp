#include<iostream>
#include<math.h>
using namespace std;
//ƽ��-���㷨

int FMM(int a, int n, int m) {
	//return a^n(mod m)
	int N = int(log2(1.0 * n)) + 1;//��������nתΪ������ʱ��λ��
	bool* A = new bool[N];//����n�Ķ�����
	for (int i = N - 1; i >= 0; i--) {
		A[i] = bool(n % 2);//nתΪ������
		n /= 2;
	}
	int c = 1;//��ʼ��c
	for (int i = 0; i < N; i++) {//�Ӹ�λ��ʼ
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
	system("pause");//��ͣ����
	return 0;
}