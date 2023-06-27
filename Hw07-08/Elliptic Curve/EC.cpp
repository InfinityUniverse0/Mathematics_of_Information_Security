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
	// 检查P
	if (P <= 3) {
		isValid = false;
		// 打印信息
		// PrintEC();
		return false;
	}
	isValid = true;
	for (int i = 2; i <= sqrt(1.0 * P); i++) {
		if (P % i == 0) {
			isValid = false;
			// 打印信息
			// PrintEC();
			return false;
		}
	}

	// 赋值
	this->p = P;
	this->a = A % P; // 限定于Z_p
	this->b = B % P; // 限定于Z_p

	if (a < 0)
		a += p; // 转为非负数
	if (b < 0)
		b += p; // 转为非负数

	if ((4 * a * a * a + 27 * b * b) % p == 0) {
		isValid = false; // 不光滑
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
		cout << "E_" << p << "(" << a << ", " << b << ") 是椭圆曲线！\n";
	}
	else {
		// 当前不是EC
		cout << "当前参数无效，不是椭圆曲线！\n";
	}
}

bool EC::onEC(int x, int y) {// 判断当前点P(x, y)是否在EC上
	// 限定于Z_p
	x %= p;
	y %= p;
	if (x < 0)
		x += p;
	if (y < 0)
		y += p;

	// 计算y^2
	int y2 = (x * x * x) % p;
	y2 = (y2 + a * x) % p;
	y2 = (y2 + b) % p;

	// 验证
	int Y2 = (y * y) % p;
	if (y2 == Y2)
		return true;
	return false;
}

int* EC::P_plus_Q(int x, int y, int m, int n) {
	// 计算P(x, y) + Q(m, n)
	// 若返回值为 nullptr，则表示无穷远点O；否则 R(int[0], int[1])

	// 限定于Z_p
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

	int k; // 斜率

	if (x == m) {
		// 横坐标相等
		if (n == ((p - y) % p)) {
			return nullptr; // 相加为无穷远点
		}
		// 倍加
		k = (3 * x * x) % p;
		k = (k + a) % p;
		int tmp = (2 * y) % p;
		tmp = Euclid(tmp, p);
		k = (k * tmp) % p;
	}
	else {
		// 点加
		k = (n - y) % p;
		if (k < 0)
			k += p;
		
		int tmp = (m - x) % p;
		if (tmp < 0)
			tmp += p;
		// 求逆元
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
	* 计算 mP
	* 倍加-和算法
	* 若返回值为 nullptr，则表示无穷远点O；否则 R(int[0], int[1])
	*/
	
	if (m == 0)
		return nullptr; // 0P = O

	bool isNeg = false; // 判断m是否为负数
	if (m < 0) {
		isNeg = true;
		m = -m; // 将m置为正数
	}

	// 提取m的二进制
	stack<bool> S; // 保存m的二进制位
	while (m) {
		S.push(m & 1); // 按位与运算
		m >>= 1; // 采用移位运算，加快运算速度
	}
	
	int len = S.size();
	S.pop();
	// 初始化
	int* R = new int[2];
	R[0] = x;
	R[1] = y;
	
	// 倍加-和算法
	int* tmp;
	while (!S.empty()) {
		tmp = R;
		if (R) { // 当前点不为无穷远点
			R = P_plus_Q(R[0], R[1], R[0], R[1]);
			delete[]tmp;
		}
		// 若P为无穷远点，倍加之后仍未无穷远点
		if (S.top()) {
			tmp = R;
			if (R) { // 当前点不为无穷远点
				R = P_plus_Q(R[0], R[1], x, y);
				delete[]tmp;
			}
			else { // 当前点为无穷远点
				R[0] = x;
				R[1] = y;
			}
		}
		S.pop();
	}

	// 若m为负数，则求|m|P的椭圆曲线加法群的加法逆元
	if (isNeg)
		R[1] = (p - R[1]) % p;

	return R;
}

int EC::OrdP(int x, int y) {
	// 限定于Z_p
	x %= p;
	y %= p;
	if (x < 0)
		x += p;
	if (y < 0)
		y += p;

	// 易知，ord(P) > 1

	// 求#E的因子
	int E = OrdE();
	vector<int> F;
	Factor(E, F);
	int len = F.size();

	int* R = nullptr;
	for (int i = 0; i < len; i++) {
		// 因子从小到大排列
		R = mP(x, y, F[i]);
		if (!R) {
			// R为无穷远点
			return F[i];
		}
		else {
			delete[]R;
		}
	}
}

int EC::OrdE() {
	allPoints(false); // 设置this->ord
	return this->ord;
}

void EC::allPoints(bool isPrint) {
	this->ord = 1; // 考虑无穷远点O
	if (isPrint)
		cout << "O(无穷远点)\n";
	int y2;
	for (int x = 0; x < p; x++) { // 遍历Z_p
		// 计算y^2
		y2 = (x * x * x) % p;
		y2 = (y2 + a * x) % p;
		y2 = (y2 + b) % p;

		// 计算y2对p的Legendre符号
		int L = Legendre(y2, p);
		if (L == -1)
			continue;
		if (L == 0) {
			// 仅有一解 (x, 0)
			this->ord++;
			if (isPrint) {
				cout << "(" << x << ", 0)\n";
			}
			continue;
		}
		if (L == 1) {
			// 存在2解
			this->ord += 2;
			if (isPrint) {
				// 遍历Z_p
				int y = 0;
				for (; y < p; y++) {
					if (((y * y) % p) == y2) {
						break; // 找到一个解，即可终止
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
	// 无换行
	if (isValid)
		cout << "E_" << p << "(" << a << ", " << b << ")";
}