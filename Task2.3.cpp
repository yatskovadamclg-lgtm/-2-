#include <iostream>   // Підключення бібліотеки введення/виведення
#include <fstream>    // Підключення бібліотеки роботи з файлами
#include <string>     // Підключення бібліотеки рядків для getline
#include <windows.h>  // Підключення Windows API
using namespace std;

// Структура з бітовими полями відповідно до Варіанту 11 (разом 16 біт = 2 байти)
struct BitFieldsV11 {
    unsigned short row : 3; // Біти 0-2: номер рядка символу (3 біти)
    unsigned short lowASCII : 4; // Біти 3-6: молодша частина ASCII коду (4 біти)
    unsigned short parity1 : 1; // Біт 7: біт парності перших двох полів (1 біт)
    unsigned short highASCII : 4; // Біти 8-11: старша частина ASCII коду (4 біти)
    unsigned short col : 3; // Біти 12-14: позиція символу в рядку (3 біти)
    unsigned short parity2 : 1; // Біт 15: біт парності попередніх двох полів (1 біт)
};

// Об'єднання (union), що поєднує бітові поля та 16-бітне ціле число в одній області пам'яті
union EncryptedChar {
    BitFieldsV11 bits;
    unsigned short raw;
};

// Допоміжна функція підрахунку біта парності
unsigned short getParity(unsigned short val, int fromBit, int toBit) {
    unsigned short p = 0;
    for (int i = fromBit; i <= toBit; i++) {
        if ((val >> i) & 1) p ^= 1;
    }
    return p;
}

// Головна функція для Завдання 3 (Варіант 11)
int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    char text[8][9];
    EncryptedChar data[64];

    cout << "=== ZAVDANNYA 3: BITOVI POLYA TA UNION (Variant 11) ===" << endl;
    cout << "Rozmir struktury BitFieldsV11: " << sizeof(BitFieldsV11) << " bayty" << endl;
    cout << "Vvedit 8 ryadkiv tekstu:" << endl;

    for (int r = 0; r < 8; r++) {
        cout << "Ryadok " << r << ": ";
        string line;
        getline(cin, line);
        for (int c = 0; c < 8; c++) {
            text[r][c] = (c < (int)line.length()) ? line[c] : ' ';
        }
        text[r][8] = '\0';
    }

    // Шифрування через бітові поля структури
    int idx = 0;
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            unsigned char ch = static_cast<unsigned char>(text[r][c]);
            EncryptedChar ec;
            ec.raw = 0;
            ec.bits.row = r;
            ec.bits.lowASCII = ch & 0x0F;
            ec.bits.parity1 = getParity(ec.raw, 0, 6);
            ec.bits.highASCII = (ch >> 4) & 0x0F;
            ec.bits.col = c;
            ec.bits.parity2 = getParity(ec.raw, 8, 14);
            data[idx++] = ec;
        }
    }

    // Запис та зчитування з бінарного файлу
    ofstream fout("union_v11.bin", ios::binary);
    fout.write(reinterpret_cast<char*>(data), sizeof(data));
    fout.close();

    EncryptedChar readData[64];
    ifstream fin("union_v11.bin", ios::binary);
    fin.read(reinterpret_cast<char*>(readData), sizeof(readData));
    fin.close();

    // Дешифрування через звертання до бітових полів структури
    char restored[8][9];
    for (int i = 0; i < 64; i++) {
        EncryptedChar ec = readData[i];
        char ch = static_cast<char>((ec.bits.highASCII << 4) | ec.bits.lowASCII);
        restored[ec.bits.row][ec.bits.col] = ch;
    }

    cout << "\nVidnovlenyy tekst cherez bitovi polya:" << endl;
    for (int r = 0; r < 8; r++) {
        restored[r][8] = '\0';
        cout << "Ryadok " << r << ": [" << restored[r] << "]" << endl;
    }

    return 0;
}