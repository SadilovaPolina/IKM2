#include "header.h"
#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    try {
        setlocale(LC_ALL, ("ru"));
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);

        cout << "Добро пожаловать в игру 'Цепочка слов'!" << endl;
        cout << "Правила игры: очередное слово должно заканчиваться той буквой,";
        cout << "на которую закончилось предыдущее\n";
        cout << "Введите слова, которые использовались в этой игре (через пробел): ";
        string input;
        getline(cin, input);

        if (input.empty()) {
            throw runtime_error("Не было введено ни одного слова!");
        }

        saveToFile("a.txt", input);

        vector<string> words = split(input);
        ListChain chain(words);

        if (chain.buildChain()) {
            chain.print("b.txt");
            cout << "Цепочка слов успешно построена и сохранена в файл b.txt" << endl;
            cout << "результат: ";
            for (const string& word : chain.Result()) {
                cout << word << " ";
            }
            cout << endl << endl;            
            cout << " ^~^  ,\n('Y') )\n/   \\/ \n(\\|||/)" << endl;
        }
        else {
            cout << "Не удалось построить цепочку" << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Произошла ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}