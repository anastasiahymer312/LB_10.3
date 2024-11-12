#include "employee.h"
#include <iostream>
using namespace std;

Employee::Employee() : surname(""), position(""), year_of_hire(0), salary(0.0) {}

void Employee::inputEmployee() {
    cout << "������ �������: ";
    cin.ignore();
    getline(cin, surname);

    cout << "������ ������: ";
    getline(cin, position);

    cout << "������ �����: ";
    while (!(cin >> salary)) {
        cout << "������� ���! ������ ����� ��� ������: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "������ �� ������� �� ������: ";
    while (!(cin >> year_of_hire)) {
        cout << "������� ���! ������ ����� ��� ����: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void Employee::printEmployee() const {
    cout << "�������: " << surname << ", ������: " << position
        << ", �����: " << salary << ", г� ������� �� ������: " << year_of_hire << endl;
}
