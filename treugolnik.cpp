#include <iostream>//подключаем библиотеку ввода и вывода
#include <conio.h>//консольный ввод вывод 
#include <math.h>// для выполнения математических условий
using namespace std;//чтобы не писать по сто раз std(чтобы работал код)


int main()//вызываем функцию(работа с целыми числами)
{
//Вычисление периметра и площади
        int a, b, c, p, s;//объявляем переменные
        cout << "Vveditе storonu: \n";//Выводим в консоль 
        cout << "A = "; cin >> a;//Вводим в консоль число
        cout << "B = "; cin >> b;//Вводим в консоль число
        cout << "C = "; cin >> c;//Вводим в консоль число
//Создаем условие если, то
        if ((b + c > a) || (a + c > b) || (a + b > c)) {//математическое выражение, при котором будети выполнятся код 
            cout << "Sushhestvuet";//вывод в консоль предложение
            p = a + b + c;//даем переменной р значение, которое выполняется после того, как ввели числа 
            cout << "\nPerimetr: " << p;//вывод в консоль уже готовое решение переменных
            p = p / 2.0;//даем переменной р еще одно значение
            s = sqrt(p * (p - a) * (p - b) * (p - c));//даем переменной s значение, которое выполняется после того, как ввели числа 
            cout << "\nPloshad:  " << s;/вывод в консоль уже готовое решение переменных
        }
        else//если стороны не равны, то выполняем след действие
            cout << "Ne sushhestvuet";//Выводим в консоль, что такого треугольника не существует



    return 0;//завершение работы функции


}

// Этот код на C++:

// 🔹 Вводит три стороны треугольника (a, b, c)
// 🔹 Проверяет, существует ли треугольник по правилу суммы двух сторон
// 🔹 Если треугольник существует:

// Вычисляет периметр

// Вычисляет площадь по формуле Герона

// Выводит результат в консоль
// 🔹 Если не существует — выводит сообщение об этом.
