// lab 6.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <clocale>

using namespace std;
double Newton(double, double);
double Check_value(double*, double, double);

double f(double x)
{
	return x * x + 5 * cos(x) - 3;
}

double df(double x)
{
	return 2 * x - 5 * sin(x);
}

int main()
{
	cout << "Condition: x^2+5*cos(x)-3\na = -4, b = 2" << endl;

	int counter = 0, choice = 1;
	double left, right, x, h, eps;

	while (choice == 1)
	{
		cout << "------------------------------------" << endl;
		cout << "Enter the left border: ";
		Check_value(&left, -32766., 32766.);
		cout << "-----------------------------------------------------------------------" << endl;
		cout << "Enter the right border (it must be greater than the left border value): ";
		Check_value(&right, left, 32766.);
		cout << "-----------------------------------------------------------------------" << endl;
		cout << "Enter step for function: ";
		Check_value(&h, 0, right - left);
		cout << "------------------------------------" << endl;
		cout << "Enter the calculation precision (eps <= h / 10): ";
		Check_value(&eps, 0, h / 10);
		cout << "------------------------------------" << endl;

		for (x = left; x <= right; x += h)
		{

			if (f(x) * f(x + h) < 0)
			{
				counter++;
				double y = Newton(x, eps);
				cout << "Root " << counter << " = " << y << endl;
				cout << "y = f(Root " << counter << ") = " << f(y) << endl << endl;
			}
		}

		if (counter == 0)
			cout << "There are no roots in this interval" << endl;

		counter = 0;
		cout << "Press 1 to re-enter, any other key to exit:";
		cin >> choice;
		cout << "--------------------------------------------------------------------" << endl;

	}
	cout << "Exited successfully" << endl;
	return 0;
}

double Newton(double x0, double eps) {

	double xn = x0, counter = 0;
	do {
		x0 = xn;
		xn = x0 - f(x0) / df(x0);
		counter++;
	} while (fabs(x0 - xn) > eps);

	cout << "Root founded by " << counter << " iterations" << endl;
	return xn;
}

double Check_value(double* value, double min, double max)
{

	int counter = 0;
	while (true)
	{
		cin >> *value;

		if ((*value < min) || (*value > max) || cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Incorrect input, please try again\n";
			counter++;

			if (counter == 3)
			{
				cout << "Dear user, CAREFULLY CHECK THE CORRECT INPUT, please!\n";;
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