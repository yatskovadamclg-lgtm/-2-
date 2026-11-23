#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

unsigned short calcParity(unsigned short val, int startBit, int endBit) {
    unsigned short parity = 0;
    for (int i = startBit; i <= endBit; i++) {
        if ((val >> i) & 1) {
            parity ^= 1;
        }
    }
    return parity;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    char text[8][9];
    unsigned short encrypted[64];

    cout << "=== ZAVDANNYA 2: SHYFRUVANNYA (Variant 11) ===" << endl;
    cout << "Vvedit 8 ryadkiv tekstu (do 8 symvoliv u kozhnomu):" << endl;

    for (int row = 0; row < 8; row++) {
        cout << "Ryadok " << row << ": ";
        string line;
        getline(cin, line);
        for (int col = 0; col < 8; col++) {
            if (col < (int)line.length()) {
                text[row][col] = line[col];
            }
            else {
                text[row][col] = ' ';
            }
        }
        text[row][8] = '\0';
    }

    int idx = 0;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            unsigned char ch = static_cast<unsigned char>(text[row][col]);
            unsigned short lowASCII = ch & 0x0F;
            unsigned short highASCII = (ch >> 4) & 0x0F;

            unsigned short word = 0;
            word |= (row & 0x07);
            word |= (lowASCII << 3);

            unsigned short p1 = calcParity(word, 0, 6);
            word |= (p1 << 7);

            word |= (highASCII << 8);
            word |= ((col & 0x07) << 12);

            unsigned short p2 = calcParity(word, 8, 14);
            word |= (p2 << 15);

            encrypted[idx++] = word;
        }
    }

    ofstream fout("encrypted_v11.bin", ios::binary);
    fout.write(reinterpret_cast<char*>(encrypted), sizeof(encrypted));
    fout.close();

    cout << "\nTekst uspishno zashyfrovano u fayl 'encrypted_v11.bin'!" << endl;
    cout << "Pershi 8 zashyfrovanykh sliv (HEX): ";
    for (int i = 0; i < 8; i++) cout << hex << encrypted[i] << " ";
    cout << dec << endl;

    return 0;
}