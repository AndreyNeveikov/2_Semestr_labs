// lab 3.cpp Написать программу по созданию, добавлению(в начало, в конец), 
//про - смотру(с начала, с конца) и решению поставленной в лаб.работе № 2 задачи
//для двунаправленных линейных списков.


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


struct Spisok {
    int value;
    Spisok* next, * prev;
} *begin, * end, * rez;



void Create_Spisok(Spisok**, Spisok**, int);
void Add_Spisok(int, Spisok**, Spisok**, int);
void View_Spisok(int, Spisok*);
void Del_All(Spisok**);
int Check_choice(int*, int, int);
void Persoonal_task(Spisok*&, Spisok*&);



int main() {
    Spisok* begin = NULL, * end = NULL, * rez;
    int num = 0, choice, direction, tmp = 0;
    char init[2][13] = { "begin", "end" };
    while (true) {
        cout << "\nPlease select an operation: \n 1. Create queue \n 2. Input element \n 3. View queue \n 4. Delete queue \n 5. Personal task \n 6. Exit" << endl;
        Check_choice(&choice, 1, 6);
        switch (choice) {
        case 1:
            if (begin != NULL)
            {
                cout << "Memory for the list has been successfully allocated!" << endl;
            }
            cout << "Enter the first value : ";
            Check_choice(&num, -32766, 32766);
            Create_Spisok(&begin, &end, num);
            cout << "The list has been successfully created!" << endl << "-----------------------------------------------------" << endl;
            break;

        case 2:
            cout << "How many elements you want to add in list?" << endl;
            int amount;
            Check_choice(&amount, 1, 1000);
            cout << "1.Add to the beginning \n2.Add to the end" << endl;
            Check_choice(&direction, 1, 2);
            for (int element_index = 0; element_index < amount; element_index++)
            {
                cout << "New element = ";
                Check_choice(&num, -32766, 32766);
                Add_Spisok(direction, &begin, &end, num);
                if (direction == 1)
                    rez = begin;
                else
                    rez = end;
                rez--;
                cout << "Item added to " << init[direction - 1] << endl;
                cout << "-----------------------------------------------------" << endl;
            }
            break;

        case 3:
            if (!begin && !end)
            {
                cout << "The list is empty!" << endl;
                break;
            }
            cout << "\n1.View from the beginning \n2 .View from the end" << endl;
            cout << "-----------------------" << endl;
            rez = begin;
            direction = 1;
            View_Spisok(direction, rez);
            cout << "( /\\  || End of queue is here)-----------------------------------------------------" << endl;
            cout << "  ||  \\/                  " << endl;
            rez = end;
            direction = 2;
            View_Spisok(direction, rez);
            cout << "-----------------------------------------------------" << endl;
            break;

        case 4:
            Del_All(&begin);
            cout << "The memory is cleared!" << endl << "-----------------------------------------------------" << endl;
            break;

        case 5:
            Persoonal_task(*&begin, *&end);
            cout << "Deletion of negative elements completed successfully!" << "-----------------------------------------------------" << endl << endl;
            rez = begin;
            direction = 1;
            View_Spisok(direction, rez);
            cout << "-----------------------------------------------------" << endl << endl;

            break;

        case 6:
            cout << "Successfully exit!";
            Del_All(&begin);
            exit(0);
        }
    }
    return 0;
}



void Create_Spisok(Spisok** start, Spisok** finish, int num) {
    rez = new Spisok;
    rez->value = num;
    rez->next = rez->prev = NULL;
    *start = *finish = rez;
}



void Add_Spisok(int direction, Spisok** start, Spisok** finish, int num) {
    rez = new Spisok;
    rez->value = num;
    if (direction == 1)
    {
        rez->prev = NULL;
        rez->next = *start;
        (*start)->prev = rez;
        *start = rez;
    }
    else
    {
        rez->next = NULL;
        rez->prev = *finish;
        (*finish)->next = rez;
        *finish = rez;
    }
}



void View_Spisok(int direction, Spisok* rez) {
    while (rez != NULL) {
        cout << rez->value << endl;
        if (direction == 1)
            rez = rez->next;
        else
            rez = rez->prev;
    }
}



void Del_All(Spisok** t) {
    Spisok* elem;
    while (*t != NULL) {
        elem = *t;
        *t = (*t)->next;
        delete elem;
    }
}



int Check_choice(int* x, int min, int max)
{
    int trial = 0;
    while (true) {
        cin >> *x;
        if ((*x < min) || (*x > max) || cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Incorrect input! Input value again: \n";
            trial++;
            if (trial == 3)
            {
                cout << "Dear user, stay focused please :)\nYou will succeed!" << endl;
                trial = 0;
            }
        }
        else
        {
            cin.ignore(32767, '\n');
            return *x;
        }
    }
}


void Persoonal_task(Spisok*& begin, Spisok*& end)
{

    Spisok* rez = begin;
    while (rez != nullptr)
    {
        if (rez->value < 0)
        {
            if (rez->prev == nullptr) //head
            {
                begin = rez->next;
                if (begin == nullptr)
                {
                    delete rez;
                    rez = end = nullptr;
                }
                else
                {
                    rez = rez->next;
                    delete rez->prev;
                    rez->prev = nullptr;
                }
            }
            else if (rez->next == nullptr) //tail
            {
                end = rez->prev;
                end->next = nullptr;
                delete rez;
                rez = nullptr;
            }
            else
            {

                rez = rez->prev;
                rez->next = rez->next->next;
                delete rez->next->prev;
                rez->next->prev = rez;
                rez = rez->next;
            }
        }
        else
            rez = rez->next;
    }
}


