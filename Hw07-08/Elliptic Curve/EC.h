#pragma once
#include<iostream>
#include<stack>
#include"Euclid.h"
using namespace std;

class EC {
	// ������F_p�ϵ���Բ����E_p(a, b)
	int p;
	int a, b;
	bool isValid; // E_p(a, b)����Բ����
	int ord; // #E
public:
	EC() :isValid(false) {};
	void help() const; // ������Ϣ
	bool Init(int P, int A, int B); // ��ʼ��
	void PrintEC() const; // ��ӡ��ǰEC����Ϣ
	bool onEC(int x, int y); // �ж�P(x, y)�Ƿ���EC��
	int* P_plus_Q(int x, int y, int m, int n); //���� P+Q
	int* mP(int x, int y, int m); // ���� mP
	int OrdP(int x, int y); // �����P(x, y)�Ľ�
	int OrdE(); // ����EC�Ľ�
	void allPoints(bool isPrint = true); // ����EC�ϵ����е�
	void getEC() const; // ��ȡ��ǰEC����
};