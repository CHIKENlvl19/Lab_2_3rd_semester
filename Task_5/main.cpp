#include "Huffman.h"
#include <iostream>

using namespace std;

void printTable(Huffman& huffman) {
    char codes[256][32];
    for (int i = 0; i < 256; ++i)
    {
        codes[i][0] = '\0';
    }

    char temp[32];
    huffman.buildCodes(huffman.getRoot(), temp, 0, codes);

    for (int i = 0; i < 256; ++i) 
    {
        if (codes[i][0] != '\0')
        {
            if (i == ' ')
            {
                cout << "' '" << " : " << codes[i] << endl;
            }
            else
            {
                cout << (char)i << " : " << codes[i] << endl;
            }
        }
    }
}

int main() {
    
    setlocale(LC_ALL, "ru");

    Huffman huffman;
    char text[256];

    cout << "Введите строку: ";
    cin.getline(text, 256);

    if (strlen(text) == 0)
    {
        cout << "Пустая строка — ничего кодировать.\n";
        return 0;
    }

    huffman.build(text);

    char encoded[2048];
    huffman.encode(text, encoded);

    char decoded[256];
    huffman.decode(encoded, decoded);

    cout << "\nИсходная строка: " << text << endl;
    cout << "Закодировано:    " << encoded << endl;
    cout << "Декодировано:    " << decoded << endl;

    cout << "\nТаблица символов:" << endl;
    printTable(huffman);
    
    return 0;
}
