#include <iostream>   // Підключення бібліотеки введення/виведення
#include <vector>     // Підключення контейнера std::vector
#include <string>     // Підключення бібліотеки рядків
#include <windows.h>  // Підключення Windows API
using namespace std;

// Головна функція для Завдання 4 (Варіант 11)
int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    cout << "=== ZAVDANNYA 4 (Variant 11) ===" << endl;
    cout << "Vvedit ryadok dlya koduvannya: ";
    string input;
    getline(cin, input); // Зчитування вхідної послідовності символів (байтів)

    int n = static_cast<int>(input.length());
    vector<unsigned char> a(n); // Вектор байтів вхідної послідовності

    for (int i = 0; i < n; i++) {
        a[i] = static_cast<unsigned char>(input[i]);
    }

    // Кодування за правилом: a[i] = a[i] ^ (255 - (i mod 256))
    cout << "\nZakodovani bayty (HEX): ";
    for (int i = 0; i < n; i++) {
        unsigned char key = static_cast<unsigned char>(255 - (i % 256));
        a[i] = a[i] ^ key; // Побітове виключне АБО (XOR)
        cout << hex << (int)a[i] << " ";
    }
    cout << dec << endl;

    // Декодування (повторне застосування операції XOR повертає початкове значення)
    cout << "Dekodovanyy ryadok: ";
    for (int i = 0; i < n; i++) {
        unsigned char key = static_cast<unsigned char>(255 - (i % 256));
        a[i] = a[i] ^ key;
        cout << a[i];
    }
    cout << endl;

    return 0;
}