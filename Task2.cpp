#include <iostream>   // Підключення бібліотеки для стандартного введення/виведення (cin, cout)
#include <fstream>    // Підключення бібліотеки для роботи з файлами (ifstream, ofstream)
#include <vector>     // Підключення бібліотеки стандартного контейнера std::vector
#include <windows.h>  // Підключення Windows API для коректного відображення кирилиці
using namespace std; // Використання стандартного простору імен std

// Функція введення масиву з консолі та запису у текстовий файл
void createTextFileFromConsole(const string& filename) {
    int n;   // Змінна для розміру масиву
    cout << "Vvedit rozmir masivu N: ";   // Виведення підказки для введення розміру
    cin >> n;    // Зчитування розміру масиву з клавіатури
    ofstream fout(filename);    // Відкриття текстового файлу для запису
    if (!fout.is_open()) {                           // Перевірка, чи успішно відкрився файл
        cout << "Pomylka vidkryttya faylu!" << endl; // Виведення повідомлення про помилку
        return;       // Достроковий вихід із функції
    }
    fout << n << endl;     // Запис розміру масиву N у перший рядок файлу
    cout << "Vvedit " << n << " elementiv:" << endl; // Запит на введення елементів масиву
    for (int i = 0; i < n; i++) {                    // Цикл для введення n елементів
        double val;  // Тимчасова змінна для поточного елемента
        cout << "A[" << i << "] = ";  // Підказка з індексом поточного елемента
        cin >> val; // Зчитування значення елемента з консолі
        fout << val << " ";         // Запис елемента у файл через пробіл
    }
    fout.close();     // Закриття файлу після завершення запису
    cout << "Dani zberezheno u fayl: " << filename << endl; // Підтвердження збереження даних
}

// Основна функція Завдання 1 (Варіант 22): добуток суми додатних та суми від'ємних елементів
void solveTask1(const string& inputFile, const string& outputFile) {
    ifstream fin(inputFile);     // Відкриття вхідного текстового файлу для читання
    if (!fin.is_open()) {     // Перевірка, чи існує та чи відкрився файл
        cout << "Спочатку виконайте пункт 1!" << endl;    // Підказка, якщо вхідний файл ще не створено
        return;  // Вихід із функції
    }
    int n;     // Змінна для розміру масиву A
    fin >> n;    // Зчитування розміру масиву з файлу
    if (n <= 0) {                                              // Перевірка на коректність розміру масиву
        fin.close();     // Закриття файлу
        return;  // Вихід із функції
    }
    double* A = new double[n];     // Виділення динамічної пам'яті під масив A розміром n
    double sumPos = 0;             // Змінна для суми додатних елементів
    double sumNeg = 0;             // Змінна для суми від'ємних елементів

    for (int i = 0; i < n; i++) {  // Цикл зчитування елементів із файлу в масив A
        fin >> A[i];               // Зчитування чергового елемента масиву
        if (A[i] > 0) {            // Якщо елемент додатний (> 0)
            sumPos += A[i];        // Додаємо його до суми додатних
        }
        else if (A[i] < 0) {       // Якщо елемент від'ємний (< 0)
            sumNeg += A[i];        // Додаємо його до суми від'ємних
        }
    }
    fin.close();  // Закриття вхідного файлу

    double product = sumPos * sumNeg; // Обчислення добутку суми додатних та суми від'ємних елементів

    cout << "\n--- Rezultaty Zavdannya 1 (Variant 22) ---" << endl; // Виведення заголовка результатів
    cout << "Masiv A: ";   // Підпис для вихідного масиву A
    for (int i = 0; i < n; i++) cout << A[i] << " ";    // Виведення масиву A у консоль
    cout << endl;   // Перехід на новий рядок
    cout << "Suma dodatnykh elementiv: " << sumPos << endl;   // Виведення суми додатних
    cout << "Suma vidyemnykh elementiv: " << sumNeg << endl;  // Виведення суми від'ємних
    cout << "Dobutok sum: " << product << endl;               // Виведення добутку сум

    ofstream fout(outputFile);  // Відкриття нового файлу для запису результату
    if (fout.is_open()) {       // Перевірка, чи відкрився файл для запису
        fout << sumPos << " " << sumNeg << " " << product << endl; // Запис результатів у файл
        fout.close();     // Закриття вихідного файлу
        cout << "Rezultat zberezheno u: " << outputFile << endl; // Повідомлення про збереження результату
    }
    delete[] A;   // Звільнення динамічної пам'яті масиву A
}

// Функція зчитування даних із текстового файлу в контейнер std::vector та виведення в консоль
void readToVectorAndPrint(const string& filename) {
    ifstream fin(filename);    // Відкриття текстового файлу для читання
    if (!fin.is_open()) {     // Перевірка успішності відкриття файлу
        cout << "Ne vdalosya vidkryty fayl " << filename << endl; // Повідомлення про помилку
        return; // Вихід із функції
    }
    vector<double> vec;       // Оголошення порожнього контейнера std::vector
    double val;      // Тимчасова змінна для зчитування елементів
    while (fin >> val) {      // Цикл читання чисел до кінця файлу
        vec.push_back(val);   // Додавання зчитаного числа в кінець вектора
    }
    fin.close(); // Закриття файлу
    cout << "\n--- Chytannya u std::vector ---" << endl;  // Заголовок виведення вектора
    cout << "Kilkist elementiv: " << vec.size() << endl;  // Виведення кількості елементів у векторі
    cout << "Vmist vektora (Suma+, Suma-, Dobutok): ";    // Підпис перед елементами вектора
    for (double elem : vec) {    // Цикл перебору всіх елементів вектора
        cout << elem << " ";     // Виведення кожного елемента на екран
    }
    cout << endl; // Перехід на новий рядок
}

// Головна функція з меню для Завдання 1
int main() {
    SetConsoleOutputCP(65001);    // Налаштування UTF-8 для виведення кирилиці
    SetConsoleCP(65001);          // Налаштування UTF-8 для введення кирилиці
    string textFile = "array_data.txt";      // Ім'я вхідного текстового файлу
    string outputFile = "result_task1.txt";  // Ім'я вихідного текстового файлу з результатом
    int choice;  // Змінна для вибору пункту меню
    do {                                                          // Початок циклу меню
        cout << "\n=== MENU ZAVDANNYA 1 (Variant 22) ===" << endl; // Заголовок меню
        cout << "1. Vvedennya masivu z konsoli (Text file)" << endl; // Пункт 1: створення файлу
        cout << "2. Vykonaty Zavdannya 1 (Dynamic arrays)" << endl;  // Пункт 2: обробка масиву
        cout << "3. Zchytaty rezultaty u std::vector" << endl;   // Пункт 3: читання у vector
        cout << "0. Vykhid" << endl; // Пункт 0: вихід
        cout << "Vash vybir: ";  // Запит вибору користувача
        cin >> choice;     // Зчитування вибору
        switch (choice) {                                         // Перевірка обраного пункту
        case 1:    // Якщо обрано 1
            createTextFileFromConsole(textFile);  // Створюємо текстовий файл з консолі
            break;   // Вихід із switch
        case 2: // Якщо обрано 2
            solveTask1(textFile, outputFile); // Виконуємо Завдання 1
            break; // Вихід із switch
        case 3:     // Якщо обрано 3
            readToVectorAndPrint(outputFile);  // Читаємо результат у vector і виводимо
            break;   // Вихід із switch
        case 0:   // Якщо обрано 0
            cout << "Zavershennya..." << endl;     // Повідомлення про вихід
            break;   // Вихід із switch
        default:  // Якщо введено невірний номер
            cout << "Nekorektnyy vybir!" << endl; // Повідомлення про помилку
        }
    } while (choice != 0);  // Повторювати, доки не введено 0
    return 0;  // Завершення програми
}