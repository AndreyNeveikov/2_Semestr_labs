// lab 4.cpp : Написать программу расшифровки и вычисления арифметических выражений с использованием стека. 
//

#include <iostream>
#include <clocale>
#include <string>
#include <stdio.h>
#include <conio.h>

using namespace std;

struct Stack {
	char symbol;
	Stack* next;
};

Stack* Add_to_stack(Stack*, char);
Stack* Take_from_stack(Stack*, char*);
int Input_array_of_char(char*, int);
int Priority_level(char);
double Calculate(Stack*, char*);
double Check_choice(double*, int, int);
int Checking_brackets(char*);

int main()
{
	setlocale(LC_ALL, "rus");
	int check = 0;
	double Restart;
	char char_symbol, inputing_string[300], Polish_string[300];
	while (true)
	{

		int inputing_string_index = 0, Polish_string_index = 0;
		cout << "Input mathematical expression without spaces: ";
		Stack* top, * op_stack = NULL;
		check = Input_array_of_char(inputing_string, check);
		if (check != 1)
		{
			cout << "It is necessary to place the brackets correctly! Please press any key and restart the program!";
			system("pause");
			exit(0);
		}
		while (inputing_string[inputing_string_index] != '\0')
		{
			if (inputing_string[inputing_string_index] >= 'a' && inputing_string[inputing_string_index] <= 'z')
			{
				Polish_string[Polish_string_index++] = inputing_string[inputing_string_index];
			}
			if (inputing_string[inputing_string_index] == '(')
				op_stack = Add_to_stack(op_stack, inputing_string[inputing_string_index]);
			else if (inputing_string[inputing_string_index] == ')')
			{
				while ((op_stack->symbol) != '(')
				{
					op_stack = Take_from_stack(op_stack, &char_symbol);
					if (!op_stack) char_symbol = '\0';
					Polish_string[Polish_string_index++] = char_symbol;
				}
				top = op_stack;
				op_stack = op_stack->next;
				delete top;
			}
			else if (inputing_string[inputing_string_index] == '+' || inputing_string[inputing_string_index] == '-' || inputing_string[inputing_string_index] == '*' || inputing_string[inputing_string_index] == '/')
			{
				while (op_stack != NULL && Priority_level(op_stack->symbol) >= Priority_level(inputing_string[inputing_string_index]))
				{
					op_stack = Take_from_stack(op_stack, &char_symbol);
					Polish_string[Polish_string_index++] = char_symbol;
				}
				op_stack = Add_to_stack(op_stack, inputing_string[inputing_string_index]);
			}
			inputing_string_index++;
		}
		while (op_stack != NULL)
		{
			op_stack = Take_from_stack(op_stack, &char_symbol);
			Polish_string[Polish_string_index++] = char_symbol;
		}
		Polish_string[Polish_string_index] = '\0';
		cout << "\nResult in Polish notation:  " << Polish_string << endl;
		cout << "Result: " << Calculate(op_stack, Polish_string) << endl;

		system("pause");

		cout << "\nDo you want to perform the calculation again?\n1.Yes\n2.No\n";
		Check_choice(&Restart, 1, 2);
		if (Restart == 2)
			exit(0);
	}
	return 0;
}

double Check_choice(double* x, int max_lim, int min_lim) {
	int counter = 0;
	while (true)
	{
		cin >> *x;
		if ((*x < max_lim) || (*x > min_lim) || cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Oops, incorrect input. Please try again: \n";
			counter++;
			if (counter == 3)
			{
				cout << "Dear user, please don't break the code :)\n";;
				counter = 0;
			}
		}
		else
		{
			cin.ignore(32767, '\n');
			return *x;
		}
	}
}

int Checking_brackets(char* arr)
{
	int counter = 0;
	for (int element_index = 0; arr[element_index] != '\0'; element_index++)
	{
		if (arr[element_index] == '(')
		{
			counter++;
		}
		if (arr[element_index] == ')')
		{
			counter--;
			if (counter < 0)
				return 0;
		}
	}
	if (counter == 0)
		return 1;
	else
		return 0;
}

int Input_array_of_char(char* array_of_char, int check)
{

	int element_index = 1;
	array_of_char[0] = ' ';
	while (true)
	{
		array_of_char[element_index] = _getch();
		if (array_of_char[element_index] == 13)
			break;
		if (!((isalpha(array_of_char[element_index])) && !isalpha(array_of_char[element_index - 1]) || ((((array_of_char[element_index] == '+') || (array_of_char[element_index] == '-') || (array_of_char[element_index] == '*') || (array_of_char[element_index] == '/')) && element_index > 1) && (isalpha(array_of_char[element_index - 1]) || (array_of_char[element_index - 1] == ')'))) || ((array_of_char[element_index] == '(') && (!isalpha(array_of_char[element_index - 1]) && (array_of_char[element_index - 1] != ')'))) || ((array_of_char[element_index] == ')') && (isalpha(array_of_char[element_index - 1])))))
			continue;
		cout << array_of_char[element_index];
		element_index++;
	}
	array_of_char[element_index] = '\0';
	cout << endl;
	check = Checking_brackets(array_of_char);
	return check;
}

int Priority_level(char a)
{
	switch (a) {
	case'*': case'/': return 3;
	case'+': case'-': return 2;
	case'(': return 1;
	}
	return 0;
}

Stack* Add_to_stack(Stack* p, char output)
{
	Stack* t = new Stack;
	t->symbol = output;
	t->next = p;
	return t;
}

Stack* Take_from_stack(Stack* p, char* input)
{
	Stack* t = p;
	*input = p->symbol;
	p = p->next;
	delete t;
	return p;
}



double Calculate(Stack* p, char* Polish_string)
{
	Stack* top = p;
	int element_index, index_of_alpha, counter = 0;
	char symbol, operand1, operand2, s_counter = 'z' + 1;
	double op1, op2, result = 0, array_of_double[200], tmp = 0;
	cout << "Enter variable values: " << endl;
	for (element_index = 0; Polish_string[element_index] != '\0'; ++element_index)
	{
		symbol = Polish_string[element_index];
		if (symbol >= 'a' && symbol <= 'z')
		{
			for (index_of_alpha = 0, counter = 0; index_of_alpha <= element_index; index_of_alpha++)
			{
				if (Polish_string[element_index] == Polish_string[index_of_alpha])
					counter++;
			}
			if (counter < 2) {
				cout << symbol << " = ";
				array_of_double[int(symbol)] = Check_choice(&tmp, -32766, 32766);
			}
		}
		if (!(symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/'))
			top = Add_to_stack(top, symbol);
		else
		{
			top = Take_from_stack(top, &operand1);
			top = Take_from_stack(top, &operand2);
			op1 = array_of_double[int(operand1)];
			op2 = array_of_double[int(operand2)];
			switch (symbol) {
			case'+': result = op2 + op1; break;
			case'-': result = op2 - op1; break;
			case'*': result = op2 * op1; break;
			case'/': {
				if (op1 == 0)
				{
					cout << "Error! The formula contains division by 0" << endl;
					system("pause");
					return 0;
				}
				result = op2 / op1;
				break;
			}
			}
			array_of_double[int(s_counter)] = result;
			top = Add_to_stack(top, s_counter);
			s_counter++;
		}
	}
	return result;
}