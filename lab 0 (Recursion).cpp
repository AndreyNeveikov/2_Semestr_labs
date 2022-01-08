// lab1.cpp : Defines the entry point for the console application.
//

#include <conio.h>
#include <iostream>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <ctime>
#include <iomanip>

using namespace std;

int* Create_1d_array(int&);		//Create one-dimensional array
void Fill_in_1d_array_randomly(int*, int);		//Fill in one-dimensional array randomly
void Input_value(int&); 	//Input value with protection against incorrect input
void Output_array(int*, int);		//Output one-dimensional array
int Max1(int*, int);
int Max2_rec(int*, int);
int Check_value(int*, int, int);


int main()
{
	//setlocale(LC_ALL, "rus");
	srand(time(0));

	int array_size;
	int* _1d_array = Create_1d_array(array_size);
	Fill_in_1d_array_randomly(_1d_array, array_size);
	cout << "Initial array: " << endl;
	Output_array(_1d_array, array_size);
	int tmp = _1d_array[0];

	cout << "1. Max = " << Max1(_1d_array, array_size) << endl;
	cout << "2. Max = " << Max2_rec(_1d_array, array_size - 1) << endl;

	_1d_array[0] = tmp;

	delete[]_1d_array;
	system("pause");
	return 0;
}

int Max1(int* _1d_array, int array_size) //Обычная
{
	int max = _1d_array[0];
	for (int element_index = 1; element_index < array_size; element_index++)
		if (_1d_array[element_index] > max) max = _1d_array[element_index];
	return max;
}

int Max2_rec(int* _1d_array, int array_size) //Рекурентная
{
	/* Возвращает вызов самой себя, а потом через какое-то время, когда array_size будет меньше 1 и попадет в первый if выйдет окончательно из функции*/
	if (array_size < 1) return _1d_array[0];
	if (_1d_array[array_size] > _1d_array[0])
		_1d_array[0] = _1d_array[array_size];
	return Max2_rec(_1d_array, array_size - 1);
}

int Check_value(int* value, int min, int max)
{

	int counter = 0;
	while (true)
	{
		cin >> *value;

		if ((*value <= min) || (*value > max) || cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Incorrect input! Try again!\n";
			counter++;

			if (counter == 3)
			{
				cout << "Dear user, please enter the values ​​carefully!\n";;
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

int* Create_1d_array(int& array_size)
{
	cout << "Input array size: ";
	Check_value(&array_size, 1, 32000);
	int* _1d_array = new int[array_size];
	return _1d_array;
}

void Output_array(int* _1d_array, int array_size)
{
	for (int element_index = 0; element_index < array_size; element_index++)
		cout << _1d_array[element_index] << " ";
	cout << endl;
}


void Fill_in_1d_array_randomly(int* _1d_array, int array_size)
{
	int min_limit, max_limit;
	cout << "Enter a range of random numbers (min_limit, max_limit): " << endl;
	cout << "Min limit: " << endl;
	Input_value(min_limit);
	cout << "Max limit: " << endl;
	Input_value(max_limit);
	for (int element_index = 0; element_index < array_size; element_index++)
		_1d_array[element_index] = min_limit + (max_limit - min_limit) * rand() / 32767.;
}

void Input_value(int& Inputing_value)
{
	cin >> Inputing_value;
	while (cin.get() != '\n')
	{
		cout << "Incorrect input!" << endl;
		cout << "Input value again: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> Inputing_value;
	}
}
