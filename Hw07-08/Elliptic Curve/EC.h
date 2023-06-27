#pragma once
#include<iostream>
#include<stack>
#include"Euclid.h"
using namespace std;

class EC {
	// 有限域F_p上的椭圆曲线E_p(a, b)
	int p;
	int a, b;
	bool isValid; // E_p(a, b)是椭圆曲线
	int ord; // #E
public:
	EC() :isValid(false) {};
	void help() const; // 帮助信息
	bool Init(int P, int A, int B); // 初始化
	void PrintEC() const; // 打印当前EC的信息
	bool onEC(int x, int y); // 判断P(x, y)是否在EC上
	int* P_plus_Q(int x, int y, int m, int n); //计算 P+Q
	int* mP(int x, int y, int m); // 计算 mP
	int OrdP(int x, int y); // 计算点P(x, y)的阶
	int OrdE(); // 计算EC的阶
	void allPoints(bool isPrint = true); // 计算EC上的所有点
	void getEC() const; // 获取当前EC参数
};