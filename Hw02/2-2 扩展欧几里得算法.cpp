#include<iostream>
#include<vector>
using namespace std;
//��չŷ������㷨

void Euclid(int a, int b) {
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
	cout << "gcd(a, b) = " << r[l] << endl;
	cout << "lcm(a, b) = " << (a * b) / r[l] << endl;
	if (r[l] == 1) {
		//������չŷ������㷨����Ԫ(�˷���Ԫ����)
		if (a > b) {//����a, b�Ĵ�С����
			//תΪ��С����ϵ��
			if (s[l] < 0)
				s[l] = b + s[l];
			if (t[l] < 0)
				t[l] = a + t[l];
			cout << "a^(-1) = " << s[l] << " (mod " << b << ")\n";
			cout << "b^(-1) = " << t[l] << " (mod " << a << ")\n";
		}
		else {
			//תΪ��С����ϵ��
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
		cout << "�޷�ͨ����չŷ������㷨����Ԫ! (��: �˷���Ԫ������)\n";
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
	system("pause");//��ͣ����
	return 0;
}