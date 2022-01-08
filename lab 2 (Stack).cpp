//lab 2.cpp : Написать программу по созданию, добавлению, просмотру и решению приведенных далее задач
//(в рассмотренных примерах это действие отсутствует) для однонаправленного линейного списка типа Stack.
//Реализовать сортировку стека методами, рассмотренными в подразделе 3.1.
//Во всех заданиях создать список из положительных и отрицательных случайных целых чисел.
//Реализовать чтение в обе стороны
// 3. Удалить из списка все отрицательные числа.

//#include "stdafx.h"
#include <iostream>
#include <stack>
#include <conio.h>
#include <time.h>
#include <iomanip>

using namespace std;


struct Element
{
	int info;
	Element* pointer_next;
};

void Input_value(int&); 	//Input value with protection against incorrect input
void Delete_stack(Element**, int&);	   //Delete stack
void Output_stack(Element*);	//Output stack
void Sort_data(Element*);	//Sort elements in stack
void Pointer_sort(Element**);	//Sort elements in stack
void Persoonal_task(Element**, int&);  //Delete elements < 0
Element* push(Element*, int, int&);	  //Ad element to stack
Element* pop(Element**, int&);		//Delete element from stack




int main()
{
	//setlocale(LC_ALL, "rus");
	srand(time(0));
	int size = 0;
	Element* top = nullptr;
	int  initial_input;

	cout << "Please firstly create a stack: \n Press 0 to create random stack \n Press 1-9 to create custom stack" << endl;
	Input_value(initial_input);

	if (initial_input == 1)
	{
		Delete_stack(&top, size);
		cout << "How many elements you want to add in stack?" << endl;
		int amount, tmp_value;
		Input_value(amount);
		for (int element_index = 0; element_index < amount; element_index++)
		{
			cout << "Enter number № " << element_index << endl;
			Input_value(tmp_value);
			top = push(top, tmp_value, size);
		}
	}

	else
	{
		Delete_stack(&top, size);
		cout << "How many elements you want to add in stack?" << endl;
		int amount, min_limit, max_limit;
		Input_value(amount);
		cout << "Enter a range of random numbers (min_limit, max_limit): \n Minimal number: " << endl;
		Input_value(min_limit);
		cout << "\n Maximal number: " << endl;
		Input_value(max_limit);

		for (int element_index = 0; element_index < amount; element_index++)
		{
			top = push(top, min_limit + (max_limit - min_limit) * rand() / 32767., size);
		}
	}



	while (true)
	{
		cout << "Please select an operation: \n 1. Create new custom stack \n 2. Create new random stack \n 3. View stack \n 4. Sort data \n 5. Pointer sort \n 6. Personal task \n 7. Exit" << endl;
		switch (_getch())
		{
		case '1': //Сreate custom stack
		{
			Delete_stack(&top, size);
			cout << "How many elements you want to add in stack?" << endl;
			int amount, tmp_value;
			Input_value(amount);
			for (int element_index = 0; element_index < amount; element_index++)
			{
				cout << "Enter number № " << element_index << endl;
				Input_value(tmp_value);
				top = push(top, tmp_value, size);
			}
			break;
		}
		case '2': //Сreate random stack
		{
			Delete_stack(&top, size);
			cout << "How many elements you want to add in stack?" << endl;
			int amount, min_limit, max_limit;
			Input_value(amount);
			cout << "Enter a range of random numbers (min_limit, max_limit): \n Minimal number: " << endl;
			Input_value(min_limit);
			cout << "\n Maximal number: " << endl;
			Input_value(max_limit);

			for (int element_index = 0; element_index < amount; element_index++)
			{
				top = push(top, min_limit + (max_limit - min_limit) * rand() / 32767., size);
			}
			break;
		}
		case '3': //View stack
		{
			cout << endl;
			Output_stack(top);
			cout << "\n Stack size is: " << size << " elements. \n" << endl;
			break;
		}
		case '4': //Sort data
		{
			cout << endl;
			Sort_data(top);
			Output_stack(top);
			cout << endl;
			cout << endl;
			break;
		}
		case '5': //Pointer sort
		{
			cout << endl;
			top = push(top, 22, size);
			Pointer_sort(&top);
			top = pop(&top, size);
			Output_stack(top);
			cout << endl;
			cout << endl;
			break;
		}
		case '6': //Personal task
		{
			cout << endl;
			Persoonal_task(&top, size);
			cout << endl;
			break;
		}
		case '7': //Exit
		{
			Delete_stack(&top, size);
			exit(1);
			break;
		}
		default: //Restart
		{
			cout << "Please select an operation from 1 to 7 \n" << endl;
			break;
		}
		}
	}


	system("pause");
	return 0;
}

void Persoonal_task(Element** top, int& size)
{
	*top = push(*top, 22, size);
	{
		for (Element* t = *top; !(t == nullptr || t->pointer_next == nullptr); t = t->pointer_next)
		{
			while (!(t->pointer_next->info >= 0 || t->pointer_next->pointer_next == nullptr))
			{
				Element* t1 = t->pointer_next;
				t->pointer_next = t->pointer_next->pointer_next;
				delete t1;
				size--;
			}
			if (t->pointer_next->pointer_next == nullptr && t->pointer_next->info < 0)
			{
				delete t->pointer_next;
				t->pointer_next = nullptr;
				size--;
			}
		}
	}
	*top = pop(top, size);
	cout << "\nResult stack: " << endl;
	Output_stack(*top);
	cout << endl;
}

void Pointer_sort(Element** top)
{

	Element* t = nullptr, * t1, * r;
	if ((*top)->pointer_next->pointer_next == nullptr)
		return;
	do
	{
		for (t1 = *top; t1->pointer_next->pointer_next != t; t1 = t1->pointer_next)
			if (t1->pointer_next->info > t1->pointer_next->pointer_next->info)
			{
				r = t1->pointer_next->pointer_next;
				t1->pointer_next->pointer_next = r->pointer_next;
				r->pointer_next = t1->pointer_next;
				t1->pointer_next = r;
			}
		t = t1->pointer_next;
	} while ((*top)->pointer_next->pointer_next != t);
}

void Sort_data(Element* top)
{
	Element* flag = nullptr, * pointer2;
	int tmp;
	do
	{
		for (pointer2 = top; pointer2->pointer_next != flag; pointer2 = pointer2->pointer_next)
			if (pointer2->info > pointer2->pointer_next->info)
			{
				tmp = pointer2->info;
				pointer2->info = pointer2->pointer_next->info;
				pointer2->pointer_next->info = tmp;
			}
		flag = pointer2;
	} while (top->pointer_next != flag);
}

void Output_stack(Element* top)
{
	if (top != nullptr)
	{
		cout << setw(5) << top->info;
		Output_stack(top->pointer_next);
	}
}

Element* push(Element* top, int value, int& size)
{
	Element* new_top = new Element;
	new_top->info = value;
	new_top->pointer_next = top;
	size++;
	return new_top;
}

Element* pop(Element** top, int& size)
{
	Element* new_top = (*top)->pointer_next;
	delete* top;
	size--;
	return new_top;
}

void Delete_stack(Element** top, int& size)
{
	Element* new_top;
	while (*top != nullptr)
	{
		new_top = (*top)->pointer_next;
		delete* top;
		*top = new_top;
	}
	size = 0;
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

