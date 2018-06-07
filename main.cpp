#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include "types.h"

using namespace std;

const string INCORRECT_SELECTION = "Неверная опция";

const TNum SINGLE_BEGIN = 1.;

const TNum SYSTEM_BEGIN_X1 = 1;
const TNum SYSTEM_BEGIN_X2 = 1;

/*
======
SINGLE
======
*/

TNum FuncSingle(TNum x) {
	return x*x*x + x*x - x - .5;
}
TNum FuncSingleDiff(TNum x) {
	return 3*x*x + 2*x - 1;
}

TNum FiSingle(TNum x) {
	return sqrt(-(x*x*x - x - 0.5));
}
TNum NewtonSingle(TNum x) {
	return x - FuncSingle(x) / FuncSingleDiff(x);
}

void SingleSolution(char method) {
	TNum xk = SINGLE_BEGIN;
	TNum xk1 = SINGLE_BEGIN;
	size_t cnt = 0;
	do {
		cnt++;
		xk = xk1;
		if (method == 0) {
			xk1 = FiSingle(xk);
		} else {
			xk1 = NewtonSingle(xk);
		}
	} while (!(abs(xk1 - xk) < EPS));
	cout << "X = " << xk1 << endl;
	cout << "Число итераций: " << cnt << endl;
}

/*
======
SYSTEM
======
*/

pair <TNum, TNum> FuncSystem(TNum x1, TNum x2) {
	return make_pair(
		x1 - cos(x2) - 1,
		x2 - log10(x1 + 1) - 1
	);
}
TNum FuncSystemFi1(TNum x2) {
	return cos(x2) + 1;
}
TNum FuncSystemFi2(TNum x1) {
	return log10(max(x1 + 1, EPS)) + 1;
}
pair <TNum, TNum> FiSystem(TNum x1, TNum x2) {
	return make_pair(
		FuncSystemFi1(x2),
		FuncSystemFi2(x1)
	);
}
pair <TNum, TNum> NewtonSystem(TNum x1, TNum x2) {
	TNum j[2][2];
	TNum jr[2][2];
	TNum jdet;
	pair <TNum, TNum> func_curr = FuncSystem(x1, x2);

	j[0][0] = (FuncSystem(x1 + EPS, x2).first - func_curr.first) / EPS;
	j[0][1] = (FuncSystem(x1, x2 + EPS).first - func_curr.first) / EPS;
	j[1][0] = (FuncSystem(x1 + EPS, x2).second - func_curr.second) / EPS;
	j[1][1] = (FuncSystem(x1, x2 + EPS).second - func_curr.second) / EPS;
	jdet = j[0][0] * j[1][1] - j[0][1] * j[1][0];
	jr[0][0] = j[1][1] / jdet;
	jr[0][1] = -j[0][1] / jdet;
	jr[1][0] = -j[1][0] / jdet;
	jr[1][1] = j[0][0] / jdet;

	return make_pair(
		x1 - jr[0][0] * func_curr.first - jr[0][1] * func_curr.second,
		x2 - jr[1][0] * func_curr.first - jr[1][1] * func_curr.second
	);
}
void SystemSolution(char method) {
	pair <TNum, TNum> xk = make_pair(SYSTEM_BEGIN_X1, SYSTEM_BEGIN_X2);
	pair <TNum, TNum> xk1 = make_pair(SYSTEM_BEGIN_X1, SYSTEM_BEGIN_X2);
	size_t cnt = 0;
	do {
		cnt++;
		xk = xk1;
		if (method == 0) {
			xk1 = FiSystem(xk.first, xk.second);
		} else {
			xk1 = NewtonSystem(xk.first, xk.second);
		}
	} while (!(max(abs(xk1.first - xk.first), abs(xk1.second - xk.second)) < EPS));
	cout << "X = (" << xk1.first << ", " << xk1.second << ")" << endl;
	cout << "Число итераций: " << cnt << endl;
}

/*
====
MAIN
====
*/

int main(void) {
	cout << "=================" << endl;
	cout << "Выберите задание:" << endl;
	cout << "1 - Решение уравнения методом простых итераций" << endl;
	cout << "2 - Решение уравнения методом Ньютона" << endl;
	cout << "3 - Решение системы уравнений методом простых итераций" << endl;
	cout << "4 - Решение системы уравнений методом Ньютона" << endl;
	cout << "=================" << endl;

	cout << "Ваш выбор: ";
	size_t selection = 0;
	cin >> selection;
	cout << "=================" << endl;

	switch (selection) {
		case 1:
			SingleSolution(0);
			break;
		case 2:
			SingleSolution(1);
			break;
		case 3:
			SystemSolution(0);
			break;
		case 4:
			SystemSolution(1);
			break;
		case '\0':
			break;
		default:
			cout << INCORRECT_SELECTION << endl;
			break;
	}
	return 0;
}
