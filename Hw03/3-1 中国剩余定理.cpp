#include<iostream>
#include<vector>
using namespace std;

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

int Euclid(int a, int b) {
	//��չŷ������㷨����aģb�ĳ˷���Ԫ
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
		//�˷���Ԫ����
		if (a > b) {//����a, b�Ĵ�С����
			//תΪ��С����ϵ��
			if (s[l] < 0)
				s[l] = b + s[l];
			if (t[l] < 0)
				t[l] = a + t[l];
			return s[l];
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
	return 0;//gcd(a, b) != 1, �˷���Ԫ������
}


bool CRT(int n, int* b, int* m) {
	//Chinese Remainder Theorem
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (!isCoprime(m[i], m[j]))
				return false;//ģ�������أ�������CRT����������������false
	//Now, all m[i] and m[j] (where i != j) is Coprime to each other
	int M = 1;//���� \sum m[i]
	for (int i = 0; i < n; i++)
		M *= m[i];
	int Ans = 0;//������
	for (int i = 0; i < n; i++) {
		Ans += (M / m[i]) * Euclid((M / m[i]), m[i]) * b[i];
		Ans %= M;
	}
	cout << "x �� " << Ans << " (mod " << M << ")\n";
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
		cout << "ģ���������������ص�������CRT������!\n";
	system("pause");//��ͣ����
	return 0;
}