//Написать и отладить программу(задания из табл. 7.1) аппроксимации функции f(x) на интервале[a, b] заданным методом,
//m – количество точек, в которых известна функция(размер таблицы).Вид функции задан для получения значений таблицы(xi, yi),
//i = 1, 2, …, m и проверки качества аппроксимации.
//x^3-5x^2     a = -2, b = 5, m = 5  Многочлен Ньютона

#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

double f(double);
double Newton(double*, double*, double, double);
double Check_value(double*, double, double);

int main()
{
    double a, b, number_of_points, number_of_definding_points;
    cout << "Enter amount of known points (recommended 5): ";
    Check_value(&number_of_points, 1., 32767.);
    cout << "Enter interval (recommended -2, 5): " << endl;
    cout << "a= ";
    Check_value(&a, -32767., 32767.);
    cout << endl;
    cout << "b= ";
    Check_value(&b, a, 32767.);
    cout << endl;
    double h = (b - a) / (number_of_points - 1);
    double* x = new double[number_of_points];
    double* y = new double[number_of_points];
    for (int i = 0; i < number_of_points; i++)
    {
        x[i] = a + h * i;
        y[i] = f(x[i]);
        cout << "x[" << i << "] = " << setw(4) << x[i] << "\ty[" << i << "] = " << setw(9) << y[i] << "\n";
    }
    cout << endl;
    cout << "Enter amount of points you want to calculate (recommended 10): " << endl;
    Check_value(&number_of_definding_points, 1, 32767);
    h = (b - a) / (number_of_definding_points - 1);
    double eps = 0;
    for (int i = 0; i < number_of_definding_points; i++)
    {
        double result = Newton(x, y, a + h * i, number_of_points);
        if (eps < fabs(f(a + h * i) - result))
            eps = fabs(f(a + h * i) - result);
        cout << "x = " << setw(4) << a + h * i << "\tNewton(x) = " << setw(9) << result << "\t\tF(x) = " << setw(9) << f(a + h * i) << "\tEps = " << fabs(f(a + h * i) - result) << "\n";
    }
    cout << "\nKnown points: " << number_of_points << "\t\tCalculated points: " << number_of_definding_points << "\t\t Eps max = " << eps << endl;
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

double f(double x)
{
    return x * x * x - 5 * x * x;
}

double Newton(double x[], double y[], double xt, double iterations)
{
    double* delta = new double[iterations];
    for (int i = 0; i < iterations; i++)
    {
        delta[i] = y[i];
    }
    double p = 1;
    double result = y[0];
    for (int k = 1; k <= iterations - 1; k++)
    {
        for (int i = 1; i <= iterations - k; i++)
            delta[i - 1] = (delta[i - 1] - delta[i]) / (x[i - 1] - x[i - 1 + k]);
        p *= (xt - x[k - 1]);
        result += p * delta[0];
    }
    delete[] delta;
    return result;
}