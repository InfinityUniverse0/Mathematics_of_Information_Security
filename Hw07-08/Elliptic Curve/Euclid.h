#pragma once
#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

// 扩展欧几里得算法求乘法逆元
int Euclid(int a, int b);

// 求正整数的非1的因子
void Factor(int m, vector<int>& A);

// 求a对p的Legendre符号
int Legendre(int a, int p);

// Eratosthenes筛法求n以内的所有素数
void Eratosthenes(int n, bool*& A);

// 算术基本定理：求n的素因子分解
void PrimeFactor(int n, vector<int>& F, vector<int>& C);