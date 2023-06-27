#include<iostream>
#include<cstring>
#include"EC.h"
using namespace std;
// 有限域F_p上的椭圆曲线 E_P(a, b)

int main() {
	EC E;
	cout << "Elliptic Curve Calculator\n";

	int p, a, b;
	while (true) {
		cout << "Please input p, a, b for E_p(a, b):\n";
		cout << "p = ";
		cin >> p;
		cout << "a = ";
		cin >> a;
		cout << "b = ";
		cin >> b;

		if (E.Init(p, a, b)) {
			E.PrintEC();
			break;
		}
		else {
			E.PrintEC();
			cout << "Please input again!\n";
		}
	}

	// 帮助信息
	E.help();
	string s;

	cout << "Please input command:\n";
	cin >> s;
	while (s != "exit") {
		if (s == "help") {
			E.help();
		}
		if (s == "getEC") {
			E.getEC();
			cout << endl; // 换行
		}
		if (s == "onEC") {
			int x, y;
			cout << "x = ";
			cin >> x;
			cout << "y = ";
			cin >> y;
			if (E.onEC(x, y)) {
				cout << "P(" << x << ", " << y << ") is on ";
				E.getEC();
				cout << "!\n";
			}
			else {
				cout << "P(" << x << ", " << y << ") is NOT on ";
				E.getEC();
				cout << "!\n";
			}
		}
		if (s == "P+Q") {
			int x, y, m, n;
			cout << "x1 = ";
			cin >> x;
			cout << "y1 = ";
			cin >> y;
			cout << "x2 = ";
			cin >> m;
			cout << "y2 = ";
			cin >> n;

			if (!E.onEC(x, y) || !E.onEC(m, n)) {
				cout << "P或Q不是";
				E.getEC();
				cout << "上的点！\n";
			}
			else {
				int* R = E.P_plus_Q(x, y, m, n);
				if (R) {
					cout << "P + Q = ("
						<< x << ", " << y << ") + ("
						<< m << ", " << n << ")\n"
						<< " = ("
						<< R[0] << ", " << R[1] << ")\n";
					delete[]R;
				}
				else {
					cout << "P + Q = ("
						<< x << ", " << y << ") + ("
						<< m << ", " << n << ") = O (无穷远点)\n";
				}
			}
		}
		if (s == "mP") {
			int m, x, y;
			cout << "x = ";
			cin >> x;
			cout << "y = ";
			cin >> y;
			cout << "m = ";
			cin >> m;

			if (!E.onEC(x, y)) {
				cout << "P不是";
				E.getEC();
				cout << "上的点！\n";
			}
			else {
				int* R = E.mP(x, y, m);
				if (R) {
					cout << "mP = " << m << "("
						<< x << ", " << y << ")\n"
						<< " = ("
						<< R[0] << ", " << R[1] << ")\n";
					delete[]R;
				}
				else {
					cout << "mP = (" << m << "("
						<< x << ", " << y << ") = O (无穷远点)\n";
				}
			}
		}
		if (s == "OrdP") {
			int x, y;
			cout << "x = ";
			cin >> x;
			cout << "y = ";
			cin >> y;

			if (!E.onEC(x, y)) {
				cout << "P不是";
				E.getEC();
				cout << "上的点！\n";
			}
			else {
				cout << "ord(P) = " << E.OrdP(x, y) << endl;
			}
		}
		if (s == "OrdE") {
			cout << "#E = " << E.OrdE() << endl;
		}
		if (s == "allPoints") {
			cout << "All points on ";
			E.getEC();
			cout << ":\n";
			E.allPoints();
		}

		cout << "Please input command:\n";
		cin >> s;
	}

	system("pause"); // 暂停界面
	return 0;
}