#pragma once
#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

// ��չŷ������㷨��˷���Ԫ
int Euclid(int a, int b);

// ���������ķ�1������
void Factor(int m, vector<int>& A);

// ��a��p��Legendre����
int Legendre(int a, int p);

// Eratosthenesɸ����n���ڵ���������
void Eratosthenes(int n, bool*& A);

// ��������������n�������ӷֽ�
void PrimeFactor(int n, vector<int>& F, vector<int>& C);