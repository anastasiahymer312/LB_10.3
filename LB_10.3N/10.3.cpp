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
        cout << "Введіть прізвище: ";
        cin.ignore(); // Очищаємо буфер
        getline(cin, surname);

        cout << "Введіть посаду: ";
        getline(cin, position);

        cout << "Введіть оклад: ";
        cin >> salary;

        cout << "Введіть рік прийому на роботу: ";
        cin >> year_of_hire;
    }

    void printEmployee() const {
        cout << "Прізвище: " << surname << ", Посада: " << position
            << ", Оклад: " << salary << ", Рік прийому на роботу: " << year_of_hire << endl;
    }
};

// Функція для додавання нового співробітника
static void addEmployee(Employee* employees, int& size) {
    Employee temp;
    temp.inputEmployee();
    employees[size] = temp; // Додаємо співробітника в масив
    size++;
}

// Видалення співробітника
static void deleteEmployee(Employee* employees, int& size) {
    string surname;
    cout << "Введіть прізвище співробітника для видалення: ";
    cin.ignore(); // Очищаємо буфер
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
            employees[i] = employees[i + 1]; // Зсув елементів в масиві
        }
        size--;
        cout << "Співробітника видалено успішно." << endl;
    }
    else {
        cout << "Співробітника не знайдено." << endl;
    }
}

// Редагування даних співробітника
static void editEmployee(Employee* employees, int size) {
    string surname;
    cout << "Введіть прізвище співробітника для редагування: ";
    cin.ignore(); // Очищаємо буфер
    getline(cin, surname);

    int index = -1;
    for (int i = 0; i < size; i++) {
        if (employees[i].surname == surname) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        cout << "Редагуємо співробітника: " << employees[index].surname << endl;
        employees[index].inputEmployee(); // Заміна старих даних новими
    }
    else {
        cout << "Співробітника не знайдено." << endl;
    }
}

// Сортування співробітників за прізвищем
static void sortByName(Employee* employees, int size) {
    sort(employees, employees + size, [](const Employee& a, const Employee& b) {
        return a.surname < b.surname;
        });
}

// Сортування співробітників за окладом
static void sortBySalary(Employee* employees, int size) {
    sort(employees, employees + size, [](const Employee& a, const Employee& b) {
        return a.salary > b.salary; // Сортуємо за спаданням окладу
        });
}

// Сортування співробітників за роком прийому на роботу
static void sortByYear(Employee* employees, int size) {
    sort(employees, employees + size, [](const Employee& a, const Employee& b) {
        return a.year_of_hire < b.year_of_hire;
        });
}

// Виведення всіх співробітників на екран
static void printAllEmployees(const Employee* employees, int size) {
    for (int i = 0; i < size; i++) {
        employees[i].printEmployee();
    }
}

// Пошук співробітника за прізвищем
static void searchEmployee(const Employee* employees, int size) {
    string surname;
    cout << "Введіть прізвище співробітника для пошуку: ";
    cin.ignore(); // Очищаємо буфер
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
        cout << "Співробітника не знайдено." << endl;
    }
}

// Збереження даних про співробітників у файл
static void saveToFile(const Employee* employees, int size, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < size; i++) {
            file << employees[i].surname << endl;
            file << employees[i].position << endl;
            file << employees[i].salary << endl;
            file << employees[i].year_of_hire << endl;
        }
        cout << "Дані успішно збережено у файл." << endl;
    }
    else {
        cout << "Помилка при відкритті файлу для запису." << endl;
    }
}

// Завантаження даних з файлу
static void loadFromFile(Employee* employees, int& size, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        Employee temp;
        while (getline(file, temp.surname)) {
            getline(file, temp.position);
            file >> temp.salary;
            file >> temp.year_of_hire;
            file.ignore(); // Для очищення буфера після int

            employees[size] = temp;
            size++;
        }
        cout << "Дані успішно завантажено з файлу." << endl;
    }
    else {
        cout << "Помилка при відкритті файлу для читання." << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int size = 0;
    int capacity = 10; // Встановлюємо початкову ємність масиву
    Employee* employees = new Employee[capacity]; // Створюємо динамічний масив співробітників
    int choice;

    do {
        cout << "Меню: \n";
        cout << "1. Додати співробітника\n";
        cout << "2. Видалити співробітника\n";
        cout << "3. Редагувати співробітника\n";
        cout << "4. Сортувати співробітників за прізвищем\n";
        cout << "5. Сортувати співробітників за окладом\n";
        cout << "6. Сортувати співробітників за роком прийому на роботу\n";
        cout << "7. Вивести всіх співробітників\n";
        cout << "8. Пошук співробітника\n";
        cout << "9. Зберегти дані у файл\n";
        cout << "10. Завантажити дані з файлу\n";
        cout << "0. Вихід\n";
        cout << "Введіть вибір: ";
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
            cout << "Введіть ім'я файлу для збереження: ";
            cin >> filename;
            saveToFile(employees, size, filename);
            break;
        }
        case 10: {
            string filename;
            cout << "Введіть ім'я файлу для завантаження: ";
            cin >> filename;
            loadFromFile(employees, size, filename);
            break;
        }
        case 0:
            cout << "Вихід з програми...\n";
            break;
        default:
            cout << "Невірний вибір, спробуйте ще раз.\n";
        }
    } while (choice != 0);

    delete[] employees; // Очищаємо динамічний масив перед виходом з програми
    return 0;
}
