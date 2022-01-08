// lab 8.cpp : Написать и отладить программу вычисления интеграла 
// указанным методом двумя способами – по заданному
// количеству разбиений n и заданной точности ε
// a = –1, b = 4, metod Гаусса 3, znachenie 22.09, х^2+5*cos(x)


#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
double f(double);
double Gauss3(double, double, double);
double Check_value(double*, int, int);
void Input_value(int&);

int main()
{
	double h, I1, eps, size;
	size = 10000000;
	double* X = new double[size]; double* pog = new double[size];
	int i, index, a = 0, b = 0, n, choice, check = 0;
	setlocale(LC_ALL, "rus");
	cout << "Данная программа считает значение интеграла функции х^2+5*cos(x)\nна заданном интервале, с заданным шагом и прогрешностью.\n" << endl;

	while (check == 0)
	{
		cout << "Введите нижний предел интегрирования: (рекомнедовано: -1)\na=";
		Input_value(a);
		cout << "Введите верхний предел интегрирования: (рекомнедовано: 4)\nb=";
		Input_value(b);

		if (a > b)
		{
			cout << "Ошибка! Нижний предел интегрирования больше верхнего! Попробуйте снова!";
		}
		else
			check = 1;
	}

	cout << "Выберите способ расчета:\n1 - по количеству разбиений \nДругая клавиша - по заданной точности\n" << endl;
	Input_value(choice);

	if (choice != 1)
	{
		cout << "Рассчет по точности eps: (10^eps, например, при eps = -6, погрешность равна 10^-6 )\n";
		Check_value(&eps, -100, -1);
		eps = pow(10, eps);
		n = 2;
	}

	else
	{
		cout << "Введите количество разбиений: (например одно из следующих значений: 25; 50; 100)\n";
		Input_value(n);
		eps = 100.;
	}

	while (check == 1)
	{
		h = (b - a) * 1. / n * 1.;

		for (i = 1; i <= n + 1; i++)
		{
			X[i] = a + (i - 1) * h;
		}

		for (i = 1; i <= n + 1; i++)
		{
			if (fabs(Gauss3(a, b, n) - Gauss3(a, b, 2 * n)) > eps)
				n = 2 * n;
		}

		if (choice == 1)
			check = 0;
		else
		{
			for (index = 2; index < n + 1; index++)
				if (pog[index] > eps)
				{
					n = 2 * n;
					break;
				}
				else
					check = 0;
		}
	}

	I1 = Gauss3(a, b, n);
	cout << endl << fixed << setprecision(2) << "Значение интеграла = " << I1 << endl;
	cout << "Количество разбиений = " << n << endl;
	delete[] X; delete[] pog;
}

double f(double x)
{
	double t;
	t = x * x + 5 * cos(x);
	return(t);
}

double Gauss3(double a, double b, double n)
{
	double h, x0, s = 0;
	h = (b - a) / n;
	double math_koef = (h / 2) * 0.7745966692;
	for (x0 = a + h / 2; x0 < b; x0 += h)
	{
		s += 5. / 9. * f(x0 - math_koef) + 8. / 9. * f(x0) + 5. / 9. * f(x0 + math_koef);
	}
	return (h / 2) * s;
}

double Check_value(double* value, int min, int max)
{
	int counter = 0;
	while (true)
	{
		cin >> *value;
		if ((*value <= min) || (*value > max) || cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Неверный ввод попробуйте снова\n";

			counter++;
			if (counter == 3)
			{
				cout << "Дорогой пользователь, пожалуйста, вводите значения внимательней!\n";;
				counter = 0;
			}
		}
		else
		{
			cin.ignore(32767, '\n');
			return *value;
		}
	}
}

void Input_value(int& Inputing_value)
{
	cin >> Inputing_value;
	while (cin.get() != '\n')
	{
		cout << "Неверный ввод!" << endl;
		cout << "Введите значение заново: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> Inputing_value;
	}
}