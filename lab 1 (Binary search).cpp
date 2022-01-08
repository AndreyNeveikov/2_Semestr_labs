// lab1.cpp : 2. В упорядоченном массиве целых чисел ai (i = 1, ..., n) найти номер находящегося в массиве элемента c, используя метод двоичного поиска.


#include <conio.h>
#include <iostream>
#include <locale.h>
#include <stdio.h>
#include <iomanip>

using namespace std;

int* Create_1d_array(int&);		//Create one-dimensional array
void Input_value(int&); 	//Input value with protection against incorrect input
void Output_array(int*, int);		//Output one-dimensional array
int* Ascending_sorting(int*, int);		//Sort numbers ascending (по возрастанию)
int Search_binary(int*, int, int, int); //Search element in array binary

int main()
{
	//setlocale(LC_ALL, "rus");

	int array_size;
	int* _1d_array = Create_1d_array(array_size);

	cout << "Input elements: " << endl;
	for (int element_index = 0; element_index < array_size; element_index++)
	{
		Input_value(_1d_array[element_index]);
	}


	cout << "Initial array: " << endl;
	_1d_array = Ascending_sorting(_1d_array, array_size);


	Output_array(_1d_array, array_size);

	int key_number;
	cout << "Input number: " << endl;
	Input_value(key_number);

	int result = Search_binary(_1d_array, key_number, 0, array_size);

	if (result < 0)
		cout << "There is no " << key_number << " in the array!" << endl;
	else
		cout << "Index of element is: " << result << endl;

	delete[]_1d_array;
	system("pause");
	return 0;

}


int Search_binary(int* _1d_array, int key_number, int low, int high)
{
	if (high < low)
		return -1;
	int mid = low + ((high - low) / 2);
	if (_1d_array[mid] > key_number)
		return Search_binary(_1d_array, key_number, low, mid - 1);
	else if (_1d_array[mid] < key_number)
		return Search_binary(_1d_array, key_number, mid + 1, high);
	else
		return mid + 1;
}

int* Ascending_sorting(int* _1d_array, int array_size)
{
	for (int element_index = 0; element_index < array_size - 1; element_index++)
		for (int add_element_index = element_index + 1; add_element_index < array_size; add_element_index++)
			if (_1d_array[element_index] > _1d_array[add_element_index])
			{
				int tmp = _1d_array[element_index];
				_1d_array[element_index] = _1d_array[add_element_index];
				_1d_array[add_element_index] = tmp;
			}
	return _1d_array;
}

int* Create_1d_array(int& array_size)
{
	cout << "Input array size: ";
	Input_value(array_size);
	int* _1d_array = new int[array_size];
	return _1d_array;
}

void Output_array(int* _1d_array, int array_size)
{
	for (int element_index = 0; element_index < array_size; element_index++)
		cout << _1d_array[element_index] << " ";
	cout << endl;
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
