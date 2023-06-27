#include "Euclid.h"

int Euclid(int a, int b) {
	/*
	* ��aģb�ĳ˷���Ԫ��С��ģ���ߵĳ˷���Ԫ��
	* return: a^(-1) (mod b)
	*/
	vector<int> r;//��������
	r.push_back(a > b ? a : b);//a, b�еĴ���
	r.push_back(a < b ? a : b);//a, b�е�С��
	vector<int> q;//������
	q.push_back(-1);//q[0]�е�ֵ��Ч
	vector<int> s;
	s.push_back(1);
	s.push_back(0);
	vector<int> t;
	t.push_back(0);
	t.push_back(1);

	int x = 0;//����
	while (r[x] % r[x + 1]) {//�������㣬��ѭ��
		r.push_back(r[x] % r[x + 1]);
		q.push_back(r[x] / r[x + 1]);
		s.push_back(s[x] - s[x + 1] * q[x + 1]);
		t.push_back(t[x] - t[x + 1] * q[x + 1]);
		x++;
	}

	int l = r.size() - 1;//���е�ĩβԪ���±�
	if (r[l] == 1) {
		//������չŷ������㷨����Ԫ(�˷���Ԫ����)
		if (a > b) {//����a, b�Ĵ�С����
			//תΪ��С����ϵ��
			if (s[l] < 0)
				s[l] = b + s[l];
			if (t[l] < 0)
				t[l] = a + t[l];
			return t[l];
		}
		else {
			//תΪ��С����ϵ��
			if (s[l] < 0)
				s[l] = a + s[l];
			if (t[l] < 0)
				t[l] = b + t[l];
			return t[l];
		}
	}
	return 0; // ʵ����Ҫ
}

void Factor(int m, vector<int>& A) {
	// m >= 1
	for (int i = 2; i <= m; i++) {
		if (m % i == 0) {
			A.push_back(i); // m�����Ӵ�С��������
		}
	}
}

int Legendre(int a, int p) {
	// a \in Z_p
	if (a == 0)
		return 0; // Legendre����Ϊ0����ʾ����
	if (a == 1)
		return 1; // Legendre����Ϊ1
	if (a == 2) {
		if ((p % 8 == 3) || ((p % 8) == 5))
			return -1;
		return 1;
	}
	
	vector<int> Factor;
	vector<int> Count;
	PrimeFactor(a, Factor, Count); // �����ӷֽ�

	int Ans = 1; // ������

	int len = Factor.size();
	for (int i = 0; i < len; i++) {
		Count[i] %= 2;
		if (Count[i]) { // ����
			if (Factor[i] == 2) {
				// (2/p)��������
				if (p % 8 == 3 || p % 8 == 5)
					Ans *= -1;
			}
			else {
				// ���ö��λ�����
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

void PrimeFactor(int n, vector<int>& F, vector<int>& C) {
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
				F.push_back(i);
				C.push_back(count);
			}
		}
	}
}