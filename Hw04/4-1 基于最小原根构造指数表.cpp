#include<iostream>
#include<vector>
#include<math.h>
using namespace std;
//���m����Сԭ��g��������Сԭ������ָ����

bool isCoprime(int a, int b) {
	//շת�����������������ж�a,b�Ƿ���
	a = a > 0 ? a : -a;//תΪ����
	b = b > 0 ? b : -b;//תΪ����
	if (a < b) {//��aΪ�ϴ��ߣ�bΪ��С��
		int tmp = a;
		a = b;
		b = tmp;
	}
	while (a % b) {//������Ϊ0������ѭ��
		int r = a % b;
		a = b;
		b = r;
	}
	return b == 1;
}

int phi(int m) {//���\phi(m)
	int count = 0;//��¼m����С�Ǹ���ȫʣ��ϵ����m���ص���������
	for (int i = 1; i <= m; i++) {
		if (isCoprime(m, i))
			count++;
	}
	return count;//phi(m)
}

void Eratosthenes(int n, bool*& A) {//Eratosthenesɸ��
	//nΪ����Χ[2,n]��A����������
	A = new bool[n + 1]{ false };
	for (int i = 2; i <= n; i++)
		A[i] = true;//��ʼ��Ϊtrue
	if (n < 4)
		return;//�ݹ����
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
	//����Eratosthenesɸ����[2,n]����������
	bool* A = nullptr;
	Eratosthenes(n, A);
	int a = n;
	for (int i = 2; i <= n; i++) {
		if (A[i]) {//iΪ����
			int count = 0;//��¼������ָ��
			while (a % i == 0) {
				count++;
				a /= i;
			}
			if (count) {//count����
				Q.push_back(n / i);
			}
		}
	}
}

int FMM(int a, int n, int m) {//ƽ��-���㷨������ģ������
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

bool MinPrimitiveRoot(int m, int& g) {
	//��m����Сԭ��g
	if (m == 1)//m==1, ������ԭ��
		return false;
	if (m == 2) {//mΪ2����������
		g = 1;
		return true;
	}
	vector<int> Q;
	PrimeFactor(phi(m), Q);//��phi(m)��������
	int i = 1;
	for (; i <= m; i++) {
		if (isCoprime(m, i)) {//m,i����
			int len = Q.size();
			int j = 0;
			for (; j < len; j++) {
				if (FMM(i, Q[j], m) == 1) {
					break;//ʧ��
				}
			}
			if (j == len) {
				g = i;//��Сԭ��
				return true;
			}
		}
	}
	return false;
}

void IndTable(int m) {
	int g;
	if (MinPrimitiveRoot(m, g)) {//ԭ������
		int phi_m = phi(m);
		int length = m / 10 + 1;//����
		int** A = new int* [length];//�洢Ind_Table
		for (int i = 0; i < length; i++) {
			A[i] = new int[10];
			for (int j = 0; j < 10; j++)
				A[i][j] = -1;//Ĭ��ֵΪ-1
		}
		A[0][1] = 0;
		for (int i = 1; i < phi_m; i++) {
			int a = FMM(g, i, m);
			A[a / 10][a % 10] = i;
		}
		//���ָ����
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
		//�����ڴ�
		for (int i = 0; i < length; i++) {
			delete[]A[i];
		}
		delete[]A;
	}
	else {
		cout << m << "��ԭ��������!\n";
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