#include "employee.h"
#include <iostream>
using namespace std;

Employee::Employee() : surname(""), position(""), year_of_hire(0), salary(0.0) {}

void Employee::inputEmployee() {
    cout << "Введіть прізвище: ";
    cin.ignore();
    getline(cin, surname);

    cout << "Введіть посаду: ";
    getline(cin, position);

    cout << "Введіть оклад: ";
    while (!(cin >> salary)) {
        cout << "Невірний ввід! Введіть число для окладу: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Введіть рік прийому на роботу: ";
    while (!(cin >> year_of_hire)) {
        cout << "Невірний ввід! Введіть число для року: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void Employee::printEmployee() const {
    cout << "Прізвище: " << surname << ", Посада: " << position
        << ", Оклад: " << salary << ", Рік прийому на роботу: " << year_of_hire << endl;
}
