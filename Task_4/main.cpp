#include "myArray.h"

using namespace std;

bool patternMatch(const char* text, const char* pattern) {
    int iText = 0;
    int iPattern = 0;
    int starPos = -1;
    int matchAfterStar = 0;

    while (text[iText] != '\0') {
        if (pattern[iPattern] == text[iText] || pattern[iPattern] == '?') 
        {
            iText++;
            iPattern++;
        }
        else if (pattern[iPattern] == '*') 
        {
            starPos = iPattern;
            matchAfterStar = iText;
            iPattern++;
        }
        else if (starPos != -1) 
        {
            iPattern = starPos + 1;
            matchAfterStar++;
            iText = matchAfterStar;
        }
        else 
        {
            return false;
        }
    }

    while (pattern[iPattern] == '*')
    {
        iPattern++;
    }

    return pattern[iPattern] == '\0';
}

int main() {

    myArray<char> text(100);
    myArray<char> pattern(100);

    cout << "Введите последовательность (строку): ";
    char ch;
    while(cin.get(ch) && ch != '\n')
    {
        text.push_back(ch);
    }
    text.push_back('\0');

    cout << "Введите шаблон: ";
    while(cin.get(ch) && ch != '\n')
    {
        pattern.push_back(ch);
    }
    text.push_back('\0');

    if(patternMatch(&text.getElement(0), &pattern.getElement(0)))
    {
        cout << "Строка соответствует шаблону." << endl;
    }
    else
    {
        cout << "Строdа НЕ соответствует шаблону." << endl;
    }

    return 0;
}