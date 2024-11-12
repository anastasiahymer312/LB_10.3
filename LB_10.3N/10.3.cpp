#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include<Windows.h>
using namespace std;

struct Employee {
    string surname;
    string position;
    int year_of_hire;
    double salary;

    Employee() : surname(""), position(""), year_of_hire(0), salary(0.0) {}

    void inputEmployee() {
        cout << "������ �������: ";
        cin.ignore(); // ������� �����
        getline(cin, surname);

        cout << "������ ������: ";
        getline(cin, position);

        cout << "������ �����: ";
        cin >> salary;

        cout << "������ �� ������� �� ������: ";
        cin >> year_of_hire;
    }

    void printEmployee() const {
        cout << "�������: " << surname << ", ������: " << position
            << ", �����: " << salary << ", г� ������� �� ������: " << year_of_hire << endl;
    }
};

// ������� ��� ��������� ������ �����������
static void addEmployee(Employee* employees, int& size) {
    Employee temp;
    temp.inputEmployee();
    employees[size] = temp; // ������ ����������� � �����
    size++;
}

// ��������� �����������
static void deleteEmployee(Employee* employees, int& size) {
    string surname;
    cout << "������ ������� ����������� ��� ���������: ";
    cin.ignore(); // ������� �����
    getline(cin, surname);

    int index = -1;
    for (int i = 0; i < size; i++) {
        if (employees[i].surname == surname) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (int i = index; i < size - 1; i++) {
            employees[i] = employees[i + 1]; // ���� �������� � �����
        }
        size--;
        cout << "����������� �������� ������." << endl;
    }
    else {
        cout << "����������� �� ��������." << endl;
    }
}

// ����������� ����� �����������
static void editEmployee(Employee* employees, int size) {
    string surname;
    cout << "������ ������� ����������� ��� �����������: ";
    cin.ignore(); // ������� �����
    getline(cin, surname);

    int index = -1;
    for (int i = 0; i < size; i++) {
        if (employees[i].surname == surname) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        cout << "�������� �����������: " << employees[index].surname << endl;
        employees[index].inputEmployee(); // ����� ������ ����� ������
    }
    else {
        cout << "����������� �� ��������." << endl;
    }
}

// ���������� ����������� �� ��������
static void sortByName(Employee* employees, int size) {
    sort(employees, employees + size, [](const Employee& a, const Employee& b) {
        return a.surname < b.surname;
        });
}

// ���������� ����������� �� �������
static void sortBySalary(Employee* employees, int size) {
    sort(employees, employees + size, [](const Employee& a, const Employee& b) {
        return a.salary > b.salary; // ������� �� ��������� ������
        });
}

// ���������� ����������� �� ����� ������� �� ������
static void sortByYear(Employee* employees, int size) {
    sort(employees, employees + size, [](const Employee& a, const Employee& b) {
        return a.year_of_hire < b.year_of_hire;
        });
}

// ��������� ��� ����������� �� �����
static void printAllEmployees(const Employee* employees, int size) {
    for (int i = 0; i < size; i++) {
        employees[i].printEmployee();
    }
}

// ����� ����������� �� ��������
static void searchEmployee(const Employee* employees, int size) {
    string surname;
    cout << "������ ������� ����������� ��� ������: ";
    cin.ignore(); // ������� �����
    getline(cin, surname);

    int index = -1;
    for (int i = 0; i < size; i++) {
        if (employees[i].surname == surname) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        employees[index].printEmployee();
    }
    else {
        cout << "����������� �� ��������." << endl;
    }
}

// ���������� ����� ��� ����������� � ����
static void saveToFile(const Employee* employees, int size, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < size; i++) {
            file << employees[i].surname << endl;
            file << employees[i].position << endl;
            file << employees[i].salary << endl;
            file << employees[i].year_of_hire << endl;
        }
        cout << "��� ������ ��������� � ����." << endl;
    }
    else {
        cout << "������� ��� ������� ����� ��� ������." << endl;
    }
}

// ������������ ����� � �����
static void loadFromFile(Employee* employees, int& size, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        Employee temp;
        while (getline(file, temp.surname)) {
            getline(file, temp.position);
            file >> temp.salary;
            file >> temp.year_of_hire;
            file.ignore(); // ��� �������� ������ ���� int

            employees[size] = temp;
            size++;
        }
        cout << "��� ������ ����������� � �����." << endl;
    }
    else {
        cout << "������� ��� ������� ����� ��� �������." << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int size = 0;
    int capacity = 10; // ������������ ��������� ������ ������
    Employee* employees = new Employee[capacity]; // ��������� ��������� ����� �����������
    int choice;

    do {
        cout << "����: \n";
        cout << "1. ������ �����������\n";
        cout << "2. �������� �����������\n";
        cout << "3. ���������� �����������\n";
        cout << "4. ��������� ����������� �� ��������\n";
        cout << "5. ��������� ����������� �� �������\n";
        cout << "6. ��������� ����������� �� ����� ������� �� ������\n";
        cout << "7. ������� ��� �����������\n";
        cout << "8. ����� �����������\n";
        cout << "9. �������� ��� � ����\n";
        cout << "10. ����������� ��� � �����\n";
        cout << "0. �����\n";
        cout << "������ ����: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (size >= capacity) {
                capacity *= 2;
                Employee* newEmployees = new Employee[capacity];
                for (int i = 0; i < size; i++) {
                    newEmployees[i] = employees[i];
                }
                delete[] employees;
                employees = newEmployees;
            }
            addEmployee(employees, size);
            break;
        case 2:
            deleteEmployee(employees, size);
            break;
        case 3:
            editEmployee(employees, size);
            break;
        case 4:
            sortByName(employees, size);
            break;
        case 5:
            sortBySalary(employees, size);
            break;
        case 6:
            sortByYear(employees, size);
            break;
        case 7:
            printAllEmployees(employees, size);
            break;
        case 8:
            searchEmployee(employees, size);
            break;
        case 9: {
            string filename;
            cout << "������ ��'� ����� ��� ����������: ";
            cin >> filename;
            saveToFile(employees, size, filename);
            break;
        }
        case 10: {
            string filename;
            cout << "������ ��'� ����� ��� ������������: ";
            cin >> filename;
            loadFromFile(employees, size, filename);
            break;
        }
        case 0:
            cout << "����� � ��������...\n";
            break;
        default:
            cout << "������� ����, ��������� �� ���.\n";
        }
    } while (choice != 0);

    delete[] employees; // ������� ��������� ����� ����� ������� � ��������
    return 0;
}
