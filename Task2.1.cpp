#include <iostream>   // Підключення бібліотеки введення/виведення
#include <windows.h>  // Підключення Windows API для кирилиці
using namespace std;  // Використання простору імен std

// Головна функція для Завдання 1 (Варіант 11)
int main() {
    SetConsoleOutputCP(65001); // Налаштування кодування UTF-8
    SetConsoleCP(65001);

    int a, b, c, d; // Вхідні цілі числа
    cout << "=== ZAVDANNYA 1 (Variant 11) ===" << endl;
    cout << "Vvedit cili chysla a, b, c, d: ";
    cin >> a >> b >> c >> d; // Зчитування вхідних даних

    // Обчислення виразу виключно за допомогою побітових зсувів, додавання та віднімання:
    // 127 * a = (a << 7) - a
    // 32 * c  = (c << 5)
    // / 4096  = >> 12
    // 1200 * d = (d << 10) + (d << 7) + (d << 5) + (d << 4)
    // 131 * b  = (b << 7) + (b << 1) + b
    int part1 = (((a << 7) - a) + (c << 5)) >> 12;
    int part2 = (d << 10) + (d << 7) + (d << 5) + (d << 4);
    int part3 = (b << 7) + (b << 1) + b;

    int res_bitwise = part1 - part2 + part3; // Результат через побітові операції

    // Перевірка звичайними арифметичними операціями
    int res_standard = (127 * a + 32 * c) / 4096 - d * 1200 + b * 131;

    cout << "Rezultat (pobitovi zsuvy): " << res_bitwise << endl;
    cout << "Perevirka (zvychayna aryfmetyka): " << res_standard << endl;

    return 0;
}