#include "EC.h"
#include<math.h>

void EC::help() const {
	cout << "This is Help Info:\n";
	cout << "- Input 'help' for Help Info.\n";
	cout << "- Input 'exit' to exit the program.\n";
	cout << "- Input 'getEC' to get the parameters of current E_p(a, b).\n";
	cout << "- Input 'onEC' to check if P(x, y) is on EC.\n";
	cout << "- Input 'P+Q' to calculate P + Q.\n";
	cout << "- Input 'mP' to calculate mP.\n";
	cout << "- Input 'OrdP' to calculate ord(P).\n";
	cout << "- Input 'OrdE' to calculate #E.\n";
	cout << "- Input 'allPoints' to calculate all points on EC.\n";
}

bool EC::Init(int P, int A, int B) {
	// ���P
	if (P <= 3) {
		isValid = false;
		// ��ӡ��Ϣ
		// PrintEC();
		return false;
	}
	isValid = true;
	for (int i = 2; i <= sqrt(1.0 * P); i++) {
		if (P % i == 0) {
			isValid = false;
			// ��ӡ��Ϣ
			// PrintEC();
			return false;
		}
	}

	// ��ֵ
	this->p = P;
	this->a = A % P; // �޶���Z_p
	this->b = B % P; // �޶���Z_p

	if (a < 0)
		a += p; // תΪ�Ǹ���
	if (b < 0)
		b += p; // תΪ�Ǹ���

	if ((4 * a * a * a + 27 * b * b) % p == 0) {
		isValid = false; // ���⻬
	}

	return isValid;
}

void EC::PrintEC() const {
	if (isValid) {
		/*
		cout << "p = " << p
			<< " a = " << a
			<< " b = " << b << endl;
		*/
		cout << "E_" << p << "(" << a << ", " << b << ") ����Բ���ߣ�\n";
	}
	else {
		// ��ǰ����EC
		cout << "��ǰ������Ч��������Բ���ߣ�\n";
	}
}

bool EC::onEC(int x, int y) {// �жϵ�ǰ��P(x, y)�Ƿ���EC��
	// �޶���Z_p
	x %= p;
	y %= p;
	if (x < 0)
		x += p;
	if (y < 0)
		y += p;

	// ����y^2
	int y2 = (x * x * x) % p;
	y2 = (y2 + a * x) % p;
	y2 = (y2 + b) % p;

	// ��֤
	int Y2 = (y * y) % p;
	if (y2 == Y2)
		return true;
	return false;
}

int* EC::P_plus_Q(int x, int y, int m, int n) {
	// ����P(x, y) + Q(m, n)
	// ������ֵΪ nullptr�����ʾ����Զ��O������ R(int[0], int[1])

	// �޶���Z_p
	x %= p;
	y %= p;
	if (x < 0)
		x += p;
	if (y < 0)
		y += p;
	m %= p;
	n %= p;
	if (m < 0)
		m += p;
	if (n < 0)
		n += p;

	int k; // б��

	if (x == m) {
		// ���������
		if (n == ((p - y) % p)) {
			return nullptr; // ���Ϊ����Զ��
		}
		// ����
		k = (3 * x * x) % p;
		k = (k + a) % p;
		int tmp = (2 * y) % p;
		tmp = Euclid(tmp, p);
		k = (k * tmp) % p;
	}
	else {
		// ���
		k = (n - y) % p;
		if (k < 0)
			k += p;
		
		int tmp = (m - x) % p;
		if (tmp < 0)
			tmp += p;
		// ����Ԫ
		tmp = Euclid(tmp, p);
		k = (k * tmp) % p;
	}

	int* R = new int[2]; // R = P + Q
	R[0] = (k * k) % p;
	R[0] = (R[0] - x - m) % p;
	if (R[0] < 0)
		R[0] += p;
	R[1] = (k * (x - R[0]) - y) % p;
	if (R[1] < 0)
		R[1] += p;

	return R;
}

int* EC::mP(int x, int y, int m) {
	/*
	* ���� mP
	* ����-���㷨
	* ������ֵΪ nullptr�����ʾ����Զ��O������ R(int[0], int[1])
	*/
	
	if (m == 0)
		return nullptr; // 0P = O

	bool isNeg = false; // �ж�m�Ƿ�Ϊ����
	if (m < 0) {
		isNeg = true;
		m = -m; // ��m��Ϊ����
	}

	// ��ȡm�Ķ�����
	stack<bool> S; // ����m�Ķ�����λ
	while (m) {
		S.push(m & 1); // ��λ������
		m >>= 1; // ������λ���㣬�ӿ������ٶ�
	}
	
	int len = S.size();
	S.pop();
	// ��ʼ��
	int* R = new int[2];
	R[0] = x;
	R[1] = y;
	
	// ����-���㷨
	int* tmp;
	while (!S.empty()) {
		tmp = R;
		if (R) { // ��ǰ�㲻Ϊ����Զ��
			R = P_plus_Q(R[0], R[1], R[0], R[1]);
			delete[]tmp;
		}
		// ��PΪ����Զ�㣬����֮����δ����Զ��
		if (S.top()) {
			tmp = R;
			if (R) { // ��ǰ�㲻Ϊ����Զ��
				R = P_plus_Q(R[0], R[1], x, y);
				delete[]tmp;
			}
			else { // ��ǰ��Ϊ����Զ��
				R[0] = x;
				R[1] = y;
			}
		}
		S.pop();
	}

	// ��mΪ����������|m|P����Բ���߼ӷ�Ⱥ�ļӷ���Ԫ
	if (isNeg)
		R[1] = (p - R[1]) % p;

	return R;
}

int EC::OrdP(int x, int y) {
	// �޶���Z_p
	x %= p;
	y %= p;
	if (x < 0)
		x += p;
	if (y < 0)
		y += p;

	// ��֪��ord(P) > 1

	// ��#E������
	int E = OrdE();
	vector<int> F;
	Factor(E, F);
	int len = F.size();

	int* R = nullptr;
	for (int i = 0; i < len; i++) {
		// ���Ӵ�С��������
		R = mP(x, y, F[i]);
		if (!R) {
			// RΪ����Զ��
			return F[i];
		}
		else {
			delete[]R;
		}
	}
}

int EC::OrdE() {
	allPoints(false); // ����this->ord
	return this->ord;
}

void EC::allPoints(bool isPrint) {
	this->ord = 1; // ��������Զ��O
	if (isPrint)
		cout << "O(����Զ��)\n";
	int y2;
	for (int x = 0; x < p; x++) { // ����Z_p
		// ����y^2
		y2 = (x * x * x) % p;
		y2 = (y2 + a * x) % p;
		y2 = (y2 + b) % p;

		// ����y2��p��Legendre����
		int L = Legendre(y2, p);
		if (L == -1)
			continue;
		if (L == 0) {
			// ����һ�� (x, 0)
			this->ord++;
			if (isPrint) {
				cout << "(" << x << ", 0)\n";
			}
			continue;
		}
		if (L == 1) {
			// ����2��
			this->ord += 2;
			if (isPrint) {
				// ����Z_p
				int y = 0;
				for (; y < p; y++) {
					if (((y * y) % p) == y2) {
						break; // �ҵ�һ���⣬������ֹ
					}
				}
				cout << "(" << x << ", " << y << ") ";
				cout << "(" << x << ", " << ((p - y) % p) << ")\n";
			}
		}
	}

	if (isPrint)
		cout << "Total: " << this->ord << endl;
}

void EC::getEC() const {
	// �޻���
	if (isValid)
		cout << "E_" << p << "(" << a << ", " << b << ")";
}